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
    player.init();
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
        player.dx = 0.0f;
        player.dy = 0.0f;
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
            player.dy -= 1.0f;
        }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
            player.dy += 1.0f;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            player.dx -= 1.0f;
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            player.dx += 1.0f;
        }
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

    RectangleShape kwadrat = RectangleShape(Point2D(100, 100), 200, 200, WHITE);
    kwadrat.rotate(kwadrat.getCenter(), 0.73f);
    kwadrat.scale(kwadrat.getCenter(), 0.5, 0.5);
    kwadrat.translate(400,400);
    kwadrat.draw(renderer);
    renderer.boundaryFill(kwadrat.getCenter(), WHITE, WHITE);
    RectangleShape kwadrat2 = RectangleShape(Point2D(300,300), 100, 100, RED);
    kwadrat2.draw(renderer);
    renderer.boundaryFill(kwadrat2.getCenter(), RED, RED);

    player.draw(renderer);
    EndDrawing();


    // opisac w dokumentacji klasy, metody itp. po co sa i co robia
    // sprawozdanie ma byc glownie insturkcja obslugi silnika w zasadzie, takie cos ze jak stworzyc cos za pomoca silnika
    // to znaczy jaki obiekt stworzyc, jakie metody wykorzystac, jakie argumenty przyjmuja itp. i to smao przy rotacji,
    // wypelnianiu i cos o bitmapach, czyli po prostu jak sie ten silnik obsluguje jakby nie patrzec
    // dlaczego kurde obrot jest w radianach
}