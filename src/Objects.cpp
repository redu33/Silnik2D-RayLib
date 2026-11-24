#include "Objects.h"

void ShapeObject::setColor(Color color) {
    this->color = color;
}

void BitmapObject::addBitmap(BitmapHandler *bitmap) {
    bitmaps.push_back(bitmap);
}

void BitmapObject::setCurrentBitmap(int index) {
    currentBitmap = index;
}

void BitmapObject::draw(PrimitiveRenderer &renderer) {
    if (!bitmaps.empty()) {
        bitmaps[currentBitmap]->draw(x, y, scale);
    }
}

void SpriteObject::animate(float dt) {
    if (bitmaps.empty()) {
        return;
    }
    frameTimer += dt;
    if (frameTimer >= frameTime) {
        frameTimer = 0.0f;
        currentBitmap = (currentBitmap + 1) % bitmaps.size();
    }
}