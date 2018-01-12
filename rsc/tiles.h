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
    void ends();
    void retexture(int,int,Texture& texture);
};
Tiles::Tiles(Texture & texture,int s,int r,bool p){
    placed = p;
    side = s;
    rotation = r;
    Sprite.setTexture(Texture);
    Sprite.setTextureRect(IntRect(rotation*64,side*64,64,64));
}
void Tiles::ends(){
    if(side == 0){
        if(rotation <= 1){
            end1 = 0;
            end2 = 1;
        }
        else{
            end1 = 2;
            end2 = 3;
        }
    }
    else{
        if(rotation <=1){
            end1 = 3;
        }
        else{
            end1 = 2;
        }
        if(rotation % 2 == 0){
            end2 = 1;
        }
        else{
            end2 = 0;
        }
    }
}
void Tiles::retexture(int s,int r,Texture & texture){
    Sprite.setTexture(Texture);
    Sprite.setTextureRect(IntRect(rotation*64,side*64,64,64));
}
 #endif
