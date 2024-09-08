#include "RenderEngine.h"
#include <glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "LogicManager.h"
#include "litegfx.h"
#define LITE_GFX_IMPLEMENTATION
#include "../Utils/Text/Font.h"
#include "stb_image.h"
#include "stb_truetype.h"
#include "../Entities/Entity.h"

RenderEngine* RenderEngine::renderInstance = nullptr;

RenderEngine* RenderEngine::GetInstanceRenderEngine()
{
    if (renderInstance == nullptr)
    {
        renderInstance = new RenderEngine();
    }
    return renderInstance;
}


int RenderEngine::Init()
{
    //initialize the GLFW library
    int initGlfw = glfwInit();
    if (initGlfw == 0) { return -1; }

    //create the window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WITH, WINDOW_HEIGHT, "The average shopping experience",
                                          nullptr/*en ventana*/, nullptr);
    glfwSetWindowSizeLimits(window, WINDOW_WITH, WINDOW_HEIGHT, WINDOW_WITH, WINDOW_HEIGHT);

    //associate OpenGl context with the window
    glfwMakeContextCurrent(window);

    // 4) Iniciamos la librería LiteGFX.
    lgfx_setup2d(WINDOW_WITH, WINDOW_HEIGHT);

    return 0;
}

void RenderEngine::UpdateRender(TimeManager& timer)
{
    GLFWwindow* window = glfwGetCurrentContext();

    //get the entities to render
    LogicManager* logicManagerInstance = LogicManager::GetInstanceLogicManager();
    std::map<int, std::vector<Entity*>> entities = logicManagerInstance->GetEntities();

    //  clear back buffer
    lgfx_clearcolorbuffer(0, 0, 0);

    //draw the entities in render order
    //maps iterate in order (in theory)
    for (const auto& kv : entities)
    {
        for (size_t i = 0; i < kv.second.size(); ++i)
        {
            //render
            kv.second[i]->RenderUpdate();
            //reset blending mode
            lgfx_setblend(BLEND_SOLID);
            //reset color
            lgfx_setcolor(1, 1, 1, 1);
        }
    }

    //draw debug
    DrawDebug();

    // Exchanges the front and back buffers
    glfwSwapBuffers(window);
}

void RenderEngine::ShutDown()
{
    //free textures
    for (const auto& tex : textures)
    {
        UnLoadTexture(tex.second);
    }
    //free fonts
    for (const auto& font : fonts)
    {
        UnLoadFont(font.second);
    }
    // End app.
    glfwTerminate();
}


Font* RenderEngine::LoadFont(std::string path, float height, const int size)
{
    //name
    char* buffer = new char[128];
    sprintf_s(buffer, 128, "%.2f", height);
    std::string name = "";
    name.append(path);
    name.append(buffer);
    delete[]buffer;
    buffer = nullptr;

    if (fonts.find(name) == fonts.end())
    {
        //file
        FILE* fontFile = nullptr;
        fopen_s(&fontFile, path.c_str(), "rb");
        //return null unable to read file
        if (fontFile == nullptr)
        {
            fclose(fontFile);
            return nullptr;
        }

        //get size
        fseek(fontFile, 0,SEEK_END);
        int fileSize = ftell(fontFile);
        fseek(fontFile, 0,SEEK_SET);

        //create buffer
        size_t fontBufferSize = sizeof(char) * fileSize;
        unsigned char* ttf_buffer = new unsigned char[fontBufferSize];
        fread(ttf_buffer, sizeof(char), fileSize, fontFile);
        fclose(fontFile);

        //render alpha buffer
        stbtt_bakedchar* cdata = new stbtt_bakedchar[96];

        unsigned char* alphaBuffer = new unsigned char [size * size];

        stbtt_BakeFontBitmap(ttf_buffer, 0, height, alphaBuffer, size, size, 32, 96, cdata);

        //create color buffer
        unsigned char* colorBuffer = new unsigned char [size * size * 4];
        for (int i = 0; i < size * size * 4; i++)
        {
            if (i % 4 == 3)
            {
                colorBuffer[i] = alphaBuffer[i / 4];
            }
            else
            {
                colorBuffer[i] = 255;
            }
        }

        //create texture
        ltex_t* tex = ltex_alloc(size, size, 0);

        //set pixels
        ltex_setpixels(tex, colorBuffer);
        Font* font = new Font(tex, cdata, height, Vec2(static_cast<float>(size), static_cast<float>(size)));
        fonts.insert_or_assign(name, font);

        //free buffers
        delete[] ttf_buffer;
        delete[] alphaBuffer;
        delete[] colorBuffer;

        return font;
    }
    return fonts[name];
}

void RenderEngine::UnLoadFont(Font* font)
{
    delete(font);
}

ltex_t* RenderEngine::LoadTexture(std::string path)
{
    //get the image buffer
    int width;
    int height;
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, nullptr, 4);
    if (data == nullptr)
    {
        return nullptr;
    }

    //get texture
    //not found
    if (textures.find(path) == textures.end())
    {
        //create texture
        ltex_t* tex = ltex_alloc(width, height, 0);
        //set pixels
        ltex_setpixels(tex, data);

        if (tex != nullptr)
        {
            textures.insert_or_assign(path, tex);
        }
        return tex;
    }
    //free buffer memory
    stbi_image_free(data);
    //found so it doesnt have to load again
    return textures[path];
}


void RenderEngine::UnLoadTexture(ltex_t* texture)
{
    ltex_free(texture);
}


int RenderEngine::GetScreenWidth()
{
    return WINDOW_WITH;
}

int RenderEngine::GetScreenHeight()
{
    return WINDOW_HEIGHT;
}

Vec2 RenderEngine::GetScreenCenter()
{
    return Vec2(static_cast<float>(WINDOW_WITH) / 2.f, static_cast<float>(WINDOW_HEIGHT) / 2.f);
}

Vec2 RenderEngine::GetScreenPos()
{
    GLFWwindow* window = glfwGetCurrentContext(); //window reference
    int x, y;
    glfwGetWindowPos(window, &x, &y);
    return Vec2(static_cast<float>(x), static_cast<float>(y));
}

void RenderEngine::AddDebug(DebugElem elem)
{
    drawDebugElems.push_back(elem);
}

void RenderEngine::DrawDebug()
{
    for (unsigned int i = 0; i < drawDebugElems.size(); ++i)
    {
        DebugElem elem = drawDebugElems[i];
        lgfx_setcolor(elem.m_color.R(), elem.m_color.G(), elem.m_color.B(), elem.m_color.A());
        switch (drawDebugElems[i].m_type)
        {
        case DebugType_SQUARE:
            lgfx_drawrect(elem.m_origin.x + elem.m_offset.x, elem.m_origin.y + elem.m_offset.y, elem.m_size.x,
                          elem.m_size.x);
            break;
        case DebugType_RECTANGLE:
            lgfx_drawrect(elem.m_origin.x + elem.m_offset.x, elem.m_origin.y + elem.m_offset.y, elem.m_size.x,
                          elem.m_size.y);
            break;
        case DebugType_POINT:
            lgfx_drawpoint(elem.m_origin.x, elem.m_origin.y);
            break;
        case DebugType_LINE:
            lgfx_drawline(elem.m_origin.x, elem.m_origin.y, elem.m_endPoint.x, elem.m_endPoint.y);
            break;
        case DebugType_CIRCLE:
            lgfx_drawoval(elem.m_origin.x, elem.m_origin.y, elem.m_size.x, elem.m_size.x);
            break;
        case DebugType_OVAL:
            lgfx_drawoval(elem.m_origin.x, elem.m_origin.y, elem.m_size.x, elem.m_size.y);
            break;
        case DebugType_NONE:
            break;
        }
    }
    //delete all elements
    drawDebugElems.clear();
}

bool RenderEngine::IsRectInScreen(const Vec2 spritePos, const Vec2& spriteSize)
{
    //screen
    float screenPositiveX = static_cast<float>(GetScreenWidth());
    float screenNegativeX = 0;
    float screenPositiveY = static_cast<float>(GetScreenHeight());
    float screenNegativeY = 0;
    //sprite
    float spritePositiveX = spritePos.x + spriteSize.x;
    float spriteNegativeX = spritePos.x;
    float spritePositiveY = spritePos.y + spriteSize.y;
    float spriteNegativeY = spritePos.y;

    return (screenPositiveX >= spriteNegativeX) &&
        (screenNegativeX <= spritePositiveX) &&
        (screenPositiveY >= spriteNegativeY) &&
        (screenNegativeY <= spritePositiveY);
}


std::map<int, std::vector<Entity*>> RenderEngine::GetEntitiesInRenderOrder(std::vector<Entity*> entities)
{
    std::map<int, std::vector<Entity*>> renderLayers;
    for (Entity* entity : entities)
    {
        int layer = entity->GetRenderLayer();
        renderLayers[layer].push_back(entity);
    }
    return renderLayers;
}
