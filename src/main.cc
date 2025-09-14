/* snake.c ... */

/*
 * Logic implementation of the Snake game. It is designed to efficiently
 * represent the state of the game in memory.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

#define SDL_MAIN_USE_CALLBACKS /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <array>
#include <sstream>

#include "application.h"
#include "event_manager.h"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv){
    Application::GetInstance().Init();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate){
    if(!Application::GetInstance().getRunning()) {
        return SDL_APP_FAILURE;
    }
    return Application::GetInstance().Run();
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
    return EventManager::GetInstance().HandleEvent(event);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    Application::GetInstance().ShutDown();
}