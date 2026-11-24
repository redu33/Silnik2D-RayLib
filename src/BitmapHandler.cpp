#include "BitmapHandler.h"

using namespace std;

BitmapHandler::BitmapHandler() {
    texture = {0};
}

void BitmapHandler::loadFromFile(string filename) {
    texture = LoadTexture(filename.c_str());
}

void BitmapHandler::destroy() {
    if (texture.id != 0) {
        UnloadTexture(texture);
        texture.id = 0;
    }
}

void BitmapHandler::draw(float x, float y, float scale) {
    DrawTextureEx(texture, {x, y}, 0.0f, scale, WHITE);
}

int BitmapHandler::getWidth() const {
    return texture.width;
}

int BitmapHandler::getHeight() const {
    return texture.height;
}