#include "Primitives.h"
#include "Engine.h"
#include <math.h>
#include <stack>

using namespace std;

Point2D::Point2D(){
    this->x = 0.0f;
    this->y = 0.0f;
}
Point2D::Point2D(float x, float y) {
    this->x = x;
    this->y = y;
}
float Point2D::getX() const { return x; }
float Point2D::getY() const { return y; }
void Point2D::setX(float x) { this->x = x; }
void Point2D::setY(float y) { this->y = y; }
void Point2D::setXY(float x, float y) {
    this->x = x;
    this->y = y;
}
void Point2D::draw(PrimitiveRenderer &renderer, Color color) {
    renderer.drawPoint(*this, color);
}
void Point2D::translate(float tx, float ty) {
    this->x += tx;
    this->y += ty;
}
void Point2D::rotate(const Point2D &origin, float angleRad) {
    float x1 = this->x;
    float y1 = this->y;
    float x0 = origin.getX();
    float y0 = origin.getY();

    this->x = x0 + (x1 - x0) * cos(angleRad) - (y1 - y0) * sin(angleRad);
    this->y = y0 + (x1 - x0) * sin(angleRad) + (y1 - y0) * cos(angleRad);
}
void Point2D::scale(const Point2D &origin, float kx, float ky) {
    float x1 = this->x;
    float y1 = this->y;
    float x0 = origin.getX();
    float y0 = origin.getY();

    this->x = x1 * kx + (1.0f - kx) * x0;
    this->y = y1 * ky + (1.0f - ky) * y0;
}



void PrimitiveRenderer::drawPoint(Point2D p, Color color) {
    int x = (int)round(p.getX());
    int y = (int)round(p.getY());

    if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
        DrawPixel(x, y, color);
        pixelBuffer[x][y] = color;
    }
}
void PrimitiveRenderer::drawRectangle(Point2D p, int width, int height, Color color) {
    vector<Point2D> punkty = {
        Point2D(p.getX(), p.getY()),
        Point2D(p.getX() + width, p.getY()),
        Point2D(p.getX() + width, p.getY() + height),
        Point2D(p.getX(), p.getY() + height)
    };
    drawPolyline(punkty, color, true);
}
void PrimitiveRenderer::drawCircle(Point2D p, int R, Color color) {
    int x0 = (int)round(p.getX());
    int y0 = (int)round(p.getY());
    float step = 1.0f / R;

    for (float a = 0; a <= M_PI / 2.0f; a += step) {
        int x = R * cos(a) + 0.5f;
        int y = R * sin(a) + 0.5f;
        drawPoint(Point2D((float)(x0 + x), (float)(y0 + y)), color);
        drawPoint(Point2D((float)(x0 - x), (float)(y0 + y)), color);
        drawPoint(Point2D((float)(x0 + x), (float)(y0 - y)), color);
        drawPoint(Point2D((float)(x0 - x), (float)(y0 - y)), color);
    }
}
void PrimitiveRenderer::drawEllipse(Point2D p, int rx, int ry, Color color) {
    int x0 = (int)round(p.getX());
    int y0 = (int)round(p.getY());
    int maxR = max(abs(rx), abs(ry));

    float step = 1.0f / (maxR * 2.0f);

    for (float a = 0; a <= M_PI / 2.0f; a += step) {
        int x = rx * cos(a) + 0.5f;
        int y = ry * sin(a) + 0.5f;
        drawPoint(Point2D((float)(x0 + x), (float)(y0 + y)), color);
        drawPoint(Point2D((float)(x0 - x), (float)(y0 + y)), color);
        drawPoint(Point2D((float)(x0 + x), (float)(y0 - y)), color);
        drawPoint(Point2D((float)(x0 - x), (float)(y0 - y)), color);
    }
}
void PrimitiveRenderer::drawTriangle(Point2D p1, Point2D p2, Point2D p3, Color color) {
    vector<Point2D> punkty = {p1, p2, p3};
    drawPolyline(punkty, color, true);
}
void PrimitiveRenderer::drawPolygon(vector<Point2D> &points, Color color){
    if (points.size() < 3) {
        return;
    }
    drawPolyline(points, color, true);
}
void PrimitiveRenderer::drawLine(Point2D p1, Point2D p2, Color color) {
    int x1 = (int)round(p1.getX());
    int y1 = (int)round(p1.getY());
    int x2 = (int)round(p2.getX());
    int y2 = (int)round(p2.getY());

    int dx = x2 - x1;
    int dy = y2 - y1;

    if (abs(dx) >= abs(dy)) {
        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
            dx = x2 - x1;
            dy = y2 - y1;
        }
        if (dx == 0) {
            drawPoint(Point2D((float)x1, (float)y1), color);
            return;
        }
        float m = (float)dy / (float)dx;
        float y = (float)y1;

        for (int x = x1; x <= x2; x++) {
            drawPoint(Point2D((float)x, (float)(int)(y + 0.5f)), color);
            y += m;
        }
    } else {
        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
            dx = x2 - x1;
            dy = y2 - y1;
        }
        float m = (float)dx / (float)dy;
        float x = (float)x1;

        for (int y = y1; y <= y2; y++) {
            drawPoint(Point2D((float)(int)(x + 0.5f), (float)y), color);
            x += m;
        }
    }
}
void PrimitiveRenderer::drawPolyline(vector<Point2D> &points, Color color, bool isClosed) {
    if (points.size() < 2) {
        return;
    }
    for (int i = 0; i < points.size() - 1; i++) {
        drawLine(points[i], points[i + 1], color);
    }
    if (isClosed) {
        drawLine(points[points.size() - 1], points[0], color);
    }
}
void PrimitiveRenderer::initBuffer(int width, int height) {
    screenWidth = width;
    screenHeight = height;
    pixelBuffer.resize(screenWidth, vector<Color>(screenHeight, BLACK));
}
Color PrimitiveRenderer::getPixelColor(int x, int y) {
    if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
        return pixelBuffer[x][y];
    }
    return BLACK;
}
void PrimitiveRenderer::clearBuffer(Color clearColor) {
    for (int x = 0; x < screenWidth; x++) {
        for (int y = 0; y < screenHeight; y++) {
            pixelBuffer[x][y] = clearColor;
        }
    }
}
bool PrimitiveRenderer::areColorsEqual(Color c1, Color c2) {
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
}
void PrimitiveRenderer::boundaryFill(Point2D seed, Color fillColor, Color boundaryColor) {
    std::stack<Point2D> dsd;
    dsd.push(seed);
    while (!dsd.empty()) {
        Point2D p = dsd.top();
        dsd.pop();
        int x = (int)round(p.getX());
        int y = (int)round(p.getY());
        Color currentColor = getPixelColor(x, y);
        if (areColorsEqual(currentColor, fillColor) || areColorsEqual(currentColor, boundaryColor)) {
            continue;
        }
        drawPoint(p, fillColor);
        dsd.push(Point2D((float)x, (float)(y - 1)));
        dsd.push(Point2D((float)x, (float)(y + 1)));
        dsd.push(Point2D((float)(x - 1), (float)y));
        dsd.push(Point2D((float)(x + 1), (float)y));
    }
}



LineSegment::LineSegment(Point2D start, Point2D end) {
    this->start = start;
    this->end = end;
}
Point2D LineSegment::getStart() const { return start; }
Point2D LineSegment::getEnd() const { return end; }
void LineSegment::setStart(Point2D start) { this->start = start; }
void LineSegment::setEnd(Point2D end) { this->end = end; }
void LineSegment::draw(PrimitiveRenderer &renderer, Color color){
    renderer.drawLine(this->start, this->end, color);
}
void LineSegment::translate(float tx, float ty) {
    this->start.translate(tx, ty);
    this->end.translate(tx, ty);
}
void LineSegment::rotate(const Point2D& origin, float angleRad) {
    this->start.rotate(origin, angleRad);
    this->end.rotate(origin, angleRad);
}
void LineSegment::scale(const Point2D& origin, float kx, float ky) {
    this->start.scale(origin, kx, ky);
    this->end.scale(origin, kx, ky);
}