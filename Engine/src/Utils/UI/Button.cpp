#include "Button.h"

#include "../Sprite/Sprite.h"
#include "../Vec2.h"

Button::Button(std::string spritePath, std::string fontPath,float size)
{
    sprite = new Sprite(spritePath, 2, 2, Vec2(1), BLEND_ALPHA,
                        Vec2(2), Vec2(0.5f, 0.5f), 0.f, CollisionType::NONE, UI);
    text = new Text(fontPath, "Hello!", size, Vec2(1));
}

Button::~Button()
{
    //delete sprite
    delete sprite;
    sprite = nullptr;

    //delete text
    delete text;
    text = nullptr;
}

void Button::Draw(Vec2 position, Vec2 textOffset)
{
    //draw background
    sprite->update(0, position);
    sprite->setCurrentFrame(isSelected ? 1 : 0);
    sprite->draw();

    //draw text
    text->SetColor(isSelected ? Vec2(1) : Vec2(0));
    text->SetPosition(position - Vec2((sprite->size.x / 2 * sprite->scale.x), 0) + textOffset);
    text->Draw();
}

void Button::SetSelected(bool selected)
{
    isSelected = selected;
}

bool Button::GetSelected() const
{
    return isSelected;
}

void Button::SetText(std::string cad)
{
    text->SetText(cad);
}
