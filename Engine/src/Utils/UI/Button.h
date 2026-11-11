#pragma once
#include <string>
#include "../Text/Text.h"
#include "../GameUtils/Delegates.h"

class InputManager;
class Vec2;
class Font;
class Sprite;

void DoA();
void DoB();
void DoC();

class Button
{
private:
    //position
    Vec2 m_position = Vec2(0,0);
    
    // void (std::lis *OnClick)();
    //sprite
    Sprite* sprite = nullptr;
    
    //text
    Text* text = nullptr;

    bool isSelected = false;
    bool m_isHovered = false;
    bool m_HighlightOnHover = false;
    
public:
    //events
    delegate<void()> OnClicked_Event;


public:
    Button(std::string spritePath, std::string fontPath, float size = 24, bool HighlightOnHover = false);
    ~Button();

    void SetPosition(Vec2 position); 
    Vec2 GetPosition()const;
    void Draw(Vec2 position, Vec2 textOffset);
    void SetSelected(bool selected);
    bool GetSelected() const;
    void SetText(std::string cad);
    void ProcessInputs(InputManager* input_manager);
    bool GetIsHovered() const;
    void SetHighlightOnHover(bool value);
};
