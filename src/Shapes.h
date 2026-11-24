#ifndef SILNK2D_SHAPES_H
#define SILNK2D_SHAPES_H

#include "Primitives.h"

class TriangleShape : public ShapeObject {
private:
    Point2D p1, p2, p3;

public:
    TriangleShape(Point2D p1, Point2D p2, Point2D p3, Color color);

    Point2D getCenter() const override;
    void draw(PrimitiveRenderer &renderer) override;
    void translate(float tx, float ty) override;
    void rotate(const Point2D &origin, float angle) override;
    void scale(const Point2D &origin, float kx, float ky) override;
};

class RectangleShape : public ShapeObject {
private:
    Point2D p1, p2, p3, p4;

public:
    RectangleShape(Point2D p, float width, float height, Color color);

    Point2D getCenter() const override;
    void draw(PrimitiveRenderer &renderer) override;
    void translate(float tx, float ty) override;
    void rotate(const Point2D &origin, float angle) override;
    void scale(const Point2D &origin, float kx, float ky) override;
};

class CircleShape : public ShapeObject {
private:
    Point2D center;
    float radius;

public:
    CircleShape(Point2D center, float radius, Color color);

    Point2D getCenter() const override;
    void draw(PrimitiveRenderer &renderer) override;
    void translate(float tx, float ty) override;
    void rotate(const Point2D &origin, float angle) override;
    void scale(const Point2D &origin, float kx, float ky) override;
};

class EllipseShape : public ShapeObject {
private:
    Point2D center;
    float rx, ry;

public:
    EllipseShape(Point2D center, float rx, float ry, Color color);

    Point2D getCenter() const override;
    void draw(PrimitiveRenderer &renderer) override;
    void translate(float tx, float ty) override;
    void rotate(const Point2D &origin, float angle) override;
    void scale(const Point2D &origin, float kx, float ky) override;
};

class PolygonShape : public ShapeObject {
private:
    vector<Point2D> points;

public:
    PolygonShape(const vector<Point2D> &points, Color color);

    Point2D getCenter() const override;
    void draw(PrimitiveRenderer &renderer) override;
    void translate(float tx, float ty) override;
    void rotate(const Point2D &origin, float angle) override;
    void scale(const Point2D &origin, float kx, float ky) override;
};

class PolylineShape : public ShapeObject {
private:
    vector<Point2D> points;
    bool isClosed;

public:
    PolylineShape(const vector<Point2D> &points, Color color, bool isClosed);

    Point2D getCenter() const override;
    void draw(PrimitiveRenderer &renderer) override;
    void translate(float tx, float ty) override;
    void rotate(const Point2D &origin, float angle) override;
    void scale(const Point2D &origin, float kx, float ky) override;
};

#endif