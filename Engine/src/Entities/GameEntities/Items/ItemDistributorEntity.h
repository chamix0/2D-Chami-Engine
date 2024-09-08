#pragma once
#include "../../Entity.h"
#include "../../../Utils/Sprite/Sprite.h"
#include "../../../Utils/Text/Text.h"
#include "../Player/PlayerEntity.h"

enum Items
{
    LECHE,
    REFRESCO,
    LIMPIEZA,
    FRUTA,
    SUSHI,
    CARNE,
    HELADO,
    REPOSTELERIA,
    SNACKS,
    ITEM_COUNT
};

class ItemDistributorEntity : public Entity
{
private:
    float m_minDistance = 32.f;
    float m_maxDistance = 150.f;
    float m_progress = 0.f;
    //machine sprite
    Sprite* m_machineSprite = nullptr;

    //machineText
    Text* m_machineText = nullptr;

    //hint  text
    Text* m_hintText = nullptr;
    float m_alpha = 0;
    //itemType
    Items m_itemType;

    //player reference
    PlayerEntity* m_Player;

    //audio source
    AudioSource* audio_source;

    bool pressing = false;

public:
    ItemDistributorEntity(Vec2 position, int renderLayer, Items item);
    ~ItemDistributorEntity() override;
    void BeginPlay() override;
    void LogicUpdate(double tick) override;
    void InputUpdate(InputManager* input_manager) override;
    void RenderUpdate() override;

    static Items GetItemByString(std::string itemName);
    static std::string GetStringByItem(Items item);
    static Vec2 GetColorByItem(Items item);
};
