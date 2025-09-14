#ifndef COMPO_FRAME
#define COMPO_FRAME

#include "component.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <iomanip>
#include <sstream>

#include "render_manager.h"

class FrameComponent : public Component {
public:
    static const int avgFrameCnt = 60;
    FrameComponent();
    ~FrameComponent();
    void update() override;
    void render() override;

private:
    Uint64 m_lastFrameTime;
    Uint32 m_frameCnt;
    float m_avgFPS;
    std::string m_fpsStr;
    SDL_Color m_textColor;
    TTF_Font* m_font;
};

// struct FrameComponent {
//     uint32_t lastFrameTime;
//     uint32_t frameCount;
//     float avgFPS;
//     std::string fpsStr;
// };


#endif