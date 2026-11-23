#include "Player.h"

Player::Player(float x, float y, float speed, float scale) {
    this->x = x;
    this->y = y;
    this->scale = scale;
    this->speed = speed;
    this->currentBitmap = 0;
    this->frameDelay = 10;
    this->frameCounter = 0;
}

Player::~Player() {
    this->frame1.destroy();
    this->frame2.destroy();
}

void Player::init() {
    this->frame1.loadFromFile("player1.png");
    this->frame2.loadFromFile("player2.png");

    addBitmap(&this->frame1);
    addBitmap(&this->frame2);
}

void Player::update(float dt) {
    float dx = 0.0f;
    float dy = 0.0f;

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    dy -= 1.0f;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  dy += 1.0f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  dx -= 1.0f;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dx += 1.0f;

    if (dx != 0.0f || dy != 0.0f) {
        this->x += dx * this->speed * dt;
        this->y += dy * this->speed * dt;

        float spriteW = this->frame1.getWidth() * this->scale;
        float spriteH = this->frame1.getHeight() * this->scale;

        if (this->x < 0) this->x = 0;
        if (this->y < 0) this->y = 0;
        if (this->x > GetScreenWidth() - spriteW) {
            this->x = (float)GetScreenWidth() - spriteW;
        }
        if (this->y > GetScreenHeight() - spriteH) {
            this->y = (float)GetScreenHeight() - spriteH;
        }
        animate();
    } else {
        setCurrentBitmap(0);
    }
}