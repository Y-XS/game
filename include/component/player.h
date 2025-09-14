#ifndef PLAYER_H
#define PLAYER_H

#include "component.h"

#include "common_define.h"
#include "render_manager.h"

enum class MOVE_STATE{
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
};

class Player : public Component {
public:
    Player(Point);
    ~Player();
    void move(MOVE_STATE);
    void update() override;
    void render() override;

    Point getLoc();
    float getSpeed();
private:
    bool inWindow(int x, int y);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    float m_speed;
    SDL_Color m_color;
    SDL_FRect m_rect;
};


#endif