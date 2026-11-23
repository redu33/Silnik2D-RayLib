#ifndef SILNK2D_ENGINE_H
#define SILNK2D_ENGINE_H
#include <raylib.h>
#include <string>
#include "Primitives.h"
#include "Player.h"

using namespace std;

struct Config {
    int width = 1024;
    int height = 768;
    string title = "Silnik 2D";
    bool fullscreen = false;
    int FPS = 60;
    bool enableKeyboard = true;
    bool enableMouse = true;
    bool logs = true;
    Color clearColor = BLACK;
};

class Engine {
public:
    Config config;

    bool init();
    void run();
    void shutdown();

    void clnScreen(Color color);
    void logError(const string &logMessage);
    void logInfo(const string &logMessage);

    bool isKeyDown(int key);
    bool isKeyPressed(int key);
    bool isMouseDown(int button);
    bool isMousePressed(int button);

private:
    PrimitiveRenderer renderer;
    void handleInput();
    void updateLogic(float deltaTime);
    void renderScreen();
    Player player = Player(400.0f, 300.0f, 350.0f, 3.0f);
};

//

#endif