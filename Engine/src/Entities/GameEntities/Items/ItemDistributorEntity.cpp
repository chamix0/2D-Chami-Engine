#include "ItemDistributorEntity.h"

#include "../../../Engine_Managers/AudioManager.h"
#include "../../../Engine_Managers/LogicManager.h"
#include "../../../Utils/MathUtils.h"

ItemDistributorEntity::ItemDistributorEntity(Vec2 position, int renderLayer, Items item): Entity(
    position, renderLayer, "itemDistributor")
{
    m_itemType = item;

    //sprite
    m_machineSprite = new Sprite("data/rect.png", 1, 1, Vec2(0, 0, 0, 0), BLEND_ALPHA,
                                 Vec2(2), Vec2(0.5f, 0.5f), 0.f, CollisionType::NONE);
    m_machineSprite->update(0, position);

    AddSprite(m_machineSprite);

    //machine text
    m_machineText = new Text("data/Fonts/Bubbleboddy.ttf", GetStringByItem(m_itemType), 13, GetColorByItem(m_itemType));

    //hint text
    m_hintText = new Text("data/Fonts/pixelFont.ttf", "Manten Spacio/A", 20, Vec2(0));
    m_machineText->SetPosition(LogicManager::GetInstanceLogicManager()->GetCamera()->WorldPosToScreen(position));

    //audio source
    audio_source = AudioManager::GetInstanceAudioManager()->CreateAudioSource(1, 4, false, position + Vec2(0, 16.f));
}

ItemDistributorEntity::~ItemDistributorEntity()
{
    delete m_machineText;
    m_machineText = nullptr;
    delete m_hintText;
    m_hintText = nullptr;
}

void ItemDistributorEntity::BeginPlay()
{
    //get player
    std::vector<Entity*> found = LogicManager::GetInstanceLogicManager()->FindEntitiesWithTag("Player");
    if (found.size() > 0)
    {
        m_Player = dynamic_cast<PlayerEntity*>(found[0]);
    }
}

void ItemDistributorEntity::LogicUpdate(double tick)
{
    float distance = m_Player->GetPosition().distance(GetPosition());
    Vec2 color = m_progress >= 5.f ? Vec2(1, 0, 0, 0) : Vec2(0.8f, 0.8f, 0.8f, 0);
    std::string text = "Manten Spacio/A";
    Vec2 position=LogicManager::GetInstanceLogicManager()->GetCamera()->WorldPosToScreen(GetPosition() + Vec2(-40, 0));
    if (pressing && m_progress < 5.f)
    {
        position=LogicManager::GetInstanceLogicManager()->GetCamera()->WorldPosToScreen(GetPosition() + Vec2(0, 0));
        color = Vec2(0, 0, 0, 0);
        m_progress += tick;
        text = std::to_string(static_cast<int>(m_progress));
    }

    if (m_progress >= 5.f)
    {
        m_Player->m_gameData.AddItem(m_itemType);
        text = "RECOGIDO";
    }
    //machine text postion
    m_machineText->SetPosition(
        LogicManager::GetInstanceLogicManager()->GetCamera()->WorldPosToScreen(GetPosition() + Vec2(-30, -50)));
    //hint text position
    m_hintText->SetPosition(position);
    //hint color
    m_hintText->SetText(text);
    m_hintText->SetColor(
        color + Vec2(0, 0, 0, 1 - MathUtils::NormalizeBetweenValues(distance, m_minDistance, m_maxDistance)));
}

void ItemDistributorEntity::InputUpdate(InputManager* input_manager)
{
    if (LogicManager::GetInstanceLogicManager()->GetPaused())
    {
        return;
    }

    if (m_Player->GetPosition().distance(GetPosition()) < m_maxDistance / 2.f)
    {
        bool inputSelect = input_manager->CheckPressedInput(vk_Space) || input_manager->
            CheckInstantInput(GAMEPAD_SOUTH);

        pressing = inputSelect;
    }
}

void ItemDistributorEntity::RenderUpdate()
{
    m_machineSprite->draw();
    m_machineText->Draw();
    m_hintText->Draw();
}

Items ItemDistributorEntity::GetItemByString(std::string itemName)
{
    if (itemName == "leche")
    {
        return LECHE;
    }
    if (itemName == "refresco")
    {
        return REFRESCO;
    }
    if (itemName == "limpieza")
    {
        return LIMPIEZA;
    }
    if (itemName == "fruta")
    {
        return FRUTA;
    }
    if (itemName == "sushi")
    {
        return SUSHI;
    }
    if (itemName == "carne")
    {
        return CARNE;
    }
    if (itemName == "helado")
    {
        return HELADO;
    }
    if (itemName == "reposteleria")
    {
        return REPOSTELERIA;
    }
    if (itemName == "snacks")
    {
        return SNACKS;
    }
    return LECHE;
}

std::string ItemDistributorEntity::GetStringByItem(Items item)
{
    switch (item)
    {
    case LECHE:
        return "LECHE";
    case REFRESCO:
        return "REFRESCO";
    case LIMPIEZA:
        return "LIMPIEZA";
    case FRUTA:
        return "FRUTA";
    case SUSHI:
        return "SUSHI";
    case CARNE:
        return "CARNE";
    case HELADO:
        return "HELADO";
    case REPOSTELERIA:
        return "REPOSTELERIA";
    case SNACKS:
        return "SNACKS";
    case ITEM_COUNT:
        return "ITEM_COUNT";
    }
    return "";
}

Vec2 ItemDistributorEntity::GetColorByItem(Items item)
{
    switch (item)
    {
    case LECHE:
        return Vec2(1);
    case REFRESCO:
        return Vec2(0.922f, 0.6f, 0.2f);
    case LIMPIEZA:
        return Vec2(0.969f, 0.592f, 0.918f);
    case FRUTA:
        return Vec2(0.475f, 0.91f, 0.4f);
    case SUSHI:
        return Vec2(0.988f, 0.478f, 0.553f);
    case CARNE:
        return Vec2(0.988f, 0.478f, 0.553f);
    case HELADO:
        return Vec2(0.157f, 0.251f, 0.902f);
    case REPOSTELERIA:
        return Vec2(0.922f, 0.796f, 0.341f);
    case SNACKS:
        return Vec2(0.902f, 0.322f, 0.157f);
    case ITEM_COUNT:
        return Vec2();
    }
    return Vec2();
}
