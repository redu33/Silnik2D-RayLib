#ifndef SILNK2D_OBJECTS_H
#define SILNK2D_OBJECTS_H

#include <raylib.h>
#include <vector>
#include "BitmapHandler.h"

using namespace std;

class PrimitiveRenderer;
class Point2D;

/**
 * @brief Bazowy typ dla obiektów w silniku.
 */
class GameObject {
public:
    /** @brief Wirtualny destruktor. */
    virtual ~GameObject() = default;
};

/**
 * @brief Interfejs dla obiektów aktualizowanych co klatkę.
 */
class UpdateableObject : virtual public GameObject {
public:
    /**
     * @brief Aktualizuje stan obiektu na podstawie czasu klatki dt.
     * @param dt Czas, który upłynął od poprzedniej klatki (w sekundach).
     */
    virtual void update(float dt) = 0;
};

/**
 * @brief Interfejs dla obiektów, które można narysować na ekranie.
 */
class DrawableObject : virtual public GameObject {
public:
    /**
     * @brief Rysuje obiekt przez podany renderer.
     * @param renderer Renderer używany do rysowania.
     */
    virtual void draw(PrimitiveRenderer &renderer) = 0;
};

/**
 * @brief Interfejs dla obiektów, które można przesuwać, obracać i skalować.
 */
class TransformableObject : virtual public GameObject {
public:
    /**
     * @brief Przesuwa obiekt o (tx, ty).
     * @param tx Przesunięcie w osi X.
     * @param ty Przesunięcie w osi Y.
     */
    virtual void translate(float tx, float ty) = 0;
    /**
     * @brief Obraca obiekt o podany kąt wokół punktu origin.
     * @param origin Punkt środka obrotu.
     * @param angle Kąt obrotu.
     */
    virtual void rotate(const Point2D &origin, float angle) = 0;
    /**
     * @brief Skaluje obiekt względem punktu origin o współczynniki kx i ky.
     * @param origin Punkt odniesienia dla skalowania.
     * @param kx Skala w osi X.
     * @param ky Skala w osi Y.
     */
    virtual void scale(const Point2D &origin, float kx, float ky) = 0;
};

/**
 * @brief Kształt, który ma swój kolor i środek, a do tego można go rysować i przekształcać.
 */
class ShapeObject : public DrawableObject, public TransformableObject {
public:
    /** @brief Kolor kształtu. */
    Color color;
    /**
     * @brief Ustawia kolor kształtu.
     * @param color Nowy kolor kształtu.
     */
    void setColor(Color color);
    /**
     * @brief Zwraca środek kształtu.
     * @return Punkt reprezentujący środek kształtu.
     */
    virtual Point2D getCenter() const = 0;
};


/**
 * @brief Interfejs dla obiektów obsługujących animację (wspólny bazowy GameObject przez dziedziczenie wirtualne).
 */
class AnimatedObject : virtual public GameObject {
public:
    /**
     * @brief Przesuwa animację do przodu o czas klatki dt.
     * @param dt Czas, który upłynął od poprzedniej klatki (w sekundach).
     */
    virtual void animate(float dt) = 0;
};

/**
 * @brief Obiekt rysowany na podstawie bitmap (z obsługą przełączania klatek/obrazków).
 */
class BitmapObject : public DrawableObject {
public:
    /** @brief Lista podpiętych bitmap. */
    vector<BitmapHandler*> bitmaps;
    /** @brief Indeks aktualnie używanej bitmapy. */
    int currentBitmap;
    /** @brief Pozycja X na ekranie. */
    float x;
    /** @brief Pozycja Y na ekranie. */
    float y;
    /** @brief Skala rysowania bitmapy. */
    float scale;
    /**
     * @brief Dodaje nową bitmapę do listy.
     * @param bitmap Wskaźnik do dodawanej bitmapy.
     */
    void addBitmap(BitmapHandler *bitmap);
    /**
     * @brief Przełącza aktywną bitmapę po jej indeksie.
     * @param index Indeks bitmapy na liście.
     */
    void setCurrentBitmap(int index);
    /**
     * @brief Rysuje aktualną bitmapę przez podany renderer.
     * @param renderer Renderer używany do rysowania.
     */
    void draw(PrimitiveRenderer &renderer) override;
};

/**
 * @brief Animowany obiekt oparty na bitmapach.
 */
class SpriteObject : public BitmapObject, public AnimatedObject {
public:
    /** @brief Ile trwa pojedyncza klatka animacji. */
    float frameTime;
    /** @brief Licznik czasu od zmiany klatki. */
    float frameTimer;
    /**
     * @brief Aktualizuje klatki animacji na podstawie czasu dt.
     * @param dt Czas, który upłynął od poprzedniej klatki (w sekundach).
     */
    void animate(float dt) override;
};

#endif