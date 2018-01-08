#include <iostream>
#include <vector>

using namespace std;

bool pathfinder(vector< vector<Tiles> >, int, int);

int main(){
    return 0;
}

bool pathfinder(vector< vector<Tiles> > tiles, int x, int y){
      if(tiles[x][y].isStation()){//.isStation is a placeholder
            return true;
      }
      else if(tiles[x][y].isBlank()){//.isBlank is a placeholder
        return false;
      }

}
