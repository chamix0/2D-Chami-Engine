#include "SquareEntity.h"

#include <glfw3.h>

#include "litegfx.h"


SquareEntity::SquareEntity(Vec2 pos, Vec2 color, Vec2 extents, bool moveWithMouse): Entity(pos), color(color),
                                                                                         extents(extents), moveWithMouse(moveWithMouse)
{
}

void SquareEntity::LogicUpdate(double tick)
{
}

void SquareEntity::InputUpdate(InputManager* inputManager)
{
    if (moveWithMouse)
    {
        double x, y;
        glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
        m_position = Vec2(x - extents.x / 2, y - extents.y / 2);
    }
}

void SquareEntity::RenderUpdate()
{
    lgfx_setcolor(color.x, color.y, color.z, 1);
    lgfx_drawrect(m_position.x, m_position.y, extents.x, extents.y);
}

void SquareEntity::OnCollisionEnter(Entity* otherEntity)
{
}

void SquareEntity::OnCollisionStay(Entity* otherEntity)
{
}

void SquareEntity::OnCollisionExit(Entity* otherEntity)
{
}

void SquareEntity::BeginPlay()
{
}

SquareEntity::~SquareEntity()
{
}
