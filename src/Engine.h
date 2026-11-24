#ifndef SILNK2D_ENGINE_H
#define SILNK2D_ENGINE_H
#include <raylib.h>
#include <string>
#include "Primitives.h"
#include "Game.h"

using namespace std;
/**
 * @brief Struktura przechowująca ustawienia konfiguracyjne silnika 2D.
 */
struct Config {
    /** @brief Szerokość okna aplikacji w pikselach. */
    int width = 1280;
    /** @brief Szerokość okna aplikacji w pikselach. */
    int height = 720;
    /** @brief Tytuł wyświetlany na pasku okna. */
    string title = "Silnik 2D";
    /** @brief Określa, czy aplikacja ma działać w trybie pełnoekranowym. */
    bool fullscreen = false;
    /** @brief Docelowa liczba klatek na sekundę. */
    int FPS = 60;
    /** @brief Włącza lub wyłącza obsługę klawiatury. */
    bool enableKeyboard = true;
    /** @brief Włącza lub wyłącza obsługę myszy. */
    bool enableMouse = true;
    /** @brief Włącza lub wyłącza wypisywanie logów diagnostycznych. */
    bool logs = true;
    /** @brief Domyślny kolor czyszczenia ekranu. */
    Color clearColor = WHITE;
};
/**
 * @brief Główna klasa silnika 2D obsługująca wejście, aktualizację logiki i rysowanie klatek.
 */
class Engine {
private:
    /** @brief Renderer odpowiedzialny za rysowanie prymitywów 2D. */
    PrimitiveRenderer renderer;
    /** @brief Przetwarza zdarzenia wejścia z klawiatury i myszy. */
    void handleInput();
    /**
     * @brief Aktualizuje logikę gry i stan silnika.
     * @param deltaTime Czas, który upłynął od poprzedniej klatki.
     */
    void updateLogic(float deltaTime);
    /** @brief Renderuje bieżącą klatkę na ekranie. */
    void renderScreen();
    /** @brief Obiekt gry przechowujący jej stan i logikę. */
    Game game;

public:
    /** @brief Aktywna konfiguracja silnika. */
    Config config;

    /**
     * @brief Inicjalizuje okno i ładuje potrzebne zasoby silnika..
     * @return true, jeśli inicjalizacja przebiegła pomyślnie; w przeciwnym razie false.
     */
    bool init();
    /** @brief Uruchamia główną pętlę silnika aż do zamknięcia aplikacji. */
    void run();
    /** @brief Zwalnia zasoby i zamyka okno oraz środowisko silnika. */
    void shutdown();

    /**
     * @brief Czyści ekran wskazanym kolorem.
     * @param color Kolor użyty do wypełnienia tła.
     */
    void clnScreen(Color color);
    /**
     * @brief Zapisuje komunikat błędu do logów.
     * @param logMessage Treść komunikatu o błędzie.
     */
    void logError(const string &logMessage);
        /**
     * @brief Zapisuje komunikat informacyjny do logów.
     * @param logMessage Treść komunikatu informacyjnego.
     */
    void logInfo(const string &logMessage);

        /**
     * @brief Sprawdza, czy wskazany klawisz klawiatury jest aktualnie wciśnięty.
     * @param key Kod klawisza zgodny z definicjami raylib.
     * @return true, jeśli klawisz jest wciśnięty; w przeciwnym razie false.
     */
    bool isKeyDown(int key);
        /**
     * @brief Sprawdza, czy wskazany przycisk myszy jest aktualnie wciśnięty.
     * @param button Kod przycisku myszy zgodny z definicjami raylib.
     * @return true, jeśli przycisk jest wciśnięty; w przeciwnym razie false.
     */
    bool isMouseDown(int button);
};

#endif