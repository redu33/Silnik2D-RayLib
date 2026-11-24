#include "Game.h"

#include <cmath>

#include "Engine.h"

float Game::getPlayerWidth() const {
    if (player.bitmaps.empty()) {
        return 0.0f;
    } else {
        return player.bitmaps[0]->getWidth() * player.scale;
    }
}

float Game::getPlayerHeight() const {
    if (player.bitmaps.empty()) {
        return 0.0f;
    } else {
        return player.bitmaps[0]->getHeight() * player.scale;
    }
}

bool Game::collidesWithObject(float px, float py, float pw, float ph, const SolidBox &box) const {
    return (px < box.x + box.w && px + pw > box.x && py < box.y + box.h && py + ph > box.y);
}

bool Game::checkCollision(float testX, float testY) const {
    float pw = getPlayerWidth();
    float ph = getPlayerHeight();

    for (int i = 0; i < walls.size(); i++) {
        if (collidesWithObject(testX, testY, pw, ph, walls[i])) {
            return true;
        }
    }
    for (int i = 0; i < obstacles.size(); i++) {
        if (collidesWithObject(testX, testY, pw, ph, obstacles[i])) {
            return true;
        }
    }
    if (!doorOpen && collidesWithObject(testX, testY, pw, ph, door)) {
        return true;
    }
    return false;
}

bool Game::init(int width, int height) {
    screenWidth = (float)width;
    screenHeight = (float)height;
    if (!player.init()) {
        return false;
    }
    resetLevel();
    return true;
}

void Game::resetLevel() {
    float wallThickness = 10.0f;
    float doorWidth = 110.0f;
    float doorX = (screenWidth - doorWidth) / 2.0f;

    collectedCount = 0;
    doorOpen = false;

    player.x = screenWidth / 2.0f - getPlayerWidth() / 2.0f;
    player.y = screenHeight - wallThickness - getPlayerHeight() - 20.0f;

    walls.clear();
    walls.push_back(SolidBox(Point2D(0.0f, 0.0f), screenWidth, wallThickness, BLACK));
    walls.push_back(SolidBox(Point2D(0.0f, screenHeight - wallThickness), screenWidth, wallThickness, BLACK));
    walls.push_back(SolidBox(Point2D(0.0f, wallThickness), wallThickness, screenHeight - wallThickness - wallThickness, BLACK));
    walls.push_back(SolidBox(Point2D(screenWidth - wallThickness, wallThickness), wallThickness, screenHeight - wallThickness - wallThickness, BLACK));

    door = SolidBox(Point2D(doorX, 0.0f), doorWidth, wallThickness + 8.0f, MAROON);

    obstacles.clear();
    obstacles.push_back(SolidBox(Point2D(220.0f, 280.0f), 90.0f, 90.0f, GRAY));
    obstacles.push_back(SolidBox(Point2D(screenWidth - 310.0f, 280.0f), 90.0f, 90.0f, GRAY));
    obstacles.push_back(SolidBox(Point2D(screenWidth / 2.0f - 70.0f, 180.0f), 140.0f, 50.0f, GRAY));

    diamonds.clear();
    diamonds.push_back(Diamond(Point2D(130.0f, 130.0f), 32.0f, SKYBLUE));
    diamonds.push_back(Diamond(Point2D(screenWidth - 130.0f, 130.0f), 32.0f, SKYBLUE));
    diamonds.push_back(Diamond(Point2D(screenWidth / 2.0f, screenHeight * 0.56f), 32.0f, SKYBLUE));
    diamonds.push_back(Diamond(Point2D(150.0f, screenHeight - 150.0f), 32.0f, SKYBLUE));
    diamonds.push_back(Diamond(Point2D(screenWidth - 150.0f, screenHeight - 150.0f), 32.0f, SKYBLUE));
}

void Game::handleInput(Engine &engine) {
    player.dx = 0.0f;
    player.dy = 0.0f;
    if (engine.isKeyDown(KEY_W) || engine.isKeyDown(KEY_UP)) {
        player.dy -= 1.0f;
    }
    if (engine.isKeyDown(KEY_S) || engine.isKeyDown(KEY_DOWN)) {
        player.dy += 1.0f;
    }
    if (engine.isKeyDown(KEY_A) || engine.isKeyDown(KEY_LEFT)) {
        player.dx -= 1.0f;
    }
    if (engine.isKeyDown(KEY_D) || engine.isKeyDown(KEY_RIGHT)) {
        player.dx += 1.0f;
    }
}

void Game::update(float dt) {
    float prevX = player.x;
    float prevY = player.y;
    player.update(dt);

    float pw = getPlayerWidth();
    float ph = getPlayerHeight();

    if (checkCollision(player.x, player.y)) {
        if (!checkCollision(prevX, player.y)) {
            player.x = prevX;
        } else if (!checkCollision(player.x, prevY)) {
            player.y = prevY;
        } else {
            player.x = prevX;
            player.y = prevY;
        }
    }

    float playerCenterX = player.x + pw / 2.0f;
    float playerCenterY = player.y + ph / 2.0f;

    collectedCount = 0;
    for (int i = 0; i < diamonds.size(); i++) {
        if (!diamonds[i].collected) {
            Point2D center = diamonds[i].shape.getCenter();
            diamonds[i].shape.rotate(center, 90.0f * dt);

            float dx = playerCenterX - center.getX();
            float dy = playerCenterY - center.getY();
            float distance = sqrt(dx * dx + dy * dy);

            if (distance <= (pw / 2.0f) + diamonds[i].size) {
                diamonds[i].collected = true;
            }
        }
        if (diamonds[i].collected) {
            collectedCount++;
        }
    }

    if (collectedCount == (int)diamonds.size()) {
        doorOpen = true;
    }

    if (doorOpen && collidesWithObject(player.x, player.y, pw, ph, door)) {
        resetLevel();
    }
}

void Game::draw(PrimitiveRenderer &renderer) {
    for (int i = 0; i < walls.size(); i++) {
        walls[i].shape.draw(renderer);
        renderer.boundaryFill(walls[i].shape.getCenter(), BLACK, BLACK);
    }

    Color doorColor = MAROON;
    if (doorOpen) {
        doorColor = GREEN;
    }
    door.shape.setColor(doorColor);
    door.shape.draw(renderer);
    renderer.boundaryFill(door.shape.getCenter(), doorColor, doorColor);

    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i].shape.draw(renderer);
        renderer.boundaryFill(obstacles[i].shape.getCenter(), DARKBROWN, GRAY);
    }

    for (int i = 0; i < diamonds.size(); i++) {
        if (!diamonds[i].collected) {
            diamonds[i].shape.draw(renderer);
            renderer.boundaryFill(diamonds[i].shape.getCenter(), SKYBLUE, SKYBLUE);
        }
    }

    player.draw(renderer);
}

void Game::destroy() {
    player.destroy();
}