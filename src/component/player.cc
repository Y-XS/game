#include "player.h"

Player::Player(Point point) : m_speed(5), m_color{255, 100, 100, 255},
    m_rect{point.x, point.y, 50, 50} {
}

void Player::move(MOVE_STATE state){
    switch(state){
        case MOVE_STATE::MOVE_UP:
            moveUp();
            break;
        case MOVE_STATE::MOVE_DOWN:
            moveDown();
            break;
        case MOVE_STATE::MOVE_LEFT:
            moveLeft();
            break;
        case MOVE_STATE::MOVE_RIGHT:
            moveRight();
            break;
        default:
            return;  
    }

}
void Player::update() {

}

void Player::render() {
    SDL_SetRenderDrawColor(RenderManager::GetInstance().getRender(), 
        m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(RenderManager::GetInstance().getRender(), &m_rect);
}

Point Player::getLoc() {
    return {m_rect.x,m_rect.y};
}
float Player::getSpeed() {
    return m_speed;
}

bool Player::inWindow(int x, int y){
    return x>=0 && x<=450 && y>=0 && y<=450;
}

void Player::moveUp(){
    float afterY = m_rect.y - m_speed;
    if(afterY<0 || afterY>=450){
        m_rect.y = afterY < 0 ? 0 : 450;
        return;
    }
    m_rect.y = afterY;
}
void Player::moveDown(){
    float afterY = m_rect.y + m_speed;
    if(afterY<0 || afterY>=450){
        m_rect.y = afterY < 0 ? 0 : 450;
        return;
    }
    m_rect.y = afterY;
}
void Player::moveLeft(){
    float afterX = m_rect.x - m_speed;
    if(afterX<0 || afterX>=450){
        m_rect.x = afterX < 0 ? 0 : 450;
        return;
    }
    m_rect.x = afterX;
}
void Player::moveRight(){
    float afterX = m_rect.x + m_speed;
    if(afterX<0 || afterX>=450){
        m_rect.x = afterX < 0 ? 0 : 450;
        return;
    }
    m_rect.x = afterX;
}

Player::~Player() {

}