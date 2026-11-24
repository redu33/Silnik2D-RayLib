#ifndef SILNK2D_OBJECTS_H
#define SILNK2D_OBJECTS_H

#include <raylib.h>
#include <vector>
#include "BitmapHandler.h"

using namespace std;

class PrimitiveRenderer;
class Point2D;

class GameObject {
public:
    virtual ~GameObject() = default;
};

class UpdateableObject : virtual public GameObject {
public:
    virtual void update(float dt) = 0;
};

class DrawableObject : virtual public GameObject {
public:
    virtual void draw(PrimitiveRenderer &renderer) = 0;
};

class TransformableObject : virtual public GameObject {
public:
    virtual void translate(float tx, float ty) = 0;
    virtual void rotate(const Point2D &origin, float angle) = 0;
    virtual void scale(const Point2D &origin, float kx, float ky) = 0;
};

class ShapeObject : public DrawableObject, public TransformableObject {
public:
    Color color;
    void setColor(Color color);
    virtual Point2D getCenter() const = 0;
};



class AnimatedObject : virtual public GameObject {
public:
    virtual void animate(float dt) = 0;
};

class BitmapObject : public DrawableObject {
public:
    vector<BitmapHandler*> bitmaps;
    int currentBitmap;
    float x;
    float y;
    float scale;
    void addBitmap(BitmapHandler *bitmap);
    void setCurrentBitmap(int index);
    void draw(PrimitiveRenderer &renderer) override;
};

class SpriteObject : public BitmapObject, public AnimatedObject {
public:
    float frameTime;
    float frameTimer;
    void animate(float dt) override;
};

#endif