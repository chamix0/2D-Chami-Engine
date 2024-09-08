#pragma once
#include "TileEntity.h"
#include "../../../Utils/Vec2.h"

class Node
{
public:
    Node(TileEntity* tile, Node* parent, float f = 0, float g = 0, float h = 0);
    TileEntity* m_tile = nullptr;
    Node* m_parentNode = nullptr;
    float f_TotalCost = 0;
    float g_distToStart = 0;
    float h_estimatedDistToDest = 0;
};
