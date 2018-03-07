#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <SFML/Graphics.hpp>

using namespace sf;

class MenuOption{
public:
    Vector2f position;
    Vector2f dimension;
    Vector2f textureSize;
    Vector2f texturePosition;
    int toggles;
    Sprite option;

    MenuOption(Texture&, Vector2f, Vector2f);
    void setPosition(Vector2f);
    void setSize(Vector2f);
    void setTexture(Texture&);
    void shiftTexture(Vector2f);
    Vector2f getPosition();
    Vector2f getSize();
    Vector2f getTexturePosition();
    Vector2f getTextureSize();
    int getToggles();
    Sprite getSprite();
};

MenuOption::MenuOption(Texture& texture, Vector2f sizeInput, Vector2f startPoint){
    option.setTexture(texture);
    dimension = sizeInput;
    textureSize = sizeInput;
    texturePosition = startPoint;
    option.setTextureRect(IntRect(texturePosition,textureSize));
}

void setPosition::MenuOption(Vector2f positionInput){
    position = positionInput;
    option.setPosition(position);
}

void setSize::MenuOption(Vector2f sizeInput){
    option.setScale(dimension.x/sizeInput.x,dimension.y/sizeInput.y);
    dimension = sizeInput;
}

void setTexture::MenuOption(Texture& texture){
    option.setTexture(texture);
}

Vector2f getPosition::MenuOption(){
    return position;
}

Vector2f getSize::MenuOption(){
    return dimension;
}

Vector2f getTexturePosition::MenuOption(){
    return texturePosition;
}

Vector2f getTextureSize::MenuOption(){
    return textureSize;
}

int getToggles::MenuOption(){
    return toggles;
}

Sprite getSprite::MenuOption(){
    return option;
}


class Button::MenuOption{
public:
<<<<<<< HEAD
    bool isClicked(Vector2f)
=======
    bool isClicked(Vector2f);
};
>>>>>>> 99b68186e33f25520d1a92ec95a269f7659a118b

bool isClicked::Button(Vector2f mousePosition){
    if(sprite.getGlobalBounds().contains(mousePosition)){
        return true;
    }
    else{
        return false;
    }
}

class Dragable::MenuOption{
public:
    void dragged(Vector2f);
};

void dragged::Dragable(Vector2f mousePosition){
    sprite.setPosition(mousePosition);
}

#endif // MENU_H_INCLUDED
