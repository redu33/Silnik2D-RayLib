#ifndef SILNK2D_GAME_H
#define SILNK2D_GAME_H

#include <vector>
#include "Shapes.h"
#include "Player.h"

class Engine;

struct SolidBox {
    RectangleShape shape;
    float x, y, w, h;

    SolidBox(Point2D pos, float w, float h, Color color) : shape(pos, w, h, color) {
        this->x = pos.getX();
        this->y = pos.getY();
        this->w = w;
        this->h = h;
    }
};

struct Diamond {
    PolygonShape shape;
    float size;
    bool collected = false;

    Diamond(Point2D center, float size, Color color) : shape({
            Point2D(center.getX(), center.getY() - size),
            Point2D(center.getX() + size, center.getY()),
            Point2D(center.getX(), center.getY() + size),
            Point2D(center.getX() - size, center.getY())}, color) {
        this->size = size;
        collected = false;
    }
};

class Game {
private:
    Player player = Player(400.0f, 300.0f, 350.0f, 3.0f);
    float screenWidth = 1280.0f;
    float screenHeight = 720.0f;

    vector<SolidBox> walls;
    vector<SolidBox> obstacles;
    SolidBox door = SolidBox(Point2D(0.0f, 0.0f), 10.0f, 10.0f, RED);
    vector<Diamond> diamonds;

    bool doorOpen = false;
    int collectedCount = 0;

    float getPlayerWidth() const;
    float getPlayerHeight() const;
    bool collidesWithObject(float px, float py, float pw, float ph, const SolidBox &box) const;
    bool checkCollision(float testX, float testY) const;

public:
    bool init(int width, int height);
    void resetLevel();
    void handleInput(Engine &engine);
    void update(float dt);
    void draw(PrimitiveRenderer &renderer);
    void destroy();
};

#endif