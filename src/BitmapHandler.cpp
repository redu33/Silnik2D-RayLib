#include "BitmapHandler.h"

using namespace std;

BitmapHandler::BitmapHandler() {
    this->texture = {0};
}

void BitmapHandler::loadFromFile(string filename) {
    this->texture = LoadTexture(filename.c_str());
}

void BitmapHandler::destroy() {
    UnloadTexture(this->texture);
}

void BitmapHandler::draw(float x, float y, float scale) {
    DrawTextureEx(this->texture, {x, y}, 0.0f, scale, WHITE);
}

int BitmapHandler::getWidth() const {
    return this->texture.width;
}

int BitmapHandler::getHeight() const {
    return this->texture.height;
}