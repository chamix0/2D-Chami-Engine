#pragma once
#include <map>
#include <string>
#include <vector>

#include "pugixml.hpp"
#include "../Entities/Entity.h"
#include "../Entities/GameEntities/Camera/GameCameraEntity.h"
#include "../Entities/GameEntities/Player/PlayerEntity.h"
#include "../Utils/Camera.h"

class TileEntity;

class Scene
{
private:
    std::map<int, std::vector<Entity*>> entities;
    Camera* camera = nullptr;
    PlayerEntity* m_player = nullptr;
    GameCameraEntity* m_cameraEntity = nullptr;

    bool loaded = false;

public:
    Scene(std::map<int, std::vector<Entity*>> entities);
    ~Scene();

    std::map<int, std::vector<Entity*>> GetEntities();
    std::vector<Entity*> GetEntitiesArray();
    void InitScene();
    /// \brief Looks for all the marked entities and deletes them
    void RemoveMarkedEntities();
    /// \brief add an entity to the scene
    /// \param entity 
    void AddEntity(Entity* entity);
    Camera* GetCamera();
    GameCameraEntity* GetGameCameraEntity() { return m_cameraEntity; }

    void SetGameCameraEntity(GameCameraEntity* entity) { m_cameraEntity = entity; }

    void IterateLayers(pugi::xml_node mapNode, std::string imagePath, int firstID, int tileSize, int numTileSetCols,
                       int numTileSetRows);
    void IterateObjects(pugi::xml_node mapNode);
    /// \brief loads a map from an tmx
    /// \param path 
    /// \return aa
    /// 
    void LoadTileMap(std::string path);
    bool GetLoaded();
    PlayerEntity* GetPlayer() { return m_player; };

private:
    bool RemoveEntity(Entity* entity);
    void SetNeighbors(int numCol, int numRows, std::vector<TileEntity*> tileMap, std::vector<TileEntity*> tiles);
};
