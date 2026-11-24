#ifndef SILNK2D_GAME_H
#define SILNK2D_GAME_H

#include <vector>
#include "Shapes.h"
#include "Player.h"

class Engine;

/**
 * @brief Prostokątna przeszkoda, przez którą nie da się przejść.
 */
struct SolidBox {
    /** @brief Kształt prostokąta do rysowania. */
    RectangleShape shape;
    /** @brief Pozycja (x, y) oraz szerokość i wysokość. */
    float x, y, w, h;

    /**
     * @brief Tworzy przeszkodę prostokątną z pozycji o podanych wymiarach i kolorze.
     * @param pos Pozycja lewego górnego rogu przeszkody.
     * @param w Szerokość przeszkody.
     * @param h Wysokość przeszkody.
     * @param color Kolor przeszkody.
     */
    SolidBox(Point2D pos, float w, float h, Color color) : shape(pos, w, h, color) {
        this->x = pos.getX();
        this->y = pos.getY();
        this->w = w;
        this->h = h;
    }
};

/**
 * @brief Okrągła przeszkoda na planszy.
 */
struct SolidCircle {
    /** @brief Kształt okręgu do rysowania. */
    CircleShape shape;
    /** @brief Pozycja środka (x, y) i promień. */
    float x, y, radius;

    /**
     * @brief Tworzy okrągłą przeszkodę ze środka o promieniu i kolorze.
     * @param center Punkt będący środkiem okręgu.
     * @param radius Promień okręgu.
     * @param color Kolor przeszkody.
     */
    SolidCircle(Point2D center, float radius, Color color) : shape(center, radius, color) {
        this->x = center.getX();
        this->y = center.getY();
        this->radius = radius;
    }
};

/**
 * @brief Kolce zadające obrażenia, resetują poziom przy kontakcie.
 */
struct Spike {
    /** @brief Trójkątny kształt kolców. */
    TriangleShape shape;
    /** @brief Środek kolców i ich rozmiar. */
    float x, y, size;

    /**
     * @brief Tworzy kolce wokół podanego środka o danym rozmiarze i kolorze.
     * @param center Środek kolców.
     * @param size Rozmiar (połowa szerokości/wysokości) kolców.
     * @param color Kolor kolców.
     */
    Spike(Point2D center, float size, Color color) : shape(
            Point2D(center.getX(), center.getY() - size),
            Point2D(center.getX() - size, center.getY() + size),
            Point2D(center.getX() + size, center.getY() + size),
            color) {
        this->x = center.getX();
        this->y = center.getY();
        this->size = size;
    }
};

/**
 * @brief Diament do zebrania na planszy.
 */
struct Diamond {
    /** @brief Kształt diamentu z czterech punktów. */
    PolygonShape shape;
    /** @brief Rozmiar diamentu od środka. */
    float size;
    /** @brief Czy gracz już go zebrał. */
    bool collected = false;
    /**
     * @brief Tworzy diament na środku punktu o danym rozmiarze i kolorze.
     * @param center Środek diamentu.
     * @param size Rozmiar diamentu (odległość od środka do wierzchołków).
     * @param color Kolor diamentu.
     */
    Diamond(Point2D center, float size, Color color) : shape({
            Point2D(center.getX(), center.getY() - size),
            Point2D(center.getX() + size, center.getY()),
            Point2D(center.getX(), center.getY() + size),
            Point2D(center.getX() - size, center.getY())}, color) {
        this->size = size;
        collected = false;
    }
};

/**
 * @brief Logika planszy i przebieg samej gry.
 */
class Game {
private:
    /** @brief Pozycja gracza na planszy. */
    Player player = Player(400.0f, 300.0f, 350.0f, 3.0f);
    /** @brief Szerokość obszaru gry. */
    float screenWidth = 1280.0f;
    /** @brief Wysokość obszaru gry. */
    float screenHeight = 720.0f;

    /** @brief Margines pokoju od krawędzi ekranu. */
    float margin = 25.0f;
    /** @brief Ramka pokoju. */
    RectangleShape roomBorder = RectangleShape(Point2D(25.0f, 25.0f), 1230.0f, 670.0f, BLACK);
    /** @brief Lista prostokątnych przeszkód. */
    vector<SolidBox> obstacles;
    /** @brief Lista okrągłych słupków. */
    vector<SolidCircle> pillars;
    /** @brief Lista kolców na planszy. */
    vector<Spike> spikes;
    /** @brief Lista diamentów do zebrania. */
    vector<Diamond> diamonds;

    /** @brief Drzwi wyjściowe z pokoju. */
    SolidBox door = SolidBox(Point2D(0.0f, 0.0f), 10.0f, 10.0f, RED);
    /** @brief Czy drzwi są już otwarte. */
    bool doorOpen = false;
    /** @brief Liczba zebranych diamentów. */
    int collectedCount = 0;

    /**
     * @brief Zwraca szerokość gracza.
     * @return Szerokość obiektu gracza w pikselach.
     */
    float getPlayerWidth() const;
    /**
     * @brief Zwraca wysokość gracza.
     * @return Wysokość obiektu gracza w pikselach.
     */
    float getPlayerHeight() const;
    /**
     * @brief Sprawdza, czy prostokąt gracza nachodzi na podaną przeszkodę.
     * @param px Pozycja X gracza.
     * @param py Pozycja Y gracza.
     * @param pw Szerokość gracza.
     * @param ph Wysokość gracza.
     * @param box Przeszkoda, z którą sprawdzana jest kolizja.
     * @return true, jeśli obiekty na siebie nachodzą; false w przeciwnym razie.
     */
    bool collidesWithObject(float px, float py, float pw, float ph, const SolidBox &box) const;
    /**
     * @brief Sprawdza kolizje dla proponowanej pozycji (testX, testY) gracza.
     * @param testX Testowana współrzędna X gracza.
     * @param testY Testowana współrzędna Y gracza.
     * @return true, jeśli w tym miejscu dochodzi do kolizji; false jeśli droga wolna.
     */
    bool checkCollision(float testX, float testY) const;

public:
    /**
     * @brief Przygotowuje planszę i elementy gry pod podany rozmiar ekranu.
     * @param width Szerokość ekranu.
     * @param height Wysokość ekranu.
     * @return true, jeśli udało się przygotować grę; false przy błędzie.
     */
    bool init(int width, int height);
    /**
     * @brief Resetuje aktualny poziom do stanu początkowego.
     */
    void resetLevel();
    /**
     * @brief Obsługuje sterowanie gracza na podstawie wejścia z silnika.
     * @param engine Referencja do silnika, z którego czytane są klawisze/mysz.
     */
    void handleInput(Engine &engine);
    /**
     * @brief Aktualizuje stan gry, kolizje i postęp o czas klatki dt.
     * @param dt Czas, który upłynął od poprzedniej klatki (w sekundach).
     */
    void update(float dt);
    /**
     * @brief Rysuje pokój, przeszkody, przedmioty i gracza.
     * @param renderer Renderer używany do rysowania prymitywów.
     */
    void draw(PrimitiveRenderer &renderer);
    /**
     * @brief Czyści i zwalnia zasoby używane przez grę.
     */
    void destroy();
};

#endif