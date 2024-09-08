#include "Node.h"

Node::Node(TileEntity* tile, Node* parent, float f, float g, float h): m_tile(tile),
    m_parentNode(parent),  f_TotalCost(f), g_distToStart(g), h_estimatedDistToDest(h)
{
}
