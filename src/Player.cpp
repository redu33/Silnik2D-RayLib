#include "Player.h"
#include <cmath>


Player::Player(float x, float y, float speed, float scale) {
    this->x = x;
    this->y = y;
    this->scale = scale;
    this->speed = speed;
    dx = 0.0f;
    dy = 0.0f;
    currentBitmap = 0;
    frameTime = 0.25f;
    frameTimer = 0.0f;
}

Player::~Player() {
    destroy();
}

bool Player::init() {
    frame1.loadFromFile("textures/player1.png");
    frame2.loadFromFile("textures/player2.png");

    if (frame1.getWidth() <= 0 || frame2.getWidth() <= 0) {
        return false;
    }

    addBitmap(&frame1);
    addBitmap(&frame2);
    return true;
}

void Player::update(float dt) {

    if (dx != 0.0f || dy != 0.0f) {
        float lenght = sqrt(dx * dx + dy * dy);
        x += (dx / lenght) * speed * dt;
        y += (dy / lenght) * speed * dt;

        float spriteW = frame1.getWidth() * scale;
        float spriteH = frame1.getHeight() * scale;

        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x > GetScreenWidth() - spriteW) {
            x = (float)GetScreenWidth() - spriteW;
        }
        if (y > GetScreenHeight() - spriteH) {
            y = (float)GetScreenHeight() - spriteH;
        }
        animate(dt);
    } else {
        setCurrentBitmap(0);
        frameTimer = 0.0f;
    }
}

void Player::destroy(){
    frame1.destroy();
    frame2.destroy();
}

int Player::getHeight() const{
    return frame1.getHeight();
}

int Player::getWidth() const{
    return frame1.getWidth();
}


