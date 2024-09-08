#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>

#include "../Engine_Managers/Input/InputManager.h"
#include "../Utils/Vec2.h"


class Sprite;

class Entity
{
protected:
    int m_renderLayer;
    std::string m_tag;
    std::vector<Sprite*> m_sprites;
    Vec2 m_position;

private:
    bool m_checkCollision = false;
    bool m_hasToBeDeleted = false;

    std::map<Entity*, bool> m_collisionEntities;

public:
    Entity(Vec2 position, int renderLayer = 0, std::string tag = "default", bool CheckCollision = false);
    virtual ~Entity();

    Vec2 GetPosition() const;
    void SetPosition(Vec2 pos, float tick = 0);


    int GetRenderLayer() const;

    /// \brief function called before begin play
    virtual void Awake();
    
    /// \brief function called when a the scene is loaded
    virtual void BeginPlay();
    
    /// \brief Slot that will process all the logic components before logic update
    /// \param tick 
    virtual void EarlyUpdate(double tick);
    
    /// \brief Slot that will process all the logic components before render
    /// \param tick 
    virtual void LogicUpdate(double tick);

    /// \brief Slot that will process all the logic components after logic update render
    /// \param tick 
    virtual void LogicLateUpdate(double tick);

    /// \brief Slot that will be performed even if the time scale is 0 for example for the pause menu
    /// \param tick 
    virtual void InputUpdate(InputManager* input_manager);
    /// \brief event when other entity collides with this one
    /// \param otherEntity 
    virtual void OnCollisionEnter(Entity* otherEntity);
    /// \brief event when other entity continues colliding with this one
    /// \param otherEntity 
    virtual void OnCollisionStay(Entity* otherEntity);
    /// \brief event when other entity ends colliding with this one
    /// \param otherEntity 
    virtual void OnCollisionExit(Entity* otherEntity);

    /// \brief slot that will do all the render components after updating the logic
    virtual void RenderUpdate();

    void AddSprite(Sprite* sprite);

    void RemoveSprite(Sprite* sprite);
    std::vector<Sprite*> GetSprites();

    bool Collides(Entity* otherEntity);

    /// \brief marks the entity si the scene deletes before doing the slots
    void DeleteEntity();

    /// \brief get if this entity should be deleted
    /// \return 
    bool HasToBeDeleted() const;

    bool GetCheckCollision();
    void SetCheckCollision(bool value);

    bool HasCollision();

    bool GetColliding(Entity* entity);
    void SetColliding(Entity* entity, bool value);

    //tag
    std::string GetTag() const;
};
