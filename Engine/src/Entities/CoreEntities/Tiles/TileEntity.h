#pragma once
#include <unordered_set>

#include "../../Entity.h"
#include "../../../Utils/Collision/Collider.h"

class Node;
class Sprite;

class TileEntity : public Entity
{
private:
    Sprite* m_tileSprite = nullptr;
    std::vector<TileEntity*> m_neighBors;
    std::vector<TileEntity*> m_nodes;
    std::map<TileEntity*, float> m_distances;
    std::map<TileEntity*, TileEntity*> m_paths;

protected:
    Entity* m_playerEntity = nullptr;

public:
    TileEntity(Vec2 position, int renderLayer, std::string tag, std::string path, int numCols, int numRows, int id,
               CollisionType collisionType = NONE);
    void RenderUpdate() override;
    void AddNeighBor(TileEntity* tile);
    void SetNodes(std::vector<TileEntity*> tiles);

    std::vector<TileEntity*> GetNeighBors();
    void LogicUpdate(double tick) override;
    void Awake() override;
    void BeginPlay() override;

protected:
    /// \brief A* algorithim
    std::vector<TileEntity*> AStar(Vec2 Position);
    TileEntity* FindClosestNode(Vec2 dest);
    Node* FindNodeOnList(TileEntity* childNode, std::vector<Node*>& list);
    void FreeListResources(std::vector<Node*>& list);
};
