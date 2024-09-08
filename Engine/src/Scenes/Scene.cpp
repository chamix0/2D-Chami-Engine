#include "Scene.h"

#include "pugixml.hpp"
#include "../Engine_Managers/RenderEngine.h"
#include "../Entities/CoreEntities/Tiles/AlienTileEntity.h"
#include "../Entities/CoreEntities/Tiles/OclussionTileEntity.h"
#include "../Entities/CoreEntities/Tiles/TileEntity.h"
#include "../Entities/GameEntities/Cashier/CashierEntity.h"
#include "../Entities/GameEntities/Coins/CoinEntity.h"
#include "../Entities/GameEntities/Collisions/BoxColliderEntity.h"
#include "../Entities/GameEntities/Items/ItemDistributorEntity.h"
#include "../Entities/GameEntities/Player/PlayerEntity.h"
#include "../Utils/Sprite/Sprite.h"


Scene::Scene(/*World* world,*/ std::map<int, std::vector<Entity*>> entities):
    entities(entities)
{
    camera = new Camera();
}


Scene::~Scene()
{
    //delete entities
    for (auto& kv : entities)
    {
        for (int i = 0; i < kv.second.size(); ++i)
        {
            delete kv.second[i];
        }
    }

    delete camera;
    camera = nullptr;
}

std::map<int, std::vector<Entity*>> Scene::GetEntities()
{
    return entities;
}

std::vector<Entity*> Scene::GetEntitiesArray()
{
    std::vector<Entity*> aux;
    for (auto& kv : GetEntities())
    {
        for (size_t i = 0; i < kv.second.size(); i++)
        {
            aux.push_back(kv.second[i]);
        }
    }
    return aux;
}

void Scene::InitScene()
{
    loaded = true;
    std::vector<Entity*> aux = GetEntitiesArray();

    //call awake function
    for (Entity* entity : aux)
    {
        entity->Awake();
    }

    //call begin play funcion
    for (Entity* entity : aux)
    {
        entity->BeginPlay();
    }

    //update camera position to the center
    camera->SetPostion(Vec2(abs(0), abs(0), abs(0), 0));
}

void Scene::AddEntity(Entity* entity)
{
    entities[entity->GetRenderLayer()].push_back(entity);
}

Camera* Scene::GetCamera()
{
    return camera;
}

void Scene::SetNeighbors(int numCol, int numRows, std::vector<TileEntity*> tileMap, std::vector<TileEntity*> tiles)
{
    if (tileMap.size() < numCol * numRows)
    {
        return;
    }

    for (int y = 0; y < numCol; ++y)
    {
        for (int x = 0; x < numRows; ++x)
        {
            int currentIndex = y * numCol + x;
            TileEntity* currentEntity = tileMap[currentIndex];
            if (currentEntity == nullptr)
            {
                continue;
            }

            //set nodes
            currentEntity->SetNodes(tiles);

            //neighbors
            std::vector<int> indexes;
            indexes.push_back((y - 1) * numCol + x);
            indexes.push_back((y + 1) * numCol + x);
            indexes.push_back(y * numCol + (x - 1));
            indexes.push_back(y * numCol + (x + 1));
            // indexes.push_back((y - 1) * numCol + (x - 1));
            // indexes.push_back((y - 1) * numCol + (x + 1));
            // indexes.push_back((y + 1) * numCol + (x - 1));
            // indexes.push_back((y + 1) * numCol + (x + 1));
            for (int item : indexes)
            {
                if (item < tileMap.size() && item >= 0)
                {
                    TileEntity* tile = tileMap[item];
                    if (tile != nullptr)
                    {
                        tileMap[currentIndex]->AddNeighBor(tileMap[item]);
                    }
                }
            }
        }
    }
}

void Scene::IterateLayers(pugi::xml_node mapNode, std::string imagePath, int firstID, int tileSize, int numTileSetCols,
                          int numTileSetRows)
{
    //iterate layers
    int layer = 0;
    for (pugi::xml_node layerNode = mapNode.child("layer"); layerNode; layerNode = layerNode.next_sibling("layer"))
    {
        int renderLayer = layer;
        std::string layerName = layerNode.attribute("name").as_string();
        int numCol = layerNode.attribute("width").as_int();
        int numRows = layerNode.attribute("height").as_int();
        int index = 0;
        int tileCount = 0;

        std::vector<TileEntity*> tileMap;
        std::vector<TileEntity*> tiles;

        //iterate tiles
        for (pugi::xml_node tileNode = layerNode.child("data").child("tile"); tileNode; tileNode = tileNode.
             next_sibling("tile"))
        {
            //get gid
            int gid = tileNode.attribute("gid").as_int();
            if (gid != 0)
            {
                int x = (index % numCol) * tileSize;
                int y = (index / numCol) * tileSize;

                //alpha walls (no collision)
                if (layerName == "alpha_walls")
                {
                    OclussionTileEntity* tile = new OclussionTileEntity(Vec2(x, y), renderLayer,
                                                                        "occlusionTile",
                                                                        imagePath,
                                                                        numTileSetCols,
                                                                        numTileSetRows,
                                                                        gid - firstID);

                    tileMap.push_back(tile);
                    tiles.push_back(tile);
                    tileCount++;
                    AddEntity(tile);
                }
                else if (layerName == "alien")
                {
                    AlienTileEntity* tile = new AlienTileEntity(Vec2(x, y), renderLayer,
                                                                "alienTile",
                                                                imagePath,
                                                                numTileSetCols,
                                                                numTileSetRows,
                                                                gid - firstID);

                    //set the alien position
                    if (tileCount % 1000 == 0)
                    {
                        tile->SetHasAlien(true);
                    }

                    //randomly create a  coin
                    int rand = std::rand() % 10;
                    if (rand == 0)
                    {
                        CoinEntity* coin_entity = new CoinEntity(Vec2(x, y), 3);
                        AddEntity(coin_entity);
                    }

                    tileCount++;
                    tiles.push_back(tile);
                    tileMap.push_back(tile);
                    AddEntity(tile);
                }
                else
                {
                    TileEntity* tile = new TileEntity(Vec2(x, y), renderLayer, "tile", imagePath,
                                                      numTileSetCols,
                                                      numTileSetRows,
                                                      gid - firstID, NONE);
                    tileMap.push_back(tile);
                    tiles.push_back(tile);
                    tileCount++;
                    AddEntity(tile);
                }
            }
            else
            {
                tileMap.push_back(nullptr);
            }

            //update index
            ++index;
        }
        SetNeighbors(numCol, numRows, tileMap, tiles);
        fprintf(stderr, "TileMap %s loaded\n", layerName.c_str());
        //increment layer index
        ++layer;
    }
}

void Scene::IterateObjects(pugi::xml_node mapNode)
{
    //iterate objects
    for (pugi::xml_node objectGrouNode = mapNode.child("objectgroup"); objectGrouNode; objectGrouNode = objectGrouNode.
         next_sibling("objectgroup"))
    {
        std::string objectGroupName = objectGrouNode.attribute("name").as_string();
        //iterate objects
        for (pugi::xml_node objectNode = objectGrouNode.child("object"); objectNode; objectNode = objectNode.
             next_sibling("object"))
        {
            //get gid
            float x = objectNode.attribute("x").as_int();
            float y = objectNode.attribute("y").as_int();
            float width = objectNode.attribute("width").as_int();
            float height = objectNode.attribute("height").as_int();

            if (objectGroupName == "colliders")
            {
                //create collider
                Vec2 size = Vec2(width, height);
                Vec2 position = Vec2(x, y) + (size / 2) - 16.f;
                AddEntity(new BoxColliderEntity(position, size, "wall"));
            }
            else if (objectGroupName == "Items")
            {
                std::string name = objectNode.attribute("name").as_string();
                Items item = ItemDistributorEntity::GetItemByString(name);

                float x = objectNode.attribute("x").as_int();
                float y = objectNode.attribute("y").as_int();
                float width = objectNode.attribute("width").as_int();
                float height = objectNode.attribute("height").as_int();
                Vec2 size = Vec2(width, height);
                Vec2 position = Vec2(x, y) + (size / 2) - 16.f;

                ItemDistributorEntity* itemDistributor = new ItemDistributorEntity(position, 4, item);
                AddEntity(itemDistributor);
            }
            else if (objectGroupName == "cashier")
            {
                float x = objectNode.attribute("x").as_int();
                float y = objectNode.attribute("y").as_int();
                float width = objectNode.attribute("width").as_int();
                float height = objectNode.attribute("height").as_int();
                Vec2 size = Vec2(width, height);
                Vec2 position = Vec2(x, y) + (size / 2) - 16.f;

                CashierEntity* cashier = new CashierEntity(position, 3);
                AddEntity(cashier);
            }
            else if (objectGroupName == "player")
            {
                //set player
                PlayerEntity* player = new PlayerEntity(Vec2(x, y), 4);
                m_player = player;

                //add player to scene
                AddEntity(player);
            }
        }
    }
}

void Scene::LoadTileMap(std::string path)
{
    //xml document
    pugi::xml_document document;

    //when fails return an empty map
    if (!document.load_file(path.c_str())) return;

    //get map root node
    pugi::xml_node mapNode = document.child("map");

    /*get the general data*/
    int mapWidth = mapNode.attribute("width").as_int(); //in tiles
    int mapHeight = mapNode.attribute("height").as_int(); //in tiles

    /*tile Set*/
    pugi::xml_node tilesetNode = document.child("map").child("tileset");

    //source image
    std::string imagePath = "data/Maps/";
    imagePath.append(tilesetNode.child("image").attribute("source").as_string());
    int imageWidth = tilesetNode.child("image").attribute("width").as_int();
    int imageHeight = tilesetNode.child("image").attribute("height").as_int();
    //tile set
    int firstID = tilesetNode.attribute("firstgid").as_int();
    int tileSize = tilesetNode.attribute("tilewidth").as_int(); //in pixels
    int numTileSetCols = tilesetNode.attribute("columns").as_int();
    int numTileSetRows = tilesetNode.attribute("tilecount").as_int() / numTileSetCols;

    //generate objects
    IterateObjects(mapNode);

    //create tiles
    IterateLayers(mapNode, imagePath, firstID, tileSize, numTileSetCols, numTileSetRows);
}

bool Scene::GetLoaded()
{
    return loaded;
}

void Scene::RemoveMarkedEntities()
{
    std::vector<Entity*> entitiesToDelete;
    for (auto& kv : entities)
    {
        for (int i = 0; i < kv.second.size(); ++i)
        {
            Entity* entity = kv.second[i];
            if (entity->HasToBeDeleted())
            {
                entitiesToDelete.push_back(entity);
            }
        }
    }

    for (size_t i = 0; i < entitiesToDelete.size(); i++)
    {
        RemoveEntity(entitiesToDelete[i]);
    }
}

bool Scene::RemoveEntity(Entity* entity)
{
    for (size_t i = 0; i < entities[entity->GetRenderLayer()].size(); ++i)
    {
        Entity* currentEntity = entities[entity->GetRenderLayer()][i];
        if (currentEntity == entity)
        {
            Entity* deadEntity = currentEntity;
            entities[entity->GetRenderLayer()].erase(std::next(entities[entity->GetRenderLayer()].begin(), i));
            delete deadEntity;
            return true;
        }
    }
    return false;
}
