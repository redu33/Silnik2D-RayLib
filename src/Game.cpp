#include "Game.h"
#include "Engine.h"

float Game::getPlayerWidth() const {
    return player.bitmaps.empty() ? 0.0f : player.bitmaps[0]->getWidth() * player.scale;
}

float Game::getPlayerHeight() const {
    return player.bitmaps.empty() ? 0.0f : player.bitmaps[0]->getHeight() * player.scale;
}

bool Game::collidesWithBox(float px, float py, float pw, float ph, const SolidBox &box) const {
    return (px < box.x + box.w && px + pw > box.x && py < box.y + box.h && py + ph > box.y);
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
    float wall = 10.0f;
    float doorWidth = 110.0f;
    float sideTopWidth = (screenWidth - doorWidth) / 2.0f;

    collectedCount = 0;
    doorOpen = false;

    player.x = screenWidth / 2.0f - getPlayerWidth() / 2.0f;
    player.y = screenHeight - wall - getPlayerHeight() - 20.0f;

    walls.clear();
    walls.emplace_back(0.0f, 0.0f, sideTopWidth, wall, BLACK);
    walls.emplace_back(sideTopWidth + doorWidth, 0.0f, sideTopWidth, wall, BLACK);
    walls.emplace_back(0.0f, screenHeight - wall, screenWidth, wall, BLACK);
    walls.emplace_back(0.0f, wall, wall, screenHeight - 2.0f * wall, BLACK);
    walls.emplace_back(screenWidth - wall, wall, wall, screenHeight - 2.0f * wall, BLACK);

    // 3. Drzwi w górnej ścianie
    door = SolidBox(sideTopWidth, 0.0f, doorWidth, wall, MAROON);

    // 4. Przeszkody wewnętrzne (RectangleShape)
    obstacles.clear();
    obstacles.emplace_back(220.0f, 280.0f, 90.0f, 90.0f, GRAY);
    obstacles.emplace_back(screenWidth - 310.0f, 280.0f, 90.0f, 90.0f, GRAY);
    obstacles.emplace_back(screenWidth / 2.0f - 70.0f, 180.0f, 140.0f, 50.0f, GRAY);

    // 5. Pięć obracających się diamentów (PolygonShape)
    diamonds.clear();
    vector<Point2D> spawnPoints = {
        Point2D(130.0f, 130.0f),
        Point2D(screenWidth - 130.0f, 130.0f),
        Point2D(screenWidth / 2.0f, screenHeight * 0.56f),
        Point2D(150.0f, screenHeight - 150.0f),
        Point2D(screenWidth - 150.0f, screenHeight - 150.0f)
    };

    float r = 32.0f;
    for (const auto &c : spawnPoints) {
        vector<Point2D> pts = {
            Point2D(c.getX(), c.getY() - r),
            Point2D(c.getX() + r, c.getY()),
            Point2D(c.getX(), c.getY() + r),
            Point2D(c.getX() - r, c.getY())
        };
        diamonds.emplace_back(pts, r, SKYBLUE);
    }
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

    auto hitsSolid = [&](float testX, float testY) {
        for (const auto &w : walls) {
            if (collidesWithBox(testX, testY, pw, ph, w)) return true;
        }
        for (const auto &obs : obstacles) {
            if (collidesWithBox(testX, testY, pw, ph, obs)) return true;
        }
        if (!doorOpen && collidesWithBox(testX, testY, pw, ph, door)) {
            return true;
        }
        return false;
    };

    if (hitsSolid(player.x, player.y)) {
        if (!hitsSolid(prevX, player.y)) {
            player.x = prevX;
        } else if (!hitsSolid(player.x, prevY)) {
            player.y = prevY;
        } else {
            player.x = prevX;
            player.y = prevY;
        }
    }

    float playerCenterX = player.x + pw / 2.0f;
    float playerCenterY = player.y + ph / 2.0f;

    collectedCount = 0;
    for (auto &d : diamonds) {
        if (d.collected) {
            collectedCount++;
            continue;
        }

        d.shape.rotate(d.shape.getCenter(), 90.0f * dt);

        Point2D dCenter = d.shape.getCenter();
        float distX = playerCenterX - dCenter.getX();
        float distY = playerCenterY - dCenter.getY();
        float hitDist = (pw + ph) / 4.0f + d.radius;

        if (distX * distX + distY * distY <= hitDist * hitDist) {
            d.collected = true;
            collectedCount++;
        }
    }

    if (collectedCount == (int)diamonds.size()) {
        doorOpen = true;
    }

    if (doorOpen && collidesWithBox(player.x, player.y, pw, ph, door)) {
        resetLevel();
    }
}

void Game::draw(PrimitiveRenderer &renderer) {
    for (auto &w : walls) {
        w.shape.draw(renderer);
        renderer.boundaryFill(w.shape.getCenter(), BLACK, BLACK);
    }

    Color doorColor = doorOpen ? GREEN : MAROON;
    door.shape.setColor(doorColor);
    door.shape.draw(renderer);
    renderer.boundaryFill(door.shape.getCenter(), doorColor, doorColor);

    for (auto &obs : obstacles) {
        obs.shape.draw(renderer);
        renderer.boundaryFill(obs.shape.getCenter(), DARKBROWN, GRAY);
    }

    for (auto &d : diamonds) {
        if (!d.collected) {
            d.shape.draw(renderer);
            renderer.boundaryFill(d.shape.getCenter(), SKYBLUE, SKYBLUE);
        }
    }

    player.draw(renderer);

    DrawText(TextFormat("Diamenty: %d / %d", collectedCount, (int)diamonds.size()), 110, 4, 18, WHITE);
}

void Game::destroy() {
    player.destroy();
}