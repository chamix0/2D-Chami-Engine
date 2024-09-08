#pragma once
#include <map>
#include <string>
#include <vector>
#include "../Utils/Debug/DebugElem.h"


class Sprite;
//forward declaration
class Entity;
struct ltex_t;
class Font;
class TimeManager;
class Vec2;

class RenderEngine
{
private:
    static RenderEngine* renderInstance; //singleton instance
    int WINDOW_WITH = 800;
    int WINDOW_HEIGHT = 800;
    std::map<std::string, ltex_t*> textures;
    std::map<std::string, Font*> fonts;
    std::vector<DebugElem> drawDebugElems;

public:
    /// \brief Singleton
    /// \return 
    static RenderEngine* GetInstanceRenderEngine();

    /// \brief Initialize everything the render needs such as the textures or openGL
    int Init();

    /// \brief Paints on screen the game
    /// \param timer 
    void UpdateRender(TimeManager& timer);

    /// \brief Un initialize everything that the render engine needs to un initialize
    void ShutDown();

    /// \brief It will Load a specified font of a specific size
    /// \param path 
    /// \return 
    Font* LoadFont(std::string path, float height, int size);

    /// \brief unloads the texture
    /// \param texture 
    void UnLoadFont(Font* texture);

    /// \brief It will look into the texture map if the texture searched has already been created. if it hasnt been created it will be loaded
    /// \param path 
    /// \return 
    ltex_t* LoadTexture(std::string path);

    /// \brief unloads the texture
    /// \param texture 
    void UnLoadTexture(ltex_t* texture);

    int GetScreenWidth();
    int GetScreenHeight();
    Vec2 GetScreenCenter();
    Vec2 GetScreenPos();
    void AddDebug(DebugElem elem);
    void DrawDebug();

    bool IsRectInScreen(const Vec2 spritePos, const Vec2& spriteSize);

private:
    std::map<int, std::vector<Entity*>> GetEntitiesInRenderOrder(std::vector<Entity*> entities);
};
