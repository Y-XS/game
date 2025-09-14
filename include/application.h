#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

#include "nocopy.h"
#include "window_manager.h"
#include "render_manager.h"

class Application : private NonCopyable {
public:
    static Application& GetInstance();

    bool Init();
    SDL_AppResult Run();
    void ShutDown();
    
    bool getRunning();
private:
    Application(){}
    ~Application(){}

    TTF_Font* m_font;
    bool m_running;
};


#endif