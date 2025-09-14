#include "frame_component.h"

FrameComponent::FrameComponent() : m_lastFrameTime(SDL_GetTicks()), m_frameCnt(0),
     m_avgFPS(0.0f), m_fpsStr("0.00"), m_textColor({255, 255, 255, 255}) {
    this->m_font = TTF_OpenFont("../res/TIMES.TTF", 24);
}

void FrameComponent::update() {
    ++m_frameCnt;
    if (m_frameCnt % avgFrameCnt == 0) {
        m_avgFPS = avgFrameCnt / ((SDL_GetTicks() - m_lastFrameTime) / 1000.0f);
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << m_avgFPS;
        m_fpsStr = ss.str();
        m_frameCnt = 0;
        m_lastFrameTime = SDL_GetTicks();
    }
}

void FrameComponent::render() {
    SDL_Surface *textSurface = TTF_RenderText_Blended(m_font, m_fpsStr.c_str(), m_fpsStr.length(), m_textColor);
    // 将Surface转换为Texture
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(RenderManager::GetInstance().getRender(), textSurface);
    float texW = 0, texH = 0;
    SDL_GetTextureSize(textTexture,&texW,&texH);
    // 设置目标渲染矩形
    SDL_FRect dstRect = {(float)200, (float)0, (float)texW, (float)texH}; // x, y为渲染位置
    // 渲染纹理
    SDL_RenderTexture(RenderManager::GetInstance().getRender(), textTexture, NULL, &dstRect);
    // 释放资源
    SDL_DestroySurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

FrameComponent::~FrameComponent(){
    
}
