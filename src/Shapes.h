#ifndef SILNK2D_SHAPES_H
#define SILNK2D_SHAPES_H

#include "Primitives.h"

/**
 * @brief Trójkąt jako obiekt kształtu z obsługą rysowania i przekształceń.
 */
class TriangleShape : public ShapeObject {
private:
    /** @brief Trzy wierzchołki trójkąta. */
    Point2D p1, p2, p3;

public:
    /**
     * @brief Tworzy pusty trójkąt.
     */
    TriangleShape() = default;
    /**
     * @brief Tworzy trójkąt z trzech punktów i ustawia jego kolor.
     * @param p1 Pierwszy wierzchołek.
     * @param p2 Drugi wierzchołek.
     * @param p3 Trzeci wierzchołek.
     * @param color Kolor trójkąta.
     */
    TriangleShape(Point2D p1, Point2D p2, Point2D p3, Color color);

    /**
     * @brief Zwraca środek trójkąta.
     * @return Punkt środka trójkąta.
     */
    Point2D getCenter() const override;
    /**
     * @brief Rysuje trójkąt przez podany renderer.
     * @param renderer Renderer używany do rysowania.
     */
    void draw(PrimitiveRenderer &renderer) override;
    /**
     * @brief Przesuwa trójkąt o (tx, ty).
     * @param tx Przesunięcie w osi X.
     * @param ty Przesunięcie w osi Y.
     */
    void translate(float tx, float ty) override;
    /**
     * @brief Obraca trójkąt o podany kąt wokół punktu origin.
     * @param origin Punkt środka obrotu.
     * @param angle Kąt obrotu.
     */
    void rotate(const Point2D &origin, float angle) override;
    /**
     * @brief Skaluje trójkąt względem punktu origin o współczynniki kx i ky.
     * @param origin Punkt odniesienia dla skalowania.
     * @param kx Skala w osi X.
     * @param ky Skala w osi Y.
     */
    void scale(const Point2D &origin, float kx, float ky) override;
};

/**
 * @brief Prostokąt jako obiekt kształtu z obsługą rysowania i przekształceń.
 */
class RectangleShape : public ShapeObject {
private:
    /** @brief Cztery rogi prostokąta. */
    Point2D p1, p2, p3, p4;

public:
    /**
     * @brief Tworzy pusty prostokąt.
     */
    RectangleShape() = default;
    /**
     * @brief Tworzy prostokąt od punktu p o podanej szerokości i wysokości oraz danym kolorze.
     * @param p Pozycja lewego górnego rogu.
     * @param width Szerokość prostokąta.
     * @param height Wysokość prostokąta.
     * @param color Kolor prostokąta.
     */
    RectangleShape(Point2D p, float width, float height, Color color);

    /**
     * @brief Zwraca środek prostokąta.
     * @return Punkt środka prostokąta.
     */
    Point2D getCenter() const override;
    /**
     * @brief Rysuje prostokąt przez podany renderer.
     * @param renderer Renderer używany do rysowania.
     */
    void draw(PrimitiveRenderer &renderer) override;
    /**
     * @brief Przesuwa prostokąt o (tx, ty).
     * @param tx Przesunięcie w osi X.
     * @param ty Przesunięcie w osi Y.
     */
    void translate(float tx, float ty) override;
    /**
     * @brief Obraca prostokąt o podany kąt wokół punktu origin.
     * @param origin Punkt środka obrotu.
     * @param angle Kąt obrotu.
     */
    void rotate(const Point2D &origin, float angle) override;
    /**
     * @brief Skaluje prostokąt względem punktu origin o współczynniki kx i ky.
     * @param origin Punkt odniesienia dla skalowania.
     * @param kx Skala w osi X.
     * @param ky Skala w osi Y.
     */
    void scale(const Point2D &origin, float kx, float ky) override;
};

/**
 * @brief Okrąg jako obiekt kształtu określony przez środek i promień.
 */
class CircleShape : public ShapeObject {
private:
    /** @brief Środek okręgu. */
    Point2D center;
    /** @brief Promień okręgu. */
    float radius;

public:
    /**
     * @brief Tworzy okrąg o podanym środku, promieniu i kolorze.
     * @param center Środek okręgu.
     * @param radius Promień okręgu.
     * @param color Kolor okręgu.
     */
    CircleShape(Point2D center, float radius, Color color);

    /**
     * @brief Zwraca środek okręgu.
     * @return Punkt środka okręgu.
     */
    Point2D getCenter() const override;
    /**
     * @brief Rysuje okrąg przez podany renderer.
     * @param renderer Renderer używany do rysowania.
     */
    void draw(PrimitiveRenderer &renderer) override;
    /**
     * @brief Przesuwa okrąg o (tx, ty).
     * @param tx Przesunięcie w osi X.
     * @param ty Przesunięcie w osi Y.
     */
    void translate(float tx, float ty) override;
    /**
     * @brief Obraca okrąg o podany kąt wokół punktu origin.
     * @param origin Punkt środka obrotu.
     * @param angle Kąt obrotu.
     */
    void rotate(const Point2D &origin, float angle) override;
    /**
     * @brief Skaluje okrąg względem punktu origin o współczynniki kx i ky.
     * @param origin Punkt odniesienia dla skalowania.
     * @param kx Skala w osi X.
     * @param ky Skala w osi Y.
     */
    void scale(const Point2D &origin, float kx, float ky) override;
};

/**
 * @brief Elipsa określona przez środek i dwa promienie.
 */
class EllipseShape : public ShapeObject {
private:
    /** @brief Środek elipsy. */
    Point2D center;
    /** @brief Promienie w osi X i Y. */
    float rx, ry;

public:
    /**
     * @brief Tworzy elipsę o podanym środku, promieniach rx, ry i kolorze.
     * @param center Środek elipsy.
     * @param rx Promień (półoś) w osi X.
     * @param ry Promień (półoś) w osi Y.
     * @param color Kolor elipsy.
     */
    EllipseShape(Point2D center, float rx, float ry, Color color);

    /**
     * @brief Zwraca środek elipsy.
     * @return Punkt środka elipsy.
     */
    Point2D getCenter() const override;
    /**
     * @brief Rysuje elipsę przez podany renderer.
     * @param renderer Renderer używany do rysowania.
     */
    void draw(PrimitiveRenderer &renderer) override;
    /**
     * @brief Przesuwa elipsę o (tx, ty).
     * @param tx Przesunięcie w osi X.
     * @param ty Przesunięcie w osi Y.
     */
    void translate(float tx, float ty) override;
    /**
     * @brief Obraca elipsę o podany kąt wokół punktu origin.
     * @param origin Punkt środka obrotu.
     * @param angle Kąt obrotu.
     */
    void rotate(const Point2D &origin, float angle) override;
    /**
     * @brief Skaluje elipsę względem punktu origin o współczynniki kx i ky.
     * @param origin Punkt odniesienia dla skalowania.
     * @param kx Skala w osi X.
     * @param ky Skala w osi Y.
     */
    void scale(const Point2D &origin, float kx, float ky) override;
};

/**
 * @brief Wielokąt zbudowany z listy punktów.
 */
class PolygonShape : public ShapeObject {
private:
    /** @brief Kolejne wierzchołki wielokąta. */
    vector<Point2D> points;

public:
    /**
     * @brief Tworzy wielokąt z listy punktów i ustawia kolor.
     * @param points Lista wierzchołków wielokąta.
     * @param color Kolor wielokąta.
     */
    PolygonShape(const vector<Point2D> &points, Color color);

    /**
     * @brief Zwraca środek wielokąta.
     * @return Punkt środka wielokąta.
     */
    Point2D getCenter() const override;
    /**
     * @brief Rysuje wielokąt przez podany renderer.
     * @param renderer Renderer używany do rysowania.
     */
    void draw(PrimitiveRenderer &renderer) override;
    /**
     * @brief Przesuwa wielokąt o (tx, ty).
     * @param tx Przesunięcie w osi X.
     * @param ty Przesunięcie w osi Y.
     */
    void translate(float tx, float ty) override;
    /**
     * @brief Obraca wielokąt o podany kąt wokół punktu origin.
     * @param origin Punkt środka obrotu.
     * @param angle Kąt obrotu.
     */
    void rotate(const Point2D &origin, float angle) override;
    /**
     * @brief Skaluje wielokąt względem punktu origin o współczynniki kx i ky.
     * @param origin Punkt odniesienia dla skalowania.
     * @param kx Skala w osi X.
     * @param ky Skala w osi Y.
     */
    void scale(const Point2D &origin, float kx, float ky) override;
};

/**
 * @brief Łamana z punktów, która może być otwarta albo zamknięta.
 */
class PolylineShape : public ShapeObject {
private:
    /** @brief Punkty tworzące łamaną. */
    vector<Point2D> points;
    /** @brief Czy koniec łączy się z początkiem. */
    bool isClosed;

public:
    /**
     * @brief Tworzy łamaną z podanych punktów, koloru i informacji o zamknięciu.
     * @param points Lista punktów łamanej.
     * @param color Kolor linii.
     * @param isClosed Czy połączyć ostatni punkt z pierwszym.
     */
    PolylineShape(const vector<Point2D> &points, Color color, bool isClosed);

    /**
     * @brief Zwraca środek łamanej.
     * @return Punkt środka łamanej.
     */
    Point2D getCenter() const override;
    /**
     * @brief Rysuje łamaną przez podany renderer.
     * @param renderer Renderer używany do rysowania.
     */
    void draw(PrimitiveRenderer &renderer) override;
    /**
     * @brief Przesuwa łamaną o (tx, ty).
     * @param tx Przesunięcie w osi X.
     * @param ty Przesunięcie w osi Y.
     */
    void translate(float tx, float ty) override;
    /**
     * @brief Obraca łamaną o podany kąt wokół punktu origin.
     * @param origin Punkt środka obrotu.
     * @param angle Kąt obrotu.
     */
    void rotate(const Point2D &origin, float angle) override;
    /**
     * @brief Skaluje łamaną względem punktu origin o współczynniki kx i ky.
     * @param origin Punkt odniesienia dla skalowania.
     * @param kx Skala w osi X.
     * @param ky Skala w osi Y.
     */
    void scale(const Point2D &origin, float kx, float ky) override;
};

#endif