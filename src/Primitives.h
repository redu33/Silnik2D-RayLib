#ifndef SILNK2D_PRIMITIVES_H
#define SILNK2D_PRIMITIVES_H
#include <raylib.h>
#include <vector>
#include "Objects.h"

using namespace std;

class PrimitiveRenderer;

/**
 * @brief Punkt 2D, który można przesuwać, obracać i skalować.
 */
class Point2D : public TransformableObject {
private:
    /** @brief Współrzędna X. */
    float x;
    /** @brief Współrzędna Y. */
    float y;

public:
    /**
     * @brief Tworzy punkt w (0, 0).
     */
    Point2D();
    /**
     * @brief Tworzy punkt we wskazanych współrzędnych.
     * @param x Pozycja X.
     * @param y Pozycja Y.
     */
    Point2D(float x, float y);

    /**
     * @brief Zwraca współrzędną X.
     * @return Współrzędna X punktu.
     */
    float getX() const;
    /**
     * @brief Zwraca współrzędną Y.
     * @return Współrzędna Y punktu.
     */
    float getY() const;

    /**
     * @brief Ustawia współrzędną X.
     * @param x Nowa współrzędna X.
     */
    void setX(float x);
    /**
     * @brief Ustawia współrzędną Y.
     * @param y Nowa współrzędna Y.
     */
    void setY(float y);
    /**
     * @brief Ustawia od razu obie współrzędne.
     * @param x Nowa współrzędna X.
     * @param y Nowa współrzędna Y.
     */
    void setXY(float x, float y);
    /**
     * @brief Rysuje punkt przez podany renderer.
     * @param renderer Renderer używany do rysowania.
     * @param color Kolor punktu.
     */
    void draw(PrimitiveRenderer &renderer, Color color);

    /**
     * @brief Przesuwa punkt o (tx, ty).
     * @param tx Przesunięcie w osi X.
     * @param ty Przesunięcie w osi Y.
     */
    void translate(float tx, float ty) override;
    /**
     * @brief Obraca punkt wokół origin o dany kąt.
     * @param origin Punkt środka obrotu.
     * @param angle Kąt obrotu.
     */
    void rotate(const Point2D &origin, float angle) override;
    /**
     * @brief Skaluje punkt względem origin o współczynniki kx i ky.
     * @param origin Punkt odniesienia dla skalowania.
     * @param kx Skala w osi X.
     * @param ky Skala w osi Y.
     */
    void scale(const Point2D &origin, float kx, float ky) override;
};

/**
 * @brief Odcinek między dwoma punktami 2D z obsługą transformacji.
 */
class LineSegment : public TransformableObject {
private:
    /** @brief Początek odcinka. */
    Point2D start;
    /** @brief Koniec odcinka. */
    Point2D end;

public:
    /**
     * @brief Tworzy odcinek od start do end.
     * @param start Punkt początkowy.
     * @param end Punkt końcowy.
     */
    LineSegment(Point2D start, Point2D end);
    /**
     * @brief Zwraca punkt początkowy.
     * @return Punkt początkowy odcinka.
     */
    Point2D getStart() const;
    /**
     * @brief Zwraca punkt końcowy.
     * @return Punkt końcowy odcinka.
     */
    Point2D getEnd() const;
    /**
     * @brief Zmienia punkt początkowy.
     * @param start Nowy punkt początkowy.
     */
    void setStart(Point2D start);
    /**
     * @brief Zmienia punkt końcowy.
     * @param end Nowy punkt końcowy.
     */
    void setEnd(Point2D end);

    /**
     * @brief Rysuje odcinek przez podany renderer.
     * @param renderer Renderer używany do rysowania.
     * @param color Kolor odcinka.
     */
    void draw(PrimitiveRenderer &renderer, Color color);

    /**
     * @brief Przesuwa cały odcinek o (tx, ty).
     * @param tx Przesunięcie w osi X.
     * @param ty Przesunięcie w osi Y.
     */
    void translate(float tx, float ty) override;
    /**
     * @brief Obraca odcinek wokół origin o dany kąt.
     * @param origin Punkt środka obrotu.
     * @param angle Kąt obrotu.
     */
    void rotate(const Point2D &origin, float angle) override;
    /**
     * @brief Skaluje odcinek względem origin o kx i ky.
     * @param origin Punkt odniesienia dla skalowania.
     * @param kx Skala w osi X.
     * @param ky Skala w osi Y.
     */
    void scale(const Point2D &origin, float kx, float ky) override;
};

/**
 * @brief Rysuje kształty na ekranie i zapisuje do bufora.
 */
class PrimitiveRenderer {
private:
    /** @brief Szerokość bufora w pikselach. */
    int screenWidth = 0;
    /** @brief Wysokość bufora w pikselach. */
    int screenHeight = 0;
    /** @brief Siatka pikseli ekranu. */
    vector<vector<Color>> pixelBuffer;
public:
    /**
     * @brief Rysuje pojedynczy punkt w podanym kolorze.
     * @param p Pozycja punktu.
     * @param color Kolor punktu.
     */
    void drawPoint(Point2D p, Color color);
    /**
     * @brief Rysuje prostokąt o podanych wymiarach i kolorze.
     * @param p Pozycja lewego górnego rogu.
     * @param width Szerokość prostokąta.
     * @param height Wysokość prostokąta.
     * @param color Kolor prostokąta.
     */
    void drawRectangle(Point2D p, int width, int height, Color color);
    /**
     * @brief Rysuje okrąg o promieniu R w podanym kolorze.
     * @param p Środek okręgu.
     * @param R Promień okręgu.
     * @param color Kolor okręgu.
     */
    void drawCircle(Point2D p, int R, Color color);
    /**
     * @brief Rysuje elipsę o półosiach rx i ry w podanym kolorze.
     * @param p Środek elipsy.
     * @param rx Półoś w osi X.
     * @param ry Półoś w osi Y.
     * @param color Kolor elipsy.
     */
    void drawEllipse(Point2D p, int rx, int ry, Color color);
    /**
     * @brief Rysuje trójkąt z trzech punktów w podanym kolorze.
     * @param p1 Pierwszy wierzchołek.
     * @param p2 Drugi wierzchołek.
     * @param p3 Trzeci wierzchołek.
     * @param color Kolor trójkąta.
     */
    void drawTriangle(Point2D p1, Point2D p2, Point2D p3, Color color);
    /**
     * @brief Rysuje wielokąt na podstawie listy wierzchołków w podanym kolorze.
     * @param points Lista wierzchołków wielokąta.
     * @param color Kolor wielokąta.
     */
    void drawPolygon(vector<Point2D> &points, Color color);
    /**
     * @brief Rysuje linię między dwoma punktami w podanym kolorze.
     * @param p1 Punkt początkowy.
     * @param p2 Punkt końcowy.
     * @param color Kolor linii.
     */
    void drawLine(Point2D p1, Point2D p2, Color color);
    /**
     * @brief Rysuje łamaną w podanym kolorze, opcjonalnie domkniętą.
     * @param points Lista punktów łamanej.
     * @param color Kolor linii.
     * @param isClosed Czy połączyć ostatni punkt z pierwszym.
     */
    void drawPolyline(vector<Point2D> &points, Color color, bool isClosed);
    /**
     * @brief Tworzy i ustawia bufor pikseli o danym rozmiarze.
     * @param width Szerokość bufora w pikselach.
     * @param height Wysokość bufora w pikselach.
     * @return true jak się uda, false przy błędzie.
     */

    bool initBuffer(int width, int height);
    /**
     * @brief Zwraca kolor piksela na pozycji (x, y).
     * @param x Współrzędna X piksela.
     * @param y Współrzędna Y piksela.
     * @return Kolor piksela w buforze.
     */
    Color getPixelColor(int x, int y);
    /**
     * @brief Wypełnia cały bufor jednym kolorem.
     * @param clearColor Kolor wypełnienia.
     */
    void clearBuffer(Color clearColor);
    /**
     * @brief Sprawdza, czy dwa kolory są takie same.
     * @param c1 Pierwszy kolor.
     * @param c2 Drugi kolor.
     * @return true, jeśli kolory są równe; false w przeciwnym razie.
     */
    bool areColorsEqual(Color c1, Color c2);
    /**
     * @brief Wypełnia obszar kolorem aż do napotkania koloru granicy.
     * @param point Punkt startowy wypełniania.
     * @param fillColor Kolor wypełnienia.
     * @param boundaryColor Kolor granicy zatrzymującej wypełnianie.
     */
    void boundaryFill(Point2D point, Color fillColor, Color boundaryColor);
};

#endif