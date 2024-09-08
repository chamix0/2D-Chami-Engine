#include "Sprite.h"
#include "litegfx.h"
#include "../MathUtils.h"
#include "../../Engine_Managers/LogicManager.h"
#include "../../Engine_Managers/RenderEngine.h"
#include "../Collision/CircleCollider.h"
#include "../Collision/PixelsCollider.h"
#include "../Collision/RectCollider.h"


Sprite::Sprite(std::string path, CollisionType collisionType, RenderMode render_mode, int hframes, int vframes,
               int currentFrame):
    hframes(hframes),
    vframes(vframes), tex(nullptr),
    render_mode(render_mode),
    collider(nullptr),
    collisionType(collisionType), blendMode(BLEND_SOLID),
    uv0(Vec2()), uv1(Vec2(1, 1)),
    fps(0), currentFrame(currentFrame)
{
    //load texture
    tex = RenderEngine::GetInstanceRenderEngine()->LoadTexture(path);
    //start stopwatch
    stopWatch.Start();
    //initialize size
    size = Vec2(static_cast<float>(tex->width) / static_cast<float>(hframes),
                static_cast<float>(tex->height) / static_cast<float>(vframes));
    //create collision
    SetCollisionType(collisionType);
}

Sprite::Sprite(std::string path, int hframes, int vframes, Vec2 color, lblend_t blendMode, Vec2 scale,
               Vec2 pivot, int fps, CollisionType collisionType, RenderMode render_mode,
               int currentFrame): hframes(hframes),
                                  vframes(vframes), tex(nullptr),
                                  render_mode(render_mode), collider(nullptr),
                                  collisionType(collisionType), blendMode(blendMode), color(color),
                                  scale(scale),
                                  pivot(pivot), uv0(Vec2()), uv1(Vec2(1, 1)), fps(fps), currentFrame(currentFrame)
{
    //load texture
    tex = RenderEngine::GetInstanceRenderEngine()->LoadTexture(path);
    //start stopwatch
    stopWatch.Start();
    //initialize size
    size = Vec2(static_cast<float>(tex->width) / static_cast<float>(hframes),
                static_cast<float>(tex->height) / static_cast<float>(vframes));
    //create collision
    SetCollisionType(collisionType);
}


const ltex_t* Sprite::getTexture() const
{
    return tex;
}

void Sprite::setTexture(const ltex_t* tex, int hframes, int vframes)
{
    this->tex = tex;
    this->hframes = hframes;
    this->vframes = vframes;
}

lblend_t Sprite::getBlend() const
{
    return blendMode;
}

void Sprite::setBlend(lblend_t mode)
{
    blendMode = mode;
}

float Sprite::getRed() const
{
    return color.R();
}

float Sprite::getGreen() const
{
    return color.G();
}

float Sprite::getBlue() const
{
    return color.B();
}

float Sprite::getAlpha() const
{
    return color.A();
}

void Sprite::setColor(Vec2 color)
{
    this->color = color;
}


const Vec2& Sprite::getScale() const
{
    return scale;
}

void Sprite::setScale(const Vec2& scale)
{
    this->scale = scale;
}

Vec2 Sprite::getSize() const
{
    return size;
}

const Vec2& Sprite::getPivot() const
{
    return pivot;
}

void Sprite::setPivot(const Vec2& pivot)
{
    this->pivot = pivot;
}

int Sprite::getHframes() const
{
    return hframes;
}

int Sprite::getVframes() const
{
    return vframes;
}

int Sprite::getFps() const
{
    return fps;
}

void Sprite::setFps(int fps)
{
    this->fps = fps;
}

int Sprite::getCurrentFrame() const
{
    return currentFrame;
}

void Sprite::setCurrentFrame(int frame)
{
    currentFrame = frame;
}

Vec2 Sprite::GetUv0() const
{
    return uv0;
}

Vec2 Sprite::GetUv1() const
{
    return uv1;
}

void Sprite::SetUv0(Vec2 uv)
{
    uv0 = uv;
}

void Sprite::SetUv1(Vec2 uv)
{
    uv1 = uv;
}

Sprite::~Sprite()
{
    if (pixels != nullptr)
    {
        delete [] pixels;
        pixels = nullptr;
    }
    delete collider;
    collider = nullptr;
}

void Sprite::update(float deltaTime, Vec2 pos, float angle)
{
    //update stopwatch
    stopWatch.ReceiveTick(deltaTime);

    //update Position and angle
    m_position = pos;
    m_angle = angle;

    //check if the elapsed time has passed 
    if (stopWatch.GetElapsedSeconds() > (1 / static_cast<float>(fps)))
    {
        //update the current frame 
        currentFrame = (currentFrame + 1) % (vframes * hframes);

        stopWatch.ReStart();
    }
}

void Sprite::draw() const
{
    int xIndex = currentFrame % hframes;
    int yIndex = currentFrame / hframes;

    //calculate uvs
    float u0 = static_cast<float>(xIndex) / static_cast<float>(hframes);
    float v0 = static_cast<float>(yIndex) / static_cast<float>(vframes);
    float u1 = static_cast<float>(xIndex + 1) / static_cast<float>(hframes);
    float v1 = static_cast<float>(yIndex + 1) / static_cast<float>(vframes);

    //set color
    lgfx_setcolor(color.R(), color.G(), color.B(), color.A());

    //set blend
    lgfx_setblend(blendMode);

    //position
    Camera* cam = LogicManager::GetInstanceLogicManager()->GetCamera();
    Vec2 pos = Vec2(m_position.x, m_position.y);
    switch (render_mode)
    {
    case WORLD:
        pos = cam->WorldPosToScreen(pos);
        break;
    case UI:
        break;
    default: ;
    }

    //draw when the object is in screen
    Vec2 auxScale = size * Vec2(abs(scale.x), abs((scale.y)));
    if (RenderEngine::GetInstanceRenderEngine()->
        IsRectInScreen(pos - Vec2(auxScale.x * pivot.x, auxScale.y * pivot.y), auxScale))
    {
        ltex_drawrotsized(tex, pos.x, pos.y, m_angle, pivot.x, pivot.y, size.x * scale.x, size.y * scale.y, u0, v0, u1,
                          v1);
    }
}

void Sprite::SimpleDraw() const
{
    //set color
    lgfx_setcolor(color.R(), color.G(), color.B(), color.A());

    //set blend
    lgfx_setblend(blendMode);

    //position
    Camera* cam = LogicManager::GetInstanceLogicManager()->GetCamera();
    Vec2 pos = Vec2(m_position.x, m_position.y);
    switch (render_mode)
    {
    case WORLD:
        pos = cam->WorldPosToScreen(pos);
        break;
    case UI:
        break;
    default: ;
    }

    //draw when the object is in screen
    Vec2 auxScale = size * Vec2(abs(scale.x), abs((scale.y)));
    if (RenderEngine::GetInstanceRenderEngine()->
        IsRectInScreen(pos - Vec2(auxScale.x * pivot.x, auxScale.y * pivot.y), auxScale))
    {
        ltex_drawrotsized(tex, pos.x, pos.y, m_angle, pivot.x, pivot.y, size.x * scale.x, size.y * scale.y, uv0.x,
                          uv0.y, uv1.x, uv1.y);
    }
}

void Sprite::DrawScaled(Vec2 pos, Vec2 scale, float alpha) const
{
    int xIndex = currentFrame % hframes;
    int yIndex = currentFrame / hframes;

    //calculate uvs
    float u0 = static_cast<float>(xIndex) / static_cast<float>(hframes);
    float v0 = static_cast<float>(yIndex) / static_cast<float>(vframes);
    float u1 = static_cast<float>(xIndex + 1) / static_cast<float>(hframes);
    float v1 = static_cast<float>(yIndex + 1) / static_cast<float>(vframes);

    //set color
    lgfx_setcolor(color.R(), color.G(), color.B(), alpha);

    //set blend
    lgfx_setblend(blendMode);

    //position
    Camera* cam = LogicManager::GetInstanceLogicManager()->GetCamera();
    switch (render_mode)
    {
    case WORLD:
        pos = cam->WorldPosToScreen(pos);
        break;
    case UI:
        break;
    default: ;
    }

    //draw when the object is in screen
    Vec2 auxScale = size * scale;
    if (RenderEngine::GetInstanceRenderEngine()->
        IsRectInScreen(pos - Vec2(auxScale.x * pivot.x, auxScale.y * pivot.y), auxScale))
    {
        ltex_drawrotsized(tex, pos.x, pos.y, m_angle, pivot.x, pivot.y, size.x * scale.x, size.y * scale.y, u0, v0, u1,
                          v1);
    }
}

void Sprite::SetCollisionType(CollisionType type)
{
    //set type
    collisionType = type;

    //delete old collider
    if (collider != nullptr)
    {
        delete collider;
        collider = nullptr;
    }

    //update collider
    switch (type)
    {
    case CIRCLE:
        collider = new CircleCollider(&m_position, Vec2(size.x * scale.x * pivot.x, size.y * scale.y * pivot.y),
                                      MathUtils::Max(size.x * scale.x / 2, size.y * scale.y / 2));
        break;
    case RECTANGLE:
        collider = new RectCollider(&m_position, pivot * scale * size,
                                    size * scale);
        break;
    case PIXEL:
        //get pixels
        pixels = new uint8_t[tex->height * tex->width * 4];
        ltex_getpixels(tex, pixels);
        collider = new PixelsCollider(&m_position, Vec2(size.x * pivot.x, size.y * pivot.y),
                                      Vec2(static_cast<float>(tex->width), static_cast<float>(tex->height)),
                                      pixels);
        break;
    case NONE:
        break;
    }
}

CollisionType Sprite::getCollisionType() const
{
    return collisionType;
}

const Collider* Sprite::getCollider() const
{
    return collider;
}

bool Sprite::collides(const Sprite& other) const
{
    if (collider == nullptr || other.getCollider() == nullptr)
    {
        return false;
    }
    return collider->collides(*other.collider);
}
