#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "tiles.h"

using namespace std;

bool pathfinder(vector< vector<Tiles> >, int, int, int);

int main(){
    RenderWindow window(VideoMode(1000,1000), "Monorail");
    window.setFramerateLimit(60);
    bool turn = true;
    bool playAgain = true;
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

bool pathfinder(vector< vector<Tiles> > &tiles, int x, int y, int last){
      if(tiles[x][y].isStation()){//.isStation is a placeholder
            return true;
      }
      else if(tiles[x][y].getPlaced == false){
        return false;
      }
      else if(tiles[x][y].getEnd1 == last){
        switch(tiles[x][y].getEnd2){
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
        switch(tiles[x][y].getEnd1){
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
