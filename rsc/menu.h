#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <SFML/Graphics.hpp>

using namespace sf;

class Button {
public:
    Vector2f position;
    Vector2f dimension;
    int clicks;
    Sprite button;


    Button(Texture&, Vector2f);
    bool isClicked(Vector2f);
    void setPosition(Vector2f);
    void setSize(Vector2f);

};

#endif // MENU_H_INCLUDED
