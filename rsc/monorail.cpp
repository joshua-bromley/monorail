#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "tiles.h"
// Created by Sierra Loiselle and Joshua Bromley
using namespace std;
using namespace sf;
bool pathfinder(vector< vector<Tiles> >& tiles, int, int, int);
bool placement(vector< vector<Tiles> >& tiles,Vector2i,int,Tiles);
//y then x
int main(){
    RenderWindow window(VideoMode(900,1000), "Monorail");
    window.setFramerateLimit(60);
    bool turn = true;
    bool playAgain = true;
    bool leftbuttondown = false, rightbuttondown = false;
    bool impossible = false;
    int rotation = 0;
    int side = 0;
    int counter = 0;
    int tilesPlaced = 0;
    int placedThisTurn = 0;
    Texture texture;
    Texture buttonTexture;
    texture.loadFromFile("sprites.png");
    buttonTexture.loadFromFile("MonorailButtons.png");
    vector< vector<Tiles> > tiles;
    for(int i = 0; i < 13; i++){
        vector<Tiles> row;
        for(int j = 0; j < 14; j++){
            if(i == 6 && (j == 6 || j == 7)){
                Tiles tiles1(texture, 0, 1, true);
                tiles1.sprite.setPosition(Vector2f(64*j,64*i));
                tiles1.ends();
                tiles1.placed = true;
                row.push_back(tiles1);
            }
            else{
                Tiles tiles2(texture, 0, 3, false);
                tiles2.sprite.setPosition(Vector2f(64*j,64*i));
                row.push_back(tiles2);
            }
        }
        tiles.push_back(row);
    }
    Sprite endTurnButton;
    Sprite impossibleButton;
    endTurnButton.setTexture(buttonTexture);
    impossibleButton.setTexture(buttonTexture);
    endTurnButton.setTextureRect(IntRect(0,0,128,128));
    impossibleButton.setTextureRect(IntRect(128,0,128,128));
    endTurnButton.setPosition(Vector2f(250,850));
    impossibleButton.setPosition(Vector2f(750,850));
    Tiles stagingButton(texture);
    stagingButton.sprite.setPosition(10,900);
    Mouse mouse;
    cout << "Player 1s turn" << endl;
    while(playAgain && window.isOpen()){

        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
            if (event.type == Event::MouseButtonReleased){
                if(event.mouseButton.button == Mouse::Left){
                    leftbuttondown = false;
                }
                else if(event.mouseButton.button == Mouse::Right){
                    rightbuttondown = false;
                }
            }
        }
        if(Mouse::isButtonPressed(Mouse::Left) && leftbuttondown == false){
            leftbuttondown = true;
            if(stagingButton.sprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                if(side == 0){
                    if(rotation == 0){
                        rotation = 2;
                    }
                    else {
                        rotation = 0;
                    }
                }
                if(side == 1){
                    rotation ++;
                    rotation = rotation%4;
                }
                stagingButton.retexture(side,rotation);
            }
            else if(endTurnButton.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                placedThisTurn = 0;
                if(!impossible){
                    turn = !turn;
                }
                for(int i = 0; i < 13; i++){
                    for(int j = 0; j < 14; j++){
                        tiles[i][j].newlyPlaced = false;
                    }
                }
                if(pathfinder(tiles,7,6,0)){
                    break;
                }
                if(turn){
                    cout << "Player 1s turn" << endl;
                }
                else{
                    cout << "Player 2s turn" << endl;
                }
                stagingButton.retexture(side,rotation);
            }
            else if(impossibleButton.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                if(!impossible){
                    impossible = true;
                    if(turn){
                        cout << "Player 1 called impossible, Player 2 must finish the track" << endl;
                    }
                    else{
                        cout << "Player 2 called impossible, Player 1 must finish the track" << endl;
                    }
                }
                else{
                    if(turn){
                        cout << "Player 2 conceded, the track is impossible" << endl;
                    }
                    else{
                        cout << "Player 1 conceded, the track is impossible" << endl;
                    }

                }
            }
            else if(mouse.getPosition(window).y > 0 && mouse.getPosition(window).x > 0 && mouse.getPosition(window).y < 832 && mouse.getPosition(window).x < 896){
                if(tilesPlaced < 16){
                    if((placedThisTurn < 3 && placement(tiles,mouse.getPosition(window),placedThisTurn,stagingButton))||impossible){
                        tiles[(mouse.getPosition(window).y/64)][(mouse.getPosition(window).x/64)].retexture(side,rotation);
                        tiles[(mouse.getPosition(window).y/64)][(mouse.getPosition(window).x/64)].newlyPlaced = true;
                        tiles[(mouse.getPosition(window).y/64)][(mouse.getPosition(window).x/64)].placed = true;
                        tiles[(mouse.getPosition(window).y/64)][(mouse.getPosition(window).x/64)].ends();
                        rotation = 0;
                        side = 0;
                        tilesPlaced++;
                        placedThisTurn++;
                        stagingButton.retexture(side,rotation);
                    }
                }
            }
        }
        if(Mouse::isButtonPressed(Mouse::Right) && rightbuttondown == false){
            rightbuttondown = true;
            if(stagingButton.sprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                side++;
                side = side%2;
                rotation = 0;
                stagingButton.retexture(side,rotation);
            }
            else if(mouse.getPosition(window).y > 0 && mouse.getPosition(window).x > 0 && mouse.getPosition(window).y < 832 && mouse.getPosition(window).x < 896){
                if(tiles[(mouse.getPosition(window).y/64)][(mouse.getPosition(window).x/64)].newlyPlaced == true){
                    tiles[(mouse.getPosition(window).y/64)][(mouse.getPosition(window).x/64)].retexture(0,3);
                    tiles[(mouse.getPosition(window).y/64)][(mouse.getPosition(window).x/64)].newlyPlaced = false;
                    tiles[(mouse.getPosition(window).y/64)][(mouse.getPosition(window).x/64)].placed = false;
                    tilesPlaced--;
                    placedThisTurn--;
                }
            }

        }
        window.clear();
        for(int x = 0;x<tiles.size();x++){
            for(int y = 0;y<tiles[x].size();y++){
                 window.draw(tiles[x][y].sprite);
            }
        }
        window.draw(endTurnButton);
        window.draw(impossibleButton);
        window.draw(stagingButton.sprite);
        window.display();



    }
    if(turn){
        cout << "Player 2 wins!" << endl;
    }
    else{
        cout << "Player 1 wins!" << endl;
    }

    return 0;
}

bool pathfinder(vector< vector<Tiles> >& tiles, int x, int y, int last){
    if(tiles[y][x].placed == false){
        return false;
    }
    else if (x == 6 && y == 6){
        return true;
    }
      else if(tiles[y][x].end1 == last){
        switch(tiles[y][x].end2){
        case 0:
            return pathfinder(tiles, x-1 ,y , 1);//go left
            break;
        case 1:
            return pathfinder(tiles, x+1, y, 0);//go right
            break;
        case 2:
            return pathfinder(tiles, x, y-1, 3);//go down
            break;
        case 3:
            return pathfinder(tiles, x, y+1, 2);//go up
            break;
        }
      }
      else{
        switch(tiles[y][x].end1){
        case 0:
            return pathfinder(tiles, x-1 ,y , 1);//go left
            break;
        case 1:
            return pathfinder(tiles, x+1, y, 0);//go right
            break;
        case 2:
            return pathfinder(tiles, x, y-1, 3);//go down
            break;
        case 3:
            return pathfinder(tiles, x, y+1, 2);//go up
            break;
        }
      }

}
bool placement(vector< vector<Tiles> >& tiles,Vector2i click, int placedThisTurn, Tiles tempTile){
    //turn = # turn this is
    int tilex;
    int tiley;
    tilex = click.x/64;
    tiley = click.y/64;
    bool connected = false;
    tempTile.ends();
    if(tilex < 0 || tilex > 14 || tiley < 0 || tiley > 13){
        return false;
    }
    if(tiles[tiley][tilex].placed == true){
        return false;
        // cannot place
    }

        //tile to the right of
    if(placedThisTurn == 0){
        if(tiles[tiley][tilex + 1].placed == true){
            if((tiles[tiley][tilex+1].end1 != 0 && tiles[tiley][tilex+1].end2 != 0)&&(tempTile.end1 == 1 || tempTile.end2 == 1)){
                return false;
            }
            if((tiles[tiley][tilex+1].end1 == 0 || tiles[tiley][tilex+1].end2 == 0)&&(tempTile.end1 != 1 && tempTile.end2 != 1)){
                return false;
            }
            connected = true;
        }
        //tile to the left of
        else if(tiles[tiley][tilex - 1].placed == true){
            if((tiles[tiley][tilex-1].end1 != 1 && tiles[tiley][tilex-1].end2 != 1)&&(tempTile.end1 == 0 || tempTile.end2 == 0)){
                return false;
            }
            if((tiles[tiley][tilex-1].end1 == 1 || tiles[tiley][tilex-1].end2 == 1)&&(tempTile.end1 != 0 && tempTile.end2 != 0)){
                return false;
            }
            connected = true;
        }

        // tile above
        else if(tiles[tiley + 1][tilex ].placed == true){
            if((tiles[tiley+1][tilex].end1 != 2 && tiles[tiley+1][tilex].end2 != 2)&&(tempTile.end1 == 3 || tempTile.end2 == 3)){
                return false;
            }
            if((tiles[tiley+1][tilex].end1 == 2 || tiles[tiley+1][tilex].end2 == 2)&&(tempTile.end1 != 3 && tempTile.end2 != 3)){
                return false;
            }
            connected = true;
        }
        //tile below
        else if(tiles[tiley-1][tilex ].placed == true){
            if((tiles[tiley-1][tilex].end1 != 3 && tiles[tiley-1][tilex].end2 != 3)&&(tempTile.end1 == 2 || tempTile.end2 == 2)){
                return false;
            }
            if((tiles[tiley-1][tilex].end1 == 3 || tiles[tiley-1][tilex].end2 == 3)&&(tempTile.end1 != 2 && tempTile.end2 != 2)){
                return false;
            }
            connected = true;
        }
        return connected;
    }
    if(placedThisTurn == 2){
        if(tiles[tiley][tilex + 1].newlyPlaced == true && tiles[tiley][tilex + 2].newlyPlaced == true){
            if((tiles[tiley][tilex+1].end1 != 0 && tiles[tiley][tilex+1].end2 != 0)&&(tempTile.end1 == 1 || tempTile.end2 == 1)){
                return false;
            }
            if((tiles[tiley][tilex+1].end1 == 0 || tiles[tiley][tilex+1].end2 == 0)&&(tempTile.end1 != 1 && tempTile.end2 != 1)){
                return false;
            }
            connected = true;
        }
        //tile to the left of
        else if(tiles[tiley][tilex - 1].newlyPlaced == true && tiles[tiley][tilex - 2].newlyPlaced == true){
            if((tiles[tiley][tilex-1].end1 != 1 && tiles[tiley][tilex-1].end2 != 1)&&(tempTile.end1 == 0 || tempTile.end2 == 0)){
                return false;
            }
            if((tiles[tiley][tilex-1].end1 == 1 || tiles[tiley][tilex-1].end2 == 1)&&(tempTile.end1 != 0 && tempTile.end2 != 0)){
                return false;
            }
            connected = true;
        }

        // tile above
        else if(tiles[tiley + 1][tilex ].newlyPlaced == true && tiles[tiley+2][tilex].newlyPlaced == true){
            if((tiles[tiley+1][tilex].end1 != 2 && tiles[tiley+1][tilex].end2 != 2)&&(tempTile.end1 == 3 || tempTile.end2 == 3)){
                return false;
            }
            if((tiles[tiley+1][tilex].end1 == 2 || tiles[tiley+1][tilex].end2 == 2)&&(tempTile.end1 != 3 && tempTile.end2 != 3)){
                return false;
            }
            connected = true;
        }
        //tile below
        else if(tiles[tiley-1][tilex ].newlyPlaced == true && tiles[tiley-2][tilex].newlyPlaced == true){
            if((tiles[tiley-1][tilex].end1 != 3 && tiles[tiley-1][tilex].end2 != 3)&&(tempTile.end1 == 2 || tempTile.end2 == 2)){
                return false;
            }
            if((tiles[tiley-1][tilex].end1 == 3 || tiles[tiley-1][tilex].end2 == 3)&&(tempTile.end1 != 2 && tempTile.end2 != 2)){
                return false;
            }
            connected = true;
        }
        return connected;
    }
    if(placedThisTurn == 1){
        if(tiles[tiley][tilex + 1].newlyPlaced == true){
            if((tiles[tiley][tilex+1].end1 != 0 && tiles[tiley][tilex+1].end2 != 0)&&(tempTile.end1 == 1 || tempTile.end2 == 1)){
                return false;
            }
            if((tiles[tiley][tilex+1].end1 == 0 || tiles[tiley][tilex+1].end2 == 0)&&(tempTile.end1 != 1 && tempTile.end2 != 1)){
                return false;
            }
            connected = true;
        }
        //tile to the left of
        else if(tiles[tiley][tilex - 1].newlyPlaced == true){
            if((tiles[tiley][tilex-1].end1 != 1 && tiles[tiley][tilex-1].end2 != 1)&&(tempTile.end1 == 0 || tempTile.end2 == 0)){
                return false;
            }
            if((tiles[tiley][tilex-1].end1 == 1 || tiles[tiley][tilex-1].end2 == 1)&&(tempTile.end1 != 0 && tempTile.end2 != 0)){
                return false;
            }
            connected = true;
        }

        // tile above
        else if(tiles[tiley + 1][tilex ].newlyPlaced == true){
            if((tiles[tiley+1][tilex].end1 != 2 && tiles[tiley+1][tilex].end2 != 2)&&(tempTile.end1 == 3 || tempTile.end2 == 3)){
                return false;
            }
            if((tiles[tiley+1][tilex].end1 == 2 || tiles[tiley+1][tilex].end2 == 2)&&(tempTile.end1 != 3 && tempTile.end2 != 3)){
                return false;
            }
            connected = true;
        }
        //tile below
        else if(tiles[tiley-1][tilex ].newlyPlaced == true){
            if((tiles[tiley-1][tilex].end1 != 3 && tiles[tiley-1][tilex].end2 != 3)&&(tempTile.end1 == 2 || tempTile.end2 == 2)){
                return false;
            }
            if((tiles[tiley-1][tilex].end1 == 3 || tiles[tiley-1][tilex].end2 == 3)&&(tempTile.end1 != 2 && tempTile.end2 != 2)){
                return false;
            }
            connected = true;
        }
        return connected;
    }



}
//hey josh
