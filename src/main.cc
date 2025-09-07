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

// 定义方块结构
typedef struct {
    SDL_FRect rect;
    SDL_Color color;
    float speed;
} Square;

// 应用程序状态结构体（可选，用于在回调间传递数据）
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int running;
    Square square;
    Uint32 lastFrameTime;
    Uint32 frameCount;
    float avgFPS;
    char fpsText[64]; 
    TTF_Font* font;
} AppState;


SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv){
    SDL_Log("SDL_AppInit...");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_EVENTS);
    TTF_Init();
    SDL_SetAppMetadata("GGame", "1.0.0", "com.example.ggame");

    AppState* app_state = new AppState;
    *appstate = app_state;
    app_state->window = SDL_CreateWindow("GGame",500,500,0);
    app_state->renderer = SDL_CreateRenderer(app_state->window,NULL);

    // 初始化方块
    app_state->square.rect = (SDL_FRect){50, 200, 50, 50};  // x, y, width, height
    app_state->square.color = (SDL_Color){255, 100, 100, 255};  // 红色
    app_state->square.speed = 2.0f;  // 移动速度

    // 初始化变量
    app_state->lastFrameTime = SDL_GetTicks(); // 上一帧的时间戳（毫秒）
    app_state->frameCount = 0;                 // 帧计数器（用于计算平均FPS）
    app_state->avgFPS = 0.0f;                   // 平均FPS

    app_state->font = TTF_OpenFont("../res/TIMES.TTF",24);
    if (!app_state->font) {
        SDL_Log("Failed to load font: %s\n", SDL_GetError());
    }
    snprintf(app_state->fpsText, sizeof(app_state->fpsText), "FPS: %.2f", app_state->avgFPS);


    app_state->running = 1;

    return SDL_APP_CONTINUE;
}


void updateRect(AppState* app){
    // 更新方块位置
    app->square.rect.x += app->square.speed;

    int window_width;
    SDL_GetWindowSize(app->window, &window_width, NULL);
    if (app->square.rect.x > window_width) {
        app->square.rect.x = -app->square.rect.w;
    }
}

void calcFps(AppState* app){
    // 计算平均FPS - 每N帧计算一次平均值以平滑显示
    app->frameCount++;
    static const int avgFrameCount = 60; // 每60帧计算一次平均FPS
    if (app->frameCount % avgFrameCount == 0) {
        // 计算过去avgFrameCount帧的平均帧时间，然后求FPS
        app->avgFPS = avgFrameCount / ((SDL_GetTicks() - app->lastFrameTime) / 1000.0f);
        // 更新显示文本
        snprintf(app->fpsText, sizeof(app->fpsText), "FPS: %.2f", app->avgFPS);
        // 重置计数器和时间戳（用于下一次平均计算）
        app->frameCount = 0;
        app->lastFrameTime = SDL_GetTicks();
    }
}

SDL_AppResult SDL_AppIterate(void *appstate){
    AppState *app_state = (AppState*)appstate;

    // 如果运行标志为假，则请求退出
    if (!app_state->running) {
        return SDL_APP_FAILURE;
    }

    // 清屏
    SDL_SetRenderDrawColor(app_state->renderer, 30, 30, 30, 255);
    SDL_RenderClear(app_state->renderer);

    //绘制方块
    updateRect(app_state);
    SDL_SetRenderDrawColor(app_state->renderer, 
                          app_state->square.color.r, 
                          app_state->square.color.g, 
                          app_state->square.color.b, 
                          app_state->square.color.a);
    SDL_RenderFillRect(app_state->renderer, &app_state->square.rect);

    // 绘制fps
    calcFps(app_state);
    SDL_Color textColor = {255, 255, 255, 255}; 
    SDL_Surface *textSurface = TTF_RenderText_Blended(app_state->font, app_state->fpsText, strlen(app_state->fpsText), textColor);
    // 将Surface转换为Texture
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(app_state->renderer, textSurface);

    float texW = 0, texH = 0;
    SDL_GetTextureSize(textTexture,&texW,&texH);
    // 设置目标渲染矩形
    SDL_FRect dstRect = {(float)200, (float)0, (float)texW, (float)texH}; // x, y为渲染位置
    // 渲染纹理
    SDL_RenderTexture(app_state->renderer, textTexture, NULL, &dstRect);
    // 释放资源
    SDL_DestroySurface(textSurface);
    SDL_DestroyTexture(textTexture);


    // 呈现
    SDL_RenderPresent(app_state->renderer);

    // 添加少量延迟以减少 CPU 占用
    SDL_Delay(6); // 约 60 FPS

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
    AppState* app_state = (AppState*)appstate;

    switch(event->type){
        case SDL_EVENT_QUIT:
            SDL_Log("收到退出事件");
            app_state->running = 0;
            return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
            if(event->key.key == SDLK_ESCAPE){
                SDL_Log("按下 ESC 键，退出");
                app_state->running = 0;
                return SDL_APP_SUCCESS;
            }
            break;
        default:break;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result){
    AppState *app_state = (AppState*)appstate;
    SDL_Log("清理应用程序资源...");

    if (app_state) {
        if (app_state->renderer) {
            SDL_DestroyRenderer(app_state->renderer);
        }
        if (app_state->window) {
            SDL_DestroyWindow(app_state->window);
        }
        SDL_free(app_state);
    }
    TTF_CloseFont(app_state->font);
    TTF_Quit();
    SDL_Quit();
    SDL_Log("清理完成.");
}