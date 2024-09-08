#pragma once

#include <string>

#include "Enums.h"
#include "../StopWatch.h"
#include "../Vec2.h"
#include "../Collision/Collider.h"

enum RenderMode { WORLD, UI };

struct ltex_t;

class Sprite
{
public:
    //number of vertical and horizontal frames of the sprite
    int hframes, vframes;

    //texture that contains the sprite sheet
    const ltex_t* tex;
    uint8_t* pixels;
    RenderMode render_mode = WORLD;

    //position
    Vec2 m_position;

    //position
    float m_angle;

    //collision
    Collider* collider;
    CollisionType collisionType;

    lblend_t blendMode;
    /*sprite parameters*/
    Vec2 color;
    Vec2 scale;
    Vec2 size;
    Vec2 pivot;
    Vec2 uv0, uv1;
    int fps;
    int currentFrame;

private:
    StopWatch stopWatch;

public:
    Sprite(std::string path, CollisionType collisionType = CollisionType::NONE, RenderMode render_mode = WORLD,
           int hframes = 1, int vframes = 1, int currentFrame = 0);
    Sprite(std::string path, int hframes, int vframes, Vec2 color, lblend_t blendMode, Vec2 scale,
           Vec2 pivot, int fps, CollisionType collisionType = CollisionType::NONE, RenderMode render_mode = WORLD,
           int currentFrame = 0);
    ~Sprite();
    /// \brief update sprite state
    /// \param deltaTime 
    void update(float deltaTime, Vec2 pos, float angle = 0);
    /// \brief draw the sprite
    void draw() const;
    void SimpleDraw() const;
    void DrawScaled(Vec2 pos, Vec2 scale,float  alpha) const;

    /*collision*/
    /// \brief change collision type and update collider
    /// \param type 
    void SetCollisionType(CollisionType type);
    CollisionType getCollisionType() const;
    const Collider* getCollider() const;

    /// \brief check for collision with other sprite
    /// \param other 
    /// \return true if collides false if not
    bool collides(const Sprite& other) const;

    /*Texture*/
    const ltex_t* getTexture() const;
    void setTexture(const ltex_t* tex, int hframes = 1, int vframes = 1);

    /*Blending mode*/
    lblend_t getBlend() const;
    void setBlend(lblend_t mode);

    /*color*/
    float getRed() const;
    float getGreen() const;
    float getBlue() const;
    float getAlpha() const;
    void setColor(Vec2 color);

    /*scale*/
    const Vec2& getScale() const;
    void setScale(const Vec2& scale);

    /*position*/
    Vec2 getSize() const;
    const Vec2& getPivot() const;
    void setPivot(const Vec2& pivot);
    int getHframes() const;
    int getVframes() const;
    int getFps() const;
    void setFps(int fps);
    int getCurrentFrame() const;
    void setCurrentFrame(int frame);

    //uvs
    Vec2 GetUv0() const;
    Vec2 GetUv1() const;
    void SetUv0(Vec2 uv);
    void SetUv1(Vec2 uv);
};
