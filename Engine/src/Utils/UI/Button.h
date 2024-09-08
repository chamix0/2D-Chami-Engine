#pragma once
#include <string>

#include "../Text/Text.h"


class Vec2;
class Font;
class Sprite;

class Button
{
private:
    //sprite
    Sprite* sprite = nullptr;

    //text
    Text* text = nullptr;
    
    bool isSelected = false;

public:
    Button(std::string spritePath, std::string fontPath,float size=24);
    ~Button();
    void Draw(Vec2 position,Vec2 textOffset);
    void SetSelected(bool selected);
    bool GetSelected() const;
    void SetText(std::string cad);
    
};
