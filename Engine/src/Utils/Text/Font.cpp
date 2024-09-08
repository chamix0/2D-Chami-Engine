#include "Font.h"

#include <string>
#define LITE_GFX_IMPLEMENTATION
#include "litegfx.h"
#define STB_TRUETYPE_IMPLEMENTATION  
#include "stb_truetype.h"
#include "../Vec2.h"

Font::~Font()
{
    ltex_free(texture);
    delete []bakedChar;
}

Font::Font(ltex_t* texture, stbtt_bakedchar* bakedChar, float height, Vec2 textSize, Vec2 color):
    texture(texture), bakedChar(bakedChar), height(height),
    textSize(textSize)
    
{
}

float Font::getHeight() const
{
    return height;
}

Vec2 Font::getTextSize() const
{
    return textSize;
}

Vec2 Font::GetEndOfTextPosition(std::string text, const Vec2 pos)
{
    //init the index and the current character to the first position
    int index = 0;
    char currentCharacter = *(text.c_str() + index);
    //create the position info
    stbtt_aligned_quad* q = new stbtt_aligned_quad();
    //temporal variables to store position
    float xpos = pos.x;
    float ypos = pos.y;

    //iterate the whole text
    while (index < text.size())
    {
        //get current character
        currentCharacter = *(text.c_str() + index);

        // bake the font position data
        stbtt_GetBakedQuad(bakedChar, static_cast<int>(textSize.x), static_cast<int>(textSize.y),
                           (currentCharacter - 32),
                           &xpos, &ypos, q, true);

        //increase index
        index++;
    }

    Vec2 finalPos = Vec2(q->x1, q->y1);

    //free the position data pointer
    delete q;
    return finalPos;
}


void Font::draw(std::string text, const Vec2 pos, float spacing, float angle) const
{
    //set blending mode to alpha
    lgfx_setblend(BLEND_ALPHA);
    //init the index and the current character to the first position
    int index = 0;
    char currentCharacter;
    //create the position info
    stbtt_aligned_quad* q = new stbtt_aligned_quad();
    //temporal variables to store position
    float xpos = pos.x;
    float ypos = pos.y;
    //iterate the whole text
    while (index < text.size())
    {
        //get current character
        currentCharacter = text[index];
        //get current character index
        int characterIndex = (currentCharacter - 32);
        // bake the font position data
        stbtt_GetBakedQuad(bakedChar, static_cast<int>(textSize.x), static_cast<int>(textSize.y), characterIndex,
                           &xpos, &ypos, q, true);
        //draw the font
        ltex_drawrotsized(texture, q->x0 + static_cast<float>(index) * spacing, q->y0, angle, 0, 0,
                          q->x1 - q->x0,
                          q->y1 - q->y0,
                          q->s0, q->t0, q->s1, q->t1);
        //increase index
        index++;
    }
    //free the position data pointer
    delete q;
    q = nullptr;
}
