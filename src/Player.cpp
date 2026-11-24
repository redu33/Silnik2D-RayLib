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
    frame1.destroy();
    frame2.destroy();
}

void Player::init() {
    frame1.loadFromFile("player1.png");
    frame2.loadFromFile("player2.png");

    addBitmap(&frame1);
    addBitmap(&frame2);
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