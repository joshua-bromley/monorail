#ifndef MINIWINDOW_H_INCLUDED
#define MINIWINDOW_H_INCLUDED
#include <SFML/Graphics.hpp>

class MiniWindow {
public:
    MiniWindow(int,int,Vector2f);
    void open();
    void close();
    void draw();
    void setPosition(Vector2f);
protected:
    Window window;
    int xSize;
    int ySize;
    Vector2f itemPosition;
};

class SpriteWindow: public MiniWindow{
public:
    SpriteWindow(Vector2i,Vector2i,Texture&) : MiniWindow(int,int,Vector2f)
    void retexture(Vector2i,Vector2i,Texture&);
private:
    Sprite sprite;
    Texture texture;
    Vector2i sprtieSize;
    Vector2i texturePosition;
    Vector2f scale;
};

class TextWindow: public MiniWindow{
public:
    TextWindow(int,Font&);
private:

};


#endif // MINIWINDOW_H_INCLUDED
