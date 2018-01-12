#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED
#include <SFML/Graphics.hpp>

class Tiles{
public:
    bool placed;
    int side;
    int rotation;
    int end1;
    int end2;
    //left = 0, right = 1, up = 2, down = 3
    Sprite sprite;

    Tiles(Texture & texture,int,int,bool);
    int getEnd1();
    int getEnd2();
    void setPlaced(bool);
    bool getPlaced();
};
Tiles::Tiles(Texture & texture,int s,int r,bool p){
    placed = p;
    side = s;
    rotation = r;
    Sprite.setTexture(Texture);
    Sprite.setTextureRect(IntRect(rotation*20,side*20,20,20));
    if(side == 0){
        if(rotation >= 1){
            end1 = 0;
            end2 = 0;
        }
        else{
            end1 = 2;
            end2 = 3;
        }
    }
    else{
        if(rotation >=1){
            end1 = 3;
        }
        else{
            end1 = 2;
        }
        if(rotation % 2 == 0){
            end2 = 0;
        }
        else{
            end2 = 1;
        }
    }
}
int Tiles::getEnd1(){
    return end1;
}

int Tiles::getEnd2(){
    return end2;
}

bool Tiles::getPlaced(){
    return placed;
}

void Tiles::setPlaced(bool input){
    placed = input;
}

 #endif
