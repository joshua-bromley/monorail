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
    int rotation = 0;
    int side = 0;
    int counter = 0;
    int tilesPlaced = 0;
    int placedThisTurn = 0;
    Texture texture;
    texture.loadFromFile("sprites.png");
    vector< vector<Tiles> > tiles;
    for(int i = 0; i < 13; i++){
        vector<Tiles> row;
        for(int j = 0; j < 14; j++){
            if(i == 6 && (j == 6 || j == 7)){
                Tiles tiles1(texture, 0, 1, true);
                tiles1.sprite.setPosition(Vector2f(64*j,64*i));
                tiles1.ends();
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
    Tiles stagingButton(texture);
    stagingButton.sprite.setPosition(10,900);
    Mouse mouse;
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
            else if(mouse.getPosition(window).y > 0 && mouse.getPosition(window).x > 0 && mouse.getPosition(window).y < 832 && mouse.getPosition(window).x < 896 && tilesPlaced < 16  && placement(tiles,mouse.getPosition(window),placedThisTurn,stagingButton)){
                tiles[(mouse.getPosition(window).y/64)][(mouse.getPosition(window).x/64)].retexture(side,rotation);
                tiles[(mouse.getPosition(window).y/64)][(mouse.getPosition(window).x/64)].newlyPlaced = true;
                tiles[(mouse.getPosition(window).y/64)][(mouse.getPosition(window).x/64)].placed = true;
                tiles[(mouse.getPosition(window).y/64)][(mouse.getPosition(window).x/64)].ends();
                rotation = 0;
                side = 0;
                tilesPlaced++;
                //placedThisTurn++;
                stagingButton.retexture(side,rotation);
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

    return 0;
}

bool pathfinder(vector< vector<Tiles> >& tiles, int x, int y, int last){
    if(tiles[x][y].placed == false){
        return false;
    }
      else if(tiles[x][y].end1 == last){
        switch(tiles[x][y].end2){
        case 0:
            return pathfinder(tiles, x-1 ,y , 1);
            break;
        case 1:
            return pathfinder(tiles, x+1, y, 0);
            break;
        case 2:
            return pathfinder(tiles, x, y+1, 3);
            break;
        case 3:
            return pathfinder(tiles, x, y-1, 2);
            break;
        }
      }
      else{
        switch(tiles[x][y].end1){
        case 0:
            return pathfinder(tiles, x-1 ,y , 1);
            break;
        case 1:
            return pathfinder(tiles, x+1, y, 0);
            break;
        case 2:
            return pathfinder(tiles, x, y+1, 3);
            break;
        case 3:
            return pathfinder(tiles, x, y-1, 2);
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
    cout << tempTile.end1 << endl << tempTile.end2 << endl;
    if(tilex < 0 || tilex > 14 || tiley < 0 || tiley > 13){
        return false;
    }
    if(tiles[tiley][tilex].placed == true){
        cout << "A" << endl;
        return false;
        // cannot place
    }

        //tile to the right of
    if(/*placedThisTurn == 0*/1){
        if(tiles[tiley][tilex + 1].placed == true){
            cout << "B" << endl;
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
            cout << "C" << endl;
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
                cout << "D" << endl;
            if((tiles[tiley+1][tilex].end1 != 3 && tiles[tiley+1][tilex].end2 != 3)&&(tempTile.end1 == 2 || tempTile.end2 == 2)){
                return false;
            }
            if((tiles[tiley+1][tilex].end1 == 3 || tiles[tiley+1][tilex].end2 == 3)&&(tempTile.end1 != 2 && tempTile.end2 != 2)){
                return false;
            }
            connected = true;
        }
        //tile below
        else if(tiles[tiley-1][tilex ].placed == true){
            cout << "E" << endl;
            if((tiles[tiley-1][tilex].end1 != 2 && tiles[tiley-1][tilex].end2 != 2)&&(tempTile.end1 == 3 || tempTile.end2 == 3)){
                return false;
            }
            if((tiles[tiley-1][tilex].end1 == 2 || tiles[tiley-1][tilex].end2 == 2)&&(tempTile.end1 != 3 && tempTile.end2 != 3)){
                return false;
            }
            connected = true;
        }
        cout << connected << endl;
        return connected;
    }



}
//hey josh
