#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "nocopy.h"
#include "manager.h"
#include <unordered_map>
#include <cstdint>
#include <SDL3/SDL.h>


class WindowManager : public Manager, private NonCopyable{
public:
    static WindowManager& GetInstance();
    bool addWindow(uint32_t, SDL_Window*);
    SDL_Window* getWindow(uint32_t id);
    void shutDown();

private:
    WindowManager(){}
    ~WindowManager(){}
    std::unordered_map<uint32_t, SDL_Window*> windowMap;
};


#endif