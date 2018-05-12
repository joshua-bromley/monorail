#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "tiles.h"
// Created by Sierra Loiselle and Joshua Bromley
using namespace std;
using namespace sf;
bool pathfinder(vector< vector<Tiles> >& tiles, int, int, int, int, int);
bool placement(vector< vector<Tiles> >& tiles,Vector2i,int,Tiles);
//y then x
int main(){
    RenderWindow window(VideoMode(900,1000), "Monorail");
    window.setFramerateLimit(60);

    bool turn = true;
    bool leftbuttondown = false, rightbuttondown = false;
    bool impossible = false;
    int rotation = 0;
    int side = 0;
    int counter = 0;
    int tilesPlaced = 0;
    int placedThisTurn = 0;

    Texture textTexture;
    Texture texture;
    Texture buttonTexture;

    texture.loadFromFile("tubesprite2.png");
    buttonTexture.loadFromFile("tubebuttons.png");
    textTexture.loadFromFile("tubeplayers.png");

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
    Sprite turnMarkers [4];
    Sprite turnLabels;
    for(int i = 0; i < 4; i++){
        turnMarkers[i].setTexture(texture);
        turnMarkers[i].setTextureRect(IntRect(0,0,64,64));
        turnMarkers[i].setScale(2.0f,2.0f);
        turnMarkers[i].setPosition(516-128*i,860);
    }
    turnMarkers[3].setTextureRect(IntRect(0,64,64,64));

    endTurnButton.setTexture(buttonTexture);
    impossibleButton.setTexture(buttonTexture);
    turnLabels.setTexture(textTexture);

    endTurnButton.setTextureRect(IntRect(0,0,128,128));
    impossibleButton.setTextureRect(IntRect(128,0,128,128));
    turnLabels.setTextureRect(IntRect(0,0,256,64));

    endTurnButton.setPosition(Vector2f(644,852));
    impossibleButton.setPosition(Vector2f(772,852));
    turnLabels.setPosition(Vector2f(277,835));

    Tiles stagingButton(texture);
    stagingButton.sprite.setScale(2.0f,2.0f);
    stagingButton.sprite.setPosition(10,860);
    Mouse mouse;

    cout << "Player 1s turn" << endl;

    while(window.isOpen()){

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
            int mouseX = mouse.getPosition(window).x;
            int mouseY = mouse.getPosition(window).y;
            if(stagingButton.sprite.getGlobalBounds().contains(mouseX,mouseY)){
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
            else if(endTurnButton.getGlobalBounds().contains(mouseX,mouseY) && placedThisTurn > 0){
                placedThisTurn = 0;
                if(!impossible){
                    turn = !turn;
                }
                for(int i = 0; i < 13; i++){
                    for(int j = 0; j < 14; j++){
                        tiles[i][j].newlyPlaced = false;
                    }
                }
                if(pathfinder(tiles,7,6,0,tilesPlaced,-2)){
                    if(turn){
                        cout << "Player 2 wins!" << endl;
                    }
                    else{
                        cout << "Player 1 wins!" << endl;
                    }
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
            else if(impossibleButton.getGlobalBounds().contains(mouseX,mouseY) && placedThisTurn == 0){
                if(!impossible){
                    if(placedThisTurn == 0){
                        impossible = true;
                        turn = !turn;
                        if(turn){
                            cout << "Player 2 called impossible, Player 1 must finish the track" << endl;
                        }
                        else{
                            cout << "Player 1 called impossible, Player 2 must finish the track" << endl;
                        }
                    }
                }
                else{
                    if(turn){
                        cout << "Player 1 conceded, the track is impossible" << endl;
                    }
                    else{
                        cout << "Player 2 conceded, the track is impossible" << endl;
                    }
                    break;

                }
            }
            else if(mouseY > 0 && mouseX > 0 && mouseY < 832 && mouseX < 896){
                cout << tilesPlaced << endl;
                if(tilesPlaced <= 16){
                    if((placedThisTurn < 3 && placement(tiles,mouse.getPosition(window),placedThisTurn,stagingButton))||(impossible && placement(tiles,mouse.getPosition(window),0,stagingButton))){
                        tiles[(mouseY/64)][(mouseX/64)].retexture(side,rotation);
                        tiles[(mouseY/64)][(mouseX/64)].newlyPlaced = true;
                        tiles[(mouseY/64)][(mouseX/64)].placed = true;
                        tiles[(mouseY/64)][(mouseX/64)].ends();
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
            int mouseX = mouse.getPosition(window).x;
            int mouseY = mouse.getPosition(window).y;
            if(stagingButton.sprite.getGlobalBounds().contains(mouseX,mouseY)){
                side++;
                side = side%2;
                rotation = 0;
                stagingButton.retexture(side,rotation);
            }
            else if(mouseY > 0 && mouseX > 0 && mouseY < 832 && mouseX < 896){
                if(tiles[(mouseY/64)][(mouseX/64)].newlyPlaced == true){
                    tiles[(mouseY/64)][(mouseX/64)].retexture(0,3);
                    tiles[(mouseY/64)][(mouseX/64)].newlyPlaced = false;
                    tiles[(mouseY/64)][(mouseX/64)].placed = false;
                    tilesPlaced--;
                    placedThisTurn--;
                }
            }

        }
        if(turn){
            turnMarkers[1].setTextureRect(IntRect(0,0,64,64));
            turnMarkers[2].setTextureRect(IntRect(64,0,64,64));
        }
        else{
            turnMarkers[1].setTextureRect(IntRect(64,0,64,64));
            turnMarkers[2].setTextureRect(IntRect(0,0,64,64));
        }
        window.clear(Color(255,255,255));
        for(int x = 0;x<tiles.size();x++){
            for(int y = 0;y<tiles[x].size();y++){
                 window.draw(tiles[x][y].sprite);
            }
        }
        for(int i = 0; i < 4; i++){
            window.draw(turnMarkers[i]);
        }
        window.draw(turnLabels);
        window.draw(endTurnButton);
        window.draw(impossibleButton);
        window.draw(stagingButton.sprite);
        window.display();



    }


    return 0;
}

bool pathfinder(vector< vector<Tiles> >& tiles, int x, int y, int last, int tilesPlaced, int tilesPassed){
    tilesPassed ++;
    if(tiles[y][x].placed == false){
        return false;
    }
    else if (x == 6 && y == 6){
            if(tilesPassed >= tilesPlaced){
                return true;
            }
            else{
                return false;
            }
    }
    else if(tiles[y][x].end1 == last){
        switch(tiles[y][x].end2){
        case 0:
            return pathfinder(tiles, x-1 ,y , 1, tilesPlaced, tilesPassed);//go left
            break;
        case 1:
            return pathfinder(tiles, x+1, y, 0,tilesPlaced, tilesPassed);//go right
            break;
        case 2:
            return pathfinder(tiles, x, y-1, 3, tilesPlaced, tilesPassed);//go down
            break;
        case 3:
            return pathfinder(tiles, x, y+1, 2,  tilesPlaced, tilesPassed);//go up
            break;
        }
      }
      else{
        switch(tiles[y][x].end1){
        case 0:
            return pathfinder(tiles, x-1 ,y , 1, tilesPlaced, tilesPassed);//go left
            break;
        case 1:
            return pathfinder(tiles, x+1, y, 0, tilesPlaced, tilesPassed);//go right
            break;
        case 2:
            return pathfinder(tiles, x, y-1, 3, tilesPlaced, tilesPassed);//go down
            break;
        case 3:
            return pathfinder(tiles, x, y+1, 2, tilesPlaced, tilesPassed);//go up
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
