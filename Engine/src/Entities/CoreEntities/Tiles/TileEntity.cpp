#include "TileEntity.h"

#include <unordered_set>

#include "Node.h"
#include "../../../Engine_Managers/LogicManager.h"
#include "../../../Engine_Managers/RenderEngine.h"
#include "../../../Utils/MathUtils.h"
#include "../../../Utils/Sprite/Sprite.h"

TileEntity::TileEntity(Vec2 position, int renderLayer, std::string tag, std::string path, int numCols, int numRows,
                       int id, CollisionType collisionType): Entity(position, renderLayer, tag, false)
{
    //create  sprite
    m_tileSprite = new Sprite(path, numCols, numRows, Vec2(1), BLEND_ALPHA,
                              Vec2(1), Vec2(0.5f), 0,
                              collisionType, WORLD, id);

    //updata sprite
    m_tileSprite->update(0.f, position);

    //register sprite
    AddSprite(m_tileSprite);
}

void TileEntity::RenderUpdate()
{
    Entity::RenderUpdate();

    //draw sprite
    m_tileSprite->draw();
}

void TileEntity::AddNeighBor(TileEntity* tile)
{
    m_neighBors.push_back(tile);
}

void TileEntity::SetNodes(std::vector<TileEntity*> tiles)
{
    m_nodes = tiles;
}

std::vector<TileEntity*> TileEntity::GetNeighBors()
{
    return m_neighBors;
}

void TileEntity::LogicUpdate(double tick)
{
}

void TileEntity::Awake()
{
}

void TileEntity::BeginPlay()
{
    //get player
    m_playerEntity = LogicManager::GetInstanceLogicManager()->GetCurrentScene()->GetPlayer();
}


std::vector<TileEntity*> TileEntity::AStar(Vec2 Position)
{
    //destination node
    TileEntity* destTile = FindClosestNode(Position);
    //open list
    std::vector<Node*> openList;
    //closed list
    std::vector<Node*> closedList;

    // Add the start node
    // put the startNode on the openList (leave it's f at zero)
    openList.push_back(new Node(this, nullptr, 0, 0, 0));

    // Loop until you find the end
    while (!openList.empty())
    {
        // Get the current node
        Node* currentNode = openList[0];

        //let the currentNode equal the node with the least f value
        for (int i = 0; i < openList.size(); ++i)
        {
            Node* aux = openList[i];
            currentNode->f_TotalCost = aux->f_TotalCost < currentNode->f_TotalCost
                                           ? aux->f_TotalCost
                                           : currentNode->f_TotalCost;
        }

        //remove the currentNode from the openList
        openList.erase(openList.begin());

        //add the currentNode to the closedList
        closedList.push_back(currentNode);

        //Found the goal
        if (currentNode->m_tile == destTile)
        {
            std::vector<TileEntity*> path;
            Node* aux = currentNode;

            //backtrack to find the pathc
            while (aux != nullptr)
            {
                //add node to the path
                path.push_back(aux->m_tile);

                //current node is its parent
                aux = aux->m_parentNode;
            }
            return path;
        }

        //Generate children
        std::vector<Node*> children;
        for (int i = 0; i < currentNode->m_tile->m_neighBors.size(); ++i)
        {
            TileEntity* neighBorTile = currentNode->m_tile->GetNeighBors()[i];
            children.push_back(new Node(neighBorTile, currentNode));
        }

        //for each child in the children
        for (Node* child : children)
        {
            //Child is on the closedList
            if (FindNodeOnList(child->m_tile, closedList) != nullptr)
            {
                delete child;
                child = nullptr;
                continue;
            }

            //Create the f, g, and h values
            //child.g = currentNode.g + distance between child and current
            child->g_distToStart = currentNode->g_distToStart + 1 /*currentNode->m_tile->GetPosition().distance(
                child->m_tile->GetPosition()*/;
            //child.h = distance from child to end
            child->h_estimatedDistToDest = pow(child->m_tile->GetPosition().x, 2) + pow(
                child->m_tile->GetPosition().y, 2);
            //child.f = child.g + child.h
            child->f_TotalCost = child->g_distToStart + child->h_estimatedDistToDest;

            // Child is already in openList
            if (FindNodeOnList(child->m_tile, openList))
            {
                delete child;
                child = nullptr;
                continue;
            }

            //Add the child to the openList
            openList.push_back(child);
        }
    }

    //free resources
    FreeListResources(openList);
    FreeListResources(closedList);
}


TileEntity* TileEntity::FindClosestNode(Vec2 dest)
{
    //get the first closet point 
    for (int i = 0; i < m_nodes.size(); ++i)
    {
        TileEntity* currentNode = m_nodes[i];
        if (currentNode->GetPosition().distance(dest) < 64.f)
        {
            return currentNode;
        }
    }
    return this;
}

Node* TileEntity::FindNodeOnList(TileEntity* childNode, std::vector<Node*>& list)
{
    for (int i = 0; i < list.size(); ++i)
    {
        if (childNode == list[i]->m_tile)
        {
            return list[i];
        }
    }
    return nullptr;
}

void TileEntity::FreeListResources(std::vector<Node*>& list)
{
    for (int i = 0; i < list.size(); ++i)
    {
        delete list[i];
        list[i] = nullptr;
    }
}
