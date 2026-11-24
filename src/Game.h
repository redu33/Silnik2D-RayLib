#ifndef SILNK2D_GAME_H
#define SILNK2D_GAME_H

#include <vector>
#include "Shapes.h"
#include "Player.h"

class Engine;

struct SolidBox {
    RectangleShape shape;
    float x, y, w, h;

    SolidBox(float x, float y, float w, float h, Color color) : shape(Point2D(x, y), w, h, color) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }
};

struct Diamond {
    PolygonShape shape;
    float radius;
    bool collected = false;

    Diamond(const vector<Point2D> &pts, float r, Color color) : shape(pts, color), radius(r), collected(false) {}
};

class Game {
private:
    Player player = Player(400.0f, 300.0f, 350.0f, 3.0f);
    float screenWidth = 1280.0f;
    float screenHeight = 720.0f;

    vector<SolidBox> walls;
    vector<SolidBox> obstacles;
    SolidBox door = SolidBox(0.0f, 0.0f, 10.0f, 10.0f, MAROON);
    vector<Diamond> diamonds;

    bool doorOpen = false;
    int collectedCount = 0;

    float getPlayerWidth() const;
    float getPlayerHeight() const;
    bool collidesWithBox(float px, float py, float pw, float ph, const SolidBox &box) const;

public:
    bool init(int width, int height);
    void resetLevel();
    void handleInput(Engine &engine);
    void update(float dt);
    void draw(PrimitiveRenderer &renderer);
    void destroy();
};

#endif