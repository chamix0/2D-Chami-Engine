#include "FontEntity.h"

#include "litegfx.h"
#include "../../Engine_Managers/RenderEngine.h"
#include "../../Utils/Text/Font.h"

FontEntity::FontEntity(Vec2 pos, int rendLayer): Entity(pos, rendLayer),
                                                   fontPath(FONTS_TO_STRING(RETRO_GAMING)), height(12),
                                                   color(Vec2(1, 1, 1)),
                                                   text("Hello, World!"), spacing(0)
{
}

FontEntity::FontEntity(Vec2 pos, int renderLayer, std::string text, FONTS font, float height, Vec2 color,
                       float spacing):
    Entity(pos, renderLayer),
    fontPath(FONTS_TO_STRING(font)),
    height(height), color(color), text(text), spacing(spacing)
{
}

void FontEntity::LogicUpdate(double tick)
{

}

void FontEntity::InputUpdate(InputManager* input_manager)
{
}

void FontEntity::RenderUpdate()
{
    if (font != nullptr)
    {
        lgfx_setcolor(color.R(), color.G(), color.B(), 1);
        font->draw(text.c_str(), Vec2(m_position.x, m_position.y), 0, 0);
    }
}

void FontEntity::OnCollisionEnter(Entity* otherEntity)
{
}

void FontEntity::BeginPlay()
{
    RenderEngine* render_engine = RenderEngine::GetInstanceRenderEngine();
    font = render_engine->LoadFont(fontPath, height, 1024);
}

void FontEntity::OnCollisionStay(Entity* otherEntity)
{
}

void FontEntity::OnCollisionExit(Entity* otherEntity)
{
}

FontEntity::~FontEntity()
{
}
