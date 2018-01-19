#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "tiles.h"

using namespace std;
using namespace sf;
bool pathfinder(vector< vector<Tiles> >& tiles, int, int, int);
bool placement(vector< vector<Tiles> >& tiles,Vector2f,Texture &,int);

int main(){
    RenderWindow window(VideoMode(1000,1000), "Monorail");
    window.setFramerateLimit(60);
    bool turn = true;
    bool playAgain = true;
    Texture texture;
    texture.loadFromFile("sprites.png");
    vector< vector<Tiles> > tiles;
    for(int i = 0; i < 13; i++){
        vector<Tiles> row;
        for(int j = 0; j < 14; j++){
            if(i == 6 && (j == 6 || j == 7)){
                Tiles tiles(texture, 0, 1, true);
                row.push_back(tiles);
            }
            else{
                Tiles tiles(texture, 0, 3, false);
                row.push_back(tiles);
            }
        }

    }
    while(playAgain && window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }


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
bool placement(vector< vector<Tiles> >& tiles,Vector2f click,Texture & texture,int turn,int s,int r){
    //turn = # turn this is
    int tilex;
    int tiley;
    bool breakcheck = false;
    for(int x = 0;x < tiles.size();x++){
        for(int y = 0; y <tiles[0].size();x++){
            if(click.x >= tiles[x][y].sprite.getPosition().x && click.x <= tiles[x][y].sprite.getPosition().x + 64 && click.y >= tiles[x][y].sprite.getPosition().y && click.y <= tiles[x][y].sprite.getPosition().y + 64){
                tilex = x;
                tiley = y;
                breakcheck = true;
            }
            if(breakcheck == true){
                break;
            }
        }
        if(breakcheck == true){
                break;
        }
    }
    if(tiles[tilex][tiley].placed == true){
        return false;
        // cannot place
    }
    int connectcount = 0;
    //tile to the right of
    if(tiles[tilex + 1][tiley].placed == true){
        connectcount++;
        if(tiles[tilex + 1][tiley].end1 == tiles[tilex][tiley].end1){

        }
        else if(tiles[tilex + 1][tiley].end1 == tiles[tilex][tiley].end2){
        }
        else if(tiles[tilex + 1][tiley].end2 == tiles[tilex][tiley].end1){
        }
        else if(tiles[tilex + 1][tiley].end2 == tiles[tilex][tiley].end2){
        }
        else{
            return false;
        }
    }
    //tile to the left of
    if(tiles[tilex - 1][tiley].placed == true){
        connectcount++;
        if(tiles[tilex - 1][tiley].end1 == tiles[tilex][tiley].end1){
        }
        else if(tiles[tilex - 1][tiley].end1 == tiles[tilex][tiley].end2){
        }
        else if(tiles[tilex - 1][tiley].end2 == tiles[tilex][tiley].end1){

        }
        else if(tiles[tilex - 1][tiley].end2 == tiles[tilex][tiley].end2){
        }
        else{
            return false;
        }
    }
    //tile to the right and above
    if(tiles[tilex + 1][tiley + 1].placed == true){
        connectcount++;
        if(tiles[tilex + 1][tiley + 1].end1 == tiles[tilex][tiley].end1){
        }
        else if(tiles[tilex + 1][tiley + 1].end1 == tiles[tilex][tiley].end2){
        }
        else if(tiles[tilex + 1][tiley + 1].end2 == tiles[tilex][tiley].end1){
        }
        else if(tiles[tilex + 1][tiley + 1].end2 == tiles[tilex][tiley].end2){
        }
        else{
            return false;
        }
    }
    //tile to the right and below
    if(tiles[tilex + 1][tiley - 1].placed == true){
        connectcount++;
        if(tiles[tilex + 1][tiley - 1].end1 == tiles[tilex][tiley].end1){
        }
        else if(tiles[tilex + 1][tiley - 1].end1 == tiles[tilex][tiley].end2){
        }
        else if(tiles[tilex + 1][tiley - 1].end2 == tiles[tilex][tiley].end1){
        }
        else if(tiles[tilex + 1][tiley - 1].end2 == tiles[tilex][tiley].end2){
        }
        else{
            return false;
        }
    }
    //tile to the left and below
    if(tiles[tilex - 1][tiley -1].placed == true){
        connectcount++;
        if(tiles[tilex - 1][tiley -1].end1 == tiles[tilex][tiley].end1){
        }
        else if(tiles[tilex - 1 ][tiley -1].end1 == tiles[tilex][tiley].end2){
        }
        else if(tiles[tilex - 1 ][tiley -1].end2 == tiles[tilex][tiley].end1){
        }
        else if(tiles[tilex - 1 ][tiley -1].end2 == tiles[tilex][tiley].end2){
        }
        else{
            return false;
        }
    }
    //tile to the left and above
    if(tiles[tilex -1][tiley + 1].placed == true){
        connectcount++;
        if(tiles[tilex -1 ][tiley + 1].end1 == tiles[tilex][tiley].end1){

        }
        else if(tiles[tilex - 1][tiley + 1].end1 == tiles[tilex][tiley].end2){
        }
        else if(tiles[tilex - 1][tiley + 1].end2 == tiles[tilex][tiley].end1){
        }
        else if(tiles[tilex - 1][tiley + 1].end2 == tiles[tilex][tiley].end2){
        }
        else{
            return false;
        }
    }
    // tile above
    if(tiles[tilex ][tiley + 1].placed == true){
        connectcount++;
        if(tiles[tilex ][tiley + 1].end1 == tiles[tilex][tiley].end1){

        }
        else if(tiles[tilex ][tiley + 1].end1 == tiles[tilex][tiley].end2){
        }
        else if(tiles[tilex ][tiley + 1].end2 == tiles[tilex][tiley].end1){

        }
        else if(tiles[tilex ][tiley + 1].end2 == tiles[tilex][tiley].end2){
        }
        else{
            return false;
        }
    }
    //tile below
    if(tiles[tilex ][tiley-1].placed == true){
        connectcount++;
        if(tiles[tilex ][tiley-1].end1 == tiles[tilex][tiley].end1){
        }
        else if(tiles[tilex ][tiley-1].end1 == tiles[tilex][tiley].end2){
        }
        else if(tiles[tilex ][tiley-1].end2 == tiles[tilex][tiley].end1){
        }
        else if(tiles[tilex ][tiley-1].end2 == tiles[tilex][tiley].end2){
        }
        else{
            return false;
        }
    }
    if(connectcount == 0){
        return false;
    }
    else{
        tiles[tilex][tiley].retexture(s,r,texture);
        return true;
    }

}
