#ifndef SILNK2D_BITMAPHANDLER_H
#define SILNK2D_BITMAPHANDLER_H

#include <raylib.h>
#include <string>

using namespace std;

/**
 * @brief Obsługuje teksturę w raylibie: ładowanie z pliku, rysowanie i usuwanie z pamięci.
 */
class BitmapHandler {
private:
    /** @brief Tekstura z rayliba. */
    Texture2D texture;

public:
    /**
     * @brief Tworzy pusty obiekt bez załadowanej tekstury.
     */
    BitmapHandler();

    /**
     * @brief Wczytuje teksturę z podanego pliku.
     * @param filename Ścieżka do pliku z obrazkiem.
     */
    void loadFromFile(string filename);
    /**
     * @brief Usuwa teksturę i zwalnia pamięć.
     */
    void destroy();
    /**
     * @brief Rysuje teksturę na pozycji (x, y) w podanej skali.
     * @param x Pozycja X na ekranie.
     * @param y Pozycja Y na ekranie.
     * @param scale Skala rysowania tekstury.
     */
    void draw(float x, float y, float scale);
    /**
     * @brief Zwraca szerokość tekstury.
     * @return Szerokość tekstury w pikselach.
     */
    int getWidth() const;
    /**
     * @brief Zwraca wysokość tekstury.
     * @return Wysokość tekstury w pikselach.
     */
    int getHeight() const;
};

#endif