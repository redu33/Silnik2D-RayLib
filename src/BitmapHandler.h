#ifndef SILNK2D_BITMAPHANDLER_H
#define SILNK2D_BITMAPHANDLER_H

#include <raylib.h>
#include <string>

using namespace std;

class BitmapHandler {
private:
    Texture2D texture;

public:
    BitmapHandler();

    void loadFromFile(string filename);
    void destroy();
    void draw(float x, float y, float scale);
    int getWidth() const;
    int getHeight() const;
};

#endif