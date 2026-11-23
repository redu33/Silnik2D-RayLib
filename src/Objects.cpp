#include "Objects.h"

void ShapeObject::setColor(Color color) {
    this->color = color;
}

void BitmapObject::addBitmap(BitmapHandler *bitmap) {
    this->bitmaps.push_back(bitmap);
}

void BitmapObject::setCurrentBitmap(int index) {
    this->currentBitmap = index;
}

void BitmapObject::draw(PrimitiveRenderer &renderer) {
    if (!this->bitmaps.empty()) {
        this->bitmaps[this->currentBitmap]->draw(this->x, this->y, this->scale);
    }
}

void SpriteObject::animate() {
    if (this->bitmaps.empty()) {
        return;
    }

    this->frameCounter++;
    if (this->frameCounter >= this->frameDelay) {
        this->frameCounter = 0;
        this->currentBitmap = (this->currentBitmap + 1) % this->bitmaps.size();
    }
}