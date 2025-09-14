#include "window_manager.h"


WindowManager& WindowManager::GetInstance() {
    static WindowManager wm;
    return wm;
}

bool WindowManager::addWindow(uint32_t id, SDL_Window* window) {
    if (window == nullptr){
        return false;
    }
    if(this->windowMap.count(id) > 0){
        SDL_Log("window already exist.");
        return false;
    }
    auto retPair = this->windowMap.insert(std::make_pair(id, window));
    return retPair.second;
}

SDL_Window* WindowManager::getWindow(uint32_t id) {
    if(this->windowMap.count(id) <= 0){
        return nullptr;
    }
    return this->windowMap[id];
}

void WindowManager::shutDown() {
    for(auto& kv : windowMap){
        SDL_DestroyWindow(kv.second);
    }
    windowMap.clear();
}
