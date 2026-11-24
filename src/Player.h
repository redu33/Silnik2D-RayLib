#ifndef SILNK2D_PLAYER_H
#define SILNK2D_PLAYER_H

#include "Objects.h"

/**
 * @brief Animowany obiekt gracza, który porusza się i aktualizuje swój stan co klatkę.
 */
class Player : public SpriteObject, public UpdateableObject {
private:
    /** @brief Prędkość poruszania się gracza. */
    float speed;
    /** @brief Pierwsza klatka animacji gracza. */
    BitmapHandler frame1;
    /** @brief Druga klatka animacji gracza. */
    BitmapHandler frame2;

public:
    /**
     * @brief Tworzy gracza na podanej pozycji, z określoną prędkością i skalą.
     * @param x Pozycja X na planszy.
     * @param y Pozycja Y na planszy.
     * @param speed Prędkość ruchu gracza.
     * @param scale Skala rysowania gracza.
     */
    Player(float x, float y, float speed, float scale);
    /**
     * @brief Destruktor gracza.
     */
    ~Player();
    /** @brief Kierunek ruchu w osi X. */
    float dx;
    /** @brief Kierunek ruchu w osi Y. */
    float dy;
    /**
     * @brief Ładuje klatki i przygotowuje gracza do działania.
     * @return true, jeśli inicjalizacja się udała; false w przeciwnym razie.
     */
    bool init();
    /**
     * @brief Aktualizuje ruch i animację gracza o czas klatki dt.
     * @param dt Czas, który upłynął od poprzedniej klatki (w sekundach).
     */
    void update(float dt) override;
    /**
     * @brief Zwalnia tekstury używane przez gracza.
     */
    void destroy();
    /**
     * @brief Zwraca szerokość gracza.
     * @return Szerokość gracza w pikselach.
     */
    int getWidth() const;
    /**
     * @brief Zwraca wysokość gracza.
     * @return Wysokość gracza w pikselach.
     */
    int getHeight() const;
};

#endif