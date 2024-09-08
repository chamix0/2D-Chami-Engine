#pragma once
#include <string>

#include "../Vec2.h"
struct stbtt_bakedchar;
struct ltex_t;

class Font
{
public:
    ltex_t* texture;
    stbtt_bakedchar* bakedChar;
    float height;
    Vec2 textSize;

public:
    ~Font();
    Font(ltex_t* texture, stbtt_bakedchar* bakedChar, float height, Vec2 textSize);
    float getHeight() const;
    Vec2 getTextSize() const;
    Vec2 GetEndOfTextPosition(std::string text, Vec2 pos);
    

    /// \brief draws into the screen the input text
    /// \param text text to draw
    /// \param pos start position of the text
    /// \param spacing extra space between letters
    /// \param angle angle of the letters
    void draw(std::string text, Vec2 pos, float spacing = 0, float angle = 0) const;
};
