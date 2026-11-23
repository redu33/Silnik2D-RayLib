#include "Engine.h"
#include <iostream>

#include "Shapes.h"

bool Engine::init(){
    SetTraceLogLevel(7);

    logInfo("Inicjalizacja silnika.");

    if (config.fullscreen) {
        SetConfigFlags(FLAG_FULLSCREEN_MODE);
    }

    if (config.width <= 0 || config.height <= 0) {
        logError("Nie udalo sie zainicjalizowac silnika.");
        logError("Niepoprawna rozdzielczosc.");
        return false;
    }

    InitWindow(config.width, config.height, config.title.c_str());

    player.init();

    if (!IsWindowReady()) {
        logError("Nie udalo sie zainicjalizowac silnika.");
        return false;
    }

    if (config.FPS > 0) {
        SetTargetFPS(config.FPS);
    } else {
        logError("Nie udalo sie zainicjalizowac silnika.");
        logError("Niepoprawna liczba klatek na sekunde.");
        return false;
    }

    renderer.initBuffer(config.width, config.height);
    logInfo("Silnik zostal poprawnie zainicjalizowany.");
    return true;
}

void Engine::run(){
    logInfo("Uruchomiono glowna petle.");
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        handleInput();
        updateLogic(deltaTime);
        renderScreen();
    }
    logInfo("Zakonczono glowna petle.");
}

void Engine::shutdown(){
    if (!IsWindowReady()) {
        return;
    }
    logInfo("Zamykanie, zwalnianie zasobow.");
    CloseWindow();
    logInfo("Poprawnie zamknieto.");
}

void Engine::clnScreen(Color color){
    ClearBackground(color);
}

void Engine::logError(const string &logMessage){
    if (config.logs) {
        cerr << "BLAD: " << logMessage << endl;
    }
}

void Engine::logInfo(const string &logMessage){
    if (config.logs) {
        cout << "INFO: " << logMessage << endl;
    }
}

bool Engine::isKeyDown(int key){
    return (config.enableKeyboard && IsKeyDown(key));
}
bool Engine::isKeyPressed(int key){
    return (config.enableKeyboard && IsKeyPressed(key));
}
bool Engine::isMouseDown(int button){
    return (config.enableMouse && IsMouseButtonDown(button));
}
bool Engine::isMousePressed(int button){
    return (config.enableMouse && IsMouseButtonPressed(button));
}

void Engine::handleInput(){
    if (config.enableKeyboard) {

    }
    if (config.enableMouse) {
        if (isMousePressed(MOUSE_BUTTON_LEFT)) {
            Vector2 pos = GetMousePosition();
            logInfo(to_string((int)pos.x) + ", " + to_string((int)pos.y));
        }
    }
}

void Engine::updateLogic(float deltaTime){
    player.update(deltaTime);
}

void Engine::renderScreen(){
    BeginDrawing();
    clnScreen(config.clearColor);
    renderer.clearBuffer(config.clearColor);
    DrawFPS(10,10);

    player.draw(renderer);

    EndDrawing();


    // opisac w dokumentacji klasy, metody itp. po co sa i co robia
    // sprawozdanie ma byc glownie insturkcja obslugi silnika w zasadzie, takie cos ze jak stworzyc cos za pomoca silnika
    // to znaczy jaki obiekt stworzyc, jakie metody wykorzystac, jakie argumenty przyjmuja itp. i to smao przy rotacji,
    // wypelnianiu i cos o bitmapach, czyli po prostu jak sie ten silnik obsluguje jakby nie patrzec
}