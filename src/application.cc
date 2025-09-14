#include "application.h"


Application& Application::GetInstance() {
    static Application app;
    return app;
}

bool Application::Init(){
    SDL_Log("Application Init...");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_EVENTS);
    TTF_Init();
    SDL_SetAppMetadata("GGame", "1.0.0", "com.example.ggame");

    auto window = SDL_CreateWindow("GGame",500,500,0);
    WindowManager::GetInstance().addWindow(1, window);
    RenderManager::GetInstance().addRender(SDL_CreateRenderer(window,NULL));

    // this->m_font = TTF_OpenFont("../res/TIMES.TTF", 24);
    this->m_running = true;

    SDL_Log("Application Init done.");
    return true;
}

SDL_AppResult Application::Run(){
    //业务逻辑

    const bool* keystates = SDL_GetKeyboardState(NULL);

    auto p = RenderManager::GetInstance().getComponent("playerCompo");
    if(p == nullptr){
        SDL_Log("getComponent nullptr.");
        return SDL_APP_CONTINUE;
    }
    Player* player = dynamic_cast<Player*>(p);

    // 检查特定按键是否被按下
    if (keystates[SDL_SCANCODE_W]) {
        // 处理持续按下W键的动作
        player->move(MOVE_STATE::MOVE_UP);
    }
    if (keystates[SDL_SCANCODE_S]) {
        // 处理持续按下W键的动作
        player->move(MOVE_STATE::MOVE_DOWN);
    }
    if (keystates[SDL_SCANCODE_A]) {
        player->move(MOVE_STATE::MOVE_LEFT);
    }
    if (keystates[SDL_SCANCODE_D]) {
        player->move(MOVE_STATE::MOVE_RIGHT);
    }

    return RenderManager::GetInstance().render();
}

void Application::ShutDown(){
    SDL_Log("Application ShutDown...");
    m_running = false;
    RenderManager::GetInstance().shutDown();
    WindowManager::GetInstance().shutDown();
    TTF_CloseFont(m_font);
    TTF_Quit();
    SDL_Quit();
}

bool Application::getRunning() {
    return m_running;
}
