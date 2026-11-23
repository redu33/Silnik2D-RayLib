#ifndef SILNK2D_GAMEOBJECT_H
#define SILNK2D_GAMEOBJECT_H

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

};

//

#endif