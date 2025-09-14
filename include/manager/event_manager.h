#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <SDL3/SDL.h>

#include <unordered_map>
#include <functional>

#include "manager.h"
#include "nocopy.h"
#include "application.h"

class EventManager : Manager, private NonCopyable  {
public:
    static EventManager& GetInstance();
    SDL_AppResult HandleEvent(SDL_Event *event);
private:
    EventManager();
    ~EventManager();

    std::unordered_map<Uint32, std::function<SDL_AppResult()>> m_evHandlerMap;
};


#endif