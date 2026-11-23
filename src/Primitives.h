#ifndef SILNK2D_PRIMITIVES_H
#define SILNK2D_PRIMITIVES_H
#include <raylib.h>
#include <vector>
#include "Objects.h"

using namespace std;

class PrimitiveRenderer;

class Point2D : public TransformableObject {
private:
    float x;
    float y;

public:
    Point2D();
    Point2D(float x, float y);

    float getX() const;
    float getY() const;

    void setX(float x);
    void setY(float y);
    void setXY(float x, float y);

    void draw(PrimitiveRenderer &renderer, Color color);

    void translate(float tx, float ty) override;
    void rotate(const Point2D &origin, float angleRad) override;
    void scale(const Point2D &origin, float kx, float ky) override;
};

class LineSegment : public TransformableObject {
private:
    Point2D start;
    Point2D end;

public:
    LineSegment(Point2D start, Point2D end);
    Point2D getStart() const;
    Point2D getEnd() const;
    void setStart(Point2D start);
    void setEnd(Point2D end);

    void draw(PrimitiveRenderer &renderer, Color color);

    void translate(float tx, float ty) override;
    void rotate(const Point2D &origin, float angleRad) override;
    void scale(const Point2D &origin, float kx, float ky) override;
};

class PrimitiveRenderer {
private:
    int screenWidth;
    int screenHeight;
    vector<vector<Color>> pixelBuffer;
public:
    void drawPoint(Point2D p, Color color);
    void drawRectangle(Point2D p, int width, int height, Color color);
    void drawCircle(Point2D p, int R, Color color);
    void drawEllipse(Point2D p, int rx, int ry, Color color);
    void drawTriangle(Point2D p1, Point2D p2, Point2D p3, Color color);
    void drawPolygon(vector<Point2D> &points, Color color);
    void drawLine(Point2D p1, Point2D p2, Color color);
    void drawPolyline(vector<Point2D> &points, Color color, bool isClosed);

    void initBuffer(int width, int height);
    Color getPixelColor(int x, int y);
    void clearBuffer(Color clearColor);
    bool areColorsEqual(Color c1, Color c2);
    void boundaryFill(Point2D seed, Color fillColor, Color boundryColor);
};

//
#endif