#pragma once
#include <string>

#include "../Entity.h"
#include "../../Utils/Text/Font.h"
#include "../../Utils/Text/FontEnum.h"

class FontEntity : public Entity
{
private:
    std::string fontPath;
    float height;
    Vec2 color;

protected:
    Font* font = nullptr;
    std::string text;
    float spacing;

public:
    FontEntity(Vec2 pos, int renderLayer);
    FontEntity(Vec2 pos, int renderLayer, std::string text, FONTS font, float height,
               Vec2 color = Vec2(1, 1, 1), float spacing = 0);

    void LogicUpdate(double tick) override;
    void InputUpdate(InputManager* input_manager) override;
    void RenderUpdate() override;
    void OnCollisionEnter(Entity* otherEntity) override;
    void BeginPlay() override;
    void OnCollisionStay(Entity* otherEntity) override;
    void OnCollisionExit(Entity* otherEntity) override;
    ~FontEntity() override;
};
