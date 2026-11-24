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

struct SolidCircle {
    CircleShape shape;
    float x, y, radius;

    SolidCircle(Point2D center, float radius, Color color) : shape(center, radius, color) {
        this->x = center.getX();
        this->y = center.getY();
        this->radius = radius;
    }
};

struct Spike {
    TriangleShape shape;
    float x, y, size;

    Spike(Point2D center, float size, Color color) : shape(
            Point2D(center.getX(), center.getY() - size),
            Point2D(center.getX() - size, center.getY() + size),
            Point2D(center.getX() + size, center.getY() + size),
            color) {
        this->x = center.getX();
        this->y = center.getY();
        this->size = size;
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

    float margin = 25.0f;
    RectangleShape roomBorder = RectangleShape(Point2D(25.0f, 25.0f), 1230.0f, 670.0f, BLACK);
    vector<SolidBox> obstacles;
    vector<SolidCircle> pillars;
    vector<Spike> spikes;
    vector<Diamond> diamonds;

    SolidBox door = SolidBox(Point2D(0.0f, 0.0f), 10.0f, 10.0f, RED);
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