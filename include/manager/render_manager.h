#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H


#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>

#include "nocopy.h"
#include "manager.h"
#include "component.h"
#include "frame_component.h"
#include "player.h"

class RenderManager : public Manager, private NonCopyable {
public:
    static RenderManager& GetInstance();
    void addRender(SDL_Renderer*);
    SDL_Renderer* getRender();
    void shutDown();
    SDL_AppResult render();

    Component* getComponent(std::string name);
private:
    RenderManager();
    ~RenderManager();

    SDL_Renderer* m_render;
    std::unordered_map<std::string, Component*> m_componentMap;
};


#endif