#include <iostream>
#include <vector>

using namespace std;

bool pathfinder(vector< vector<Tiles> >, int, int, int);

int main(){
    return 0;
}

bool pathfinder(vector< vector<Tiles> > tiles, int x, int y, int last){
      tiles[x][y].ends();
      if(tiles[x][y].isStation()){//.isStation is a placeholder
            return true;
      }
      else if(tiles[x][y].placed == false){
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
