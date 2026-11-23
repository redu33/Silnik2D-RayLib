#include "Shapes.h"
#include <math.h>

TriangleShape::TriangleShape(Point2D p1, Point2D p2, Point2D p3, Color color) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->color = color;
}
Point2D TriangleShape::getCenter() const {
    return Point2D(
        (p1.getX() + p2.getX() + p3.getX()) / 3.0f,
        (p1.getY() + p2.getY() + p3.getY()) / 3.0f
    );
}
void TriangleShape::draw(PrimitiveRenderer &renderer) {
    renderer.drawTriangle(p1, p2, p3, color);
}
void TriangleShape::translate(float tx, float ty) {
    p1.translate(tx, ty);
    p2.translate(tx, ty);
    p3.translate(tx, ty);
}
void TriangleShape::rotate(const Point2D &origin, float angleRad) {
    p1.rotate(origin, angleRad);
    p2.rotate(origin, angleRad);
    p3.rotate(origin, angleRad);
}
void TriangleShape::scale(const Point2D &origin, float kx, float ky) {
    p1.scale(origin, kx, ky);
    p2.scale(origin, kx, ky);
    p3.scale(origin, kx, ky);
}



RectangleShape::RectangleShape(Point2D p, float width, float height, Color color) {
    this->p1 = p;
    this->p2 = Point2D(p.getX() + width, p.getY());
    this->p3 = Point2D(p.getX() + width, p.getY() + height);
    this->p4 = Point2D(p.getX(), p.getY() + height);
    this->color = color;
}
Point2D RectangleShape::getCenter() const {
    return Point2D(
        (p1.getX() + p2.getX() + p3.getX() + p4.getX()) / 4.0f,
        (p1.getY() + p2.getY() + p3.getY() + p4.getY()) / 4.0f
    );
}
void RectangleShape::draw(PrimitiveRenderer &renderer) {
    vector<Point2D> punkty = {p1, p2, p3, p4};
    renderer.drawPolygon(punkty, color);
}
void RectangleShape::translate(float tx, float ty) {
    p1.translate(tx, ty);
    p2.translate(tx, ty);
    p3.translate(tx, ty);
    p4.translate(tx, ty);
}
void RectangleShape::rotate(const Point2D &origin, float angleRad) {
    p1.rotate(origin, angleRad);
    p2.rotate(origin, angleRad);
    p3.rotate(origin, angleRad);
    p4.rotate(origin, angleRad);
}
void RectangleShape::scale(const Point2D &origin, float kx, float ky) {
    p1.scale(origin, kx, ky);
    p2.scale(origin, kx, ky);
    p3.scale(origin, kx, ky);
    p4.scale(origin, kx, ky);
}



CircleShape::CircleShape(Point2D center, float radius, Color color) {
    this->center = center;
    this->radius = radius;
    this->color = color;
}
Point2D CircleShape::getCenter() const {
    return center;
}
void CircleShape::draw(PrimitiveRenderer &renderer) {
    renderer.drawCircle(center, (int)round(radius), color);
}
void CircleShape::translate(float tx, float ty) {
    center.translate(tx, ty);
}
void CircleShape::rotate(const Point2D &origin, float angleRad){
    center.rotate(origin, angleRad);
}
void CircleShape::scale(const Point2D &origin, float kx, float ky) {
    center.scale(origin, kx, ky);
    radius *= kx;
}



EllipseShape::EllipseShape(Point2D center, float rx, float ry, Color color) {
    this->center = center;
    this->rx = rx;
    this->ry = ry;
    this->color = color;
}
Point2D EllipseShape::getCenter() const {
    return center;
}
void EllipseShape::draw(PrimitiveRenderer &renderer) {
    renderer.drawEllipse(center, (int)round(rx), (int)round(ry), color);
}
void EllipseShape::translate(float tx, float ty) {
    center.translate(tx, ty);
}
void EllipseShape::rotate(const Point2D &origin, float angleRad) {
    center.rotate(origin, angleRad);
}
void EllipseShape::scale(const Point2D &origin, float kx, float ky) {
    center.scale(origin, kx, ky);
    rx *= kx;
    ry *= ky;
}



PolygonShape::PolygonShape(const vector<Point2D> &points, Color color) {
    this->points = points;
    this->color = color;
}
Point2D PolygonShape::getCenter() const {
    if (points.empty()) return Point2D(0.0f, 0.0f);
    float sumX = 0.0f, sumY = 0.0f;
    for (int i = 0; i < points.size(); i++) {
        sumX += points[i].getX();
        sumY += points[i].getY();
    }
    return Point2D(sumX / points.size(), sumY / points.size());
}
void PolygonShape::draw(PrimitiveRenderer &renderer) {
    renderer.drawPolygon(points, color);
}
void PolygonShape::translate(float tx, float ty) {
    for (int i = 0; i < points.size(); i++) {
        points[i].translate(tx, ty);
    }
}
void PolygonShape::rotate(const Point2D &origin, float angleRad) {
    for (int i = 0; i < points.size(); i++) {
        points[i].rotate(origin, angleRad);
    }
}
void PolygonShape::scale(const Point2D &origin, float kx, float ky) {
    for (int i = 0; i < points.size(); i++) {
        points[i].scale(origin, kx, ky);
    }
}



PolylineShape::PolylineShape(const vector<Point2D> &points, Color color, bool isClosed)  {
    this->points = points;
    this->color = color;
    this->isClosed = isClosed;
}
Point2D PolylineShape::getCenter() const {
    if (points.empty()) return Point2D(0.0f, 0.0f);
    float sumX = 0.0f, sumY = 0.0f;
    for (int i = 0; i < points.size(); i++) {
        sumX += points[i].getX();
        sumY += points[i].getY();
    }
    return Point2D(sumX / points.size(), sumY / points.size());
}
void PolylineShape::draw(PrimitiveRenderer &renderer) {
    renderer.drawPolyline(points, color, isClosed);
}
void PolylineShape::translate(float tx, float ty) {
    for (int i = 0; i < points.size(); i++) {
        points[i].translate(tx, ty);
    }
}
void PolylineShape::rotate(const Point2D &origin, float angleRad) {
    for (int i = 0; i < points.size(); i++) {
        points[i].rotate(origin, angleRad);
    }
}
void PolylineShape::scale(const Point2D &origin, float kx, float ky) {
    for (int i = 0; i < points.size(); i++) {
        points[i].scale(origin, kx, ky);
    }
}