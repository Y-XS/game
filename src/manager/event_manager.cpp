#include "event_manager.h"


static SDL_AppResult HandleQuit();
// static SDL_AppResult HandleKeyUp();
// static SDL_AppResult HandleKeyDown();
// static SDL_AppResult HandleKeyLeft();
// static SDL_AppResult HandleKeyRight();


EventManager::EventManager() {
    m_evHandlerMap = {
        {SDLK_ESCAPE, HandleQuit},
        // {SDLK_UP, HandleKeyUp},
        // {SDLK_DOWN, HandleKeyDown},
        // {SDLK_LEFT, HandleKeyLeft},
        // {SDLK_RIGHT, HandleKeyRight},
    };
}

EventManager& EventManager::GetInstance() {
    static EventManager evm;
    return evm;
}

SDL_AppResult EventManager::HandleEvent(SDL_Event *event) {
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return HandleQuit();
        case SDL_EVENT_KEY_DOWN:
            if(m_evHandlerMap.count(event->key.key)<=0){
                return SDL_APP_CONTINUE;
            }
            return m_evHandlerMap[event->key.key]();
        default:
            return SDL_APP_CONTINUE;
    }
}

EventManager::~EventManager() {
    
}

static SDL_AppResult HandleQuit() {
    SDL_Log("HandleQuit.");
    Application::GetInstance().ShutDown();
    return SDL_APP_SUCCESS;
}

// static SDL_AppResult HandleKeyUp() {
//     auto p = RenderManager::GetInstance().getComponent("playerCompo");
//     if(p == nullptr){
//         SDL_Log("getComponent nullptr.");
//         return SDL_APP_CONTINUE;
//     }
//     Player* player = dynamic_cast<Player*>(p);
//     player->move(0,-1);
//     return SDL_APP_CONTINUE;
// }
// static SDL_AppResult HandleKeyDown() {
//     auto p = RenderManager::GetInstance().getComponent("playerCompo");
//     if(p == nullptr){
//         SDL_Log("getComponent nullptr.");
//         return SDL_APP_CONTINUE;
//     }
//     Player* player = dynamic_cast<Player*>(p);
//     player->move(0,1);
//     return SDL_APP_CONTINUE;
// }
// static SDL_AppResult HandleKeyLeft() {
//     auto p = RenderManager::GetInstance().getComponent("playerCompo");
//     if(p == nullptr){
//         SDL_Log("getComponent nullptr.");
//         return SDL_APP_CONTINUE;
//     }
//     Player* player = dynamic_cast<Player*>(p);
//     player->move(-1,0);
//     return SDL_APP_CONTINUE;
// }
// static SDL_AppResult HandleKeyRight() {
//     auto p = RenderManager::GetInstance().getComponent("playerCompo");
//     if(p == nullptr){
//         SDL_Log("getComponent nullptr.");
//         return SDL_APP_CONTINUE;
//     }
//     Player* player = dynamic_cast<Player*>(p);
//     player->move(1,0);
//     return SDL_APP_CONTINUE;
// }