#pragma once
#include <vector>

#include "Font.h"

class Text
{
private:
    std::string m_fontPath;
    std::string m_text;
    float m_size;
    Vec2 m_color;
    Vec2 m_position;
    std::vector<std::string> m_textsCads;

public:
    Text(std::string fontPath, std::string text, float size, Vec2 color);
    void Draw();
    void SetText(std::string text);
    std::string GetText();
    void SetSize(float size);
    float GetSize();
    void SetColor(Vec2 color);
    Vec2 GetColor();
    void SetPosition(Vec2 pos);

private:
    void ParseText(std::string text);
};
