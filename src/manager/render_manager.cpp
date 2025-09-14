#include "render_manager.h"


RenderManager::RenderManager() {

    this->m_componentMap.emplace("frameCompo", new FrameComponent());
    this->m_componentMap.emplace("playerCompo", new Player({100, 100}));
}

RenderManager& RenderManager::GetInstance() {
    static RenderManager rm;
    return rm;
}

void RenderManager::addRender(SDL_Renderer* render) {
    this->m_render = render;
}
SDL_Renderer* RenderManager::getRender() {
    return this->m_render;
}
Component* RenderManager::getComponent(std::string name) {
    if(m_componentMap.count(name) <= 0){
        return nullptr;
    }
    return m_componentMap[name];
}

SDL_AppResult RenderManager::render() {
    // 清屏
    SDL_SetRenderDrawColor(m_render, 30, 30, 30, 255);
    SDL_RenderClear(m_render);

    for(auto kv : m_componentMap){
        kv.second->update();
        kv.second->render();
    }
    SDL_RenderPresent(m_render);
    // SDL_Delay(1000); // 约 60 FPS
    SDL_Delay(12); // 约 60 FPS
    return SDL_APP_CONTINUE;
}

void RenderManager::shutDown() {
    if(m_render){
        SDL_DestroyRenderer(m_render);
    }
}

RenderManager::~RenderManager() {
    
}