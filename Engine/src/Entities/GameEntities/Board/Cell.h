#pragma once
#include "../../Entity.h"

class Cell : public Entity
{
    //cell color
    Vec2 m_Color = Vec2(1);

    //cell sprite
    Sprite* m_Sprite = nullptr;

public:
    Cell(Vec2 position, Vec2 cellSize, Vec2 color);
    ~Cell() override;
    
    void Awake() override;
    
    void BeginPlay() override;
    
    void LogicUpdate(double tick) override;
    
    void InputUpdate(InputManager* input_manager) override;
    
    void RenderUpdate() override;
};
