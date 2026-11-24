#ifndef SILNK2D_PLAYER_H
#define SILNK2D_PLAYER_H

#include "Objects.h"

class Player : public SpriteObject, public UpdateableObject {
private:
    float speed;
    BitmapHandler frame1;
    BitmapHandler frame2;

public:
    Player(float x, float y, float speed, float scale);
    ~Player();
    float dx;
    float dy;
    bool init();
    void update(float dt) override;
};

#endif