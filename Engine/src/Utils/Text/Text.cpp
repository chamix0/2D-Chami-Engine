#include "Text.h"

#include "litegfx.h"
#include "../../Engine_Managers/RenderEngine.h"

Text::Text(std::string fontPath, std::string text, float size, Vec2 color): m_fontPath(fontPath),
    m_text(text),
    m_size(size), m_color(color)
{
    //parse text for the first time
    ParseText(text);
}

void Text::Draw()
{
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    Font* font = render_engine->LoadFont(m_fontPath, m_size, 1024);
    if (font != nullptr)
    {
        //set color
        lgfx_setcolor(m_color.R(), m_color.G(), m_color.B(), m_color.A());
        for (int i = 0; i < m_textsCads.size(); ++i)
        {
            font->draw(m_textsCads[i], m_position + Vec2(0, m_size + 10.f) * i);
        }
    }
}

void Text::SetText(std::string text)
{
    m_text = text;
    ParseText(m_text);
}

std::string Text::GetText()
{
    return m_text;
}

void Text::SetSize(float size)
{
    m_size = size;
}

float Text::GetSize()
{
    return m_size;
}

void Text::SetColor(Vec2 color)
{
    m_color = color;
}

Vec2 Text::GetColor()
{
    return m_color;
}

void Text::SetPosition(Vec2 pos)
{
    m_position = pos;
}

void Text::ParseText(std::string text)
{
    m_textsCads.clear();
    std::string buffer="";
    for (int i = 0; i < text.size(); ++i)
    {
        char currentChar = text[i];
        if (currentChar == '|')
        {
            m_textsCads.push_back(buffer);
            buffer.clear();
        }
        else
        {
            buffer.push_back(currentChar);
        }
    }
    m_textsCads.push_back(buffer);
}
