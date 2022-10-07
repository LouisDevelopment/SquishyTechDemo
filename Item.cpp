#include "Item.h"
#include "Level.h"

//ball item default constructor (never used)
Ball::Ball() {
    pos = glm::vec2(10000, 10000);
    size = glm::vec2(64, 64);
    vel = glm::vec2(0, 0);
}

//main constructor, sets random colour
Ball::Ball(Texture tex, glm::vec2 pos) {
    this->pos = pos;
    this->tex = tex;
    r = glm::linearRand(0.2f, 0.8f);
    g = glm::linearRand(0.2f, 0.8f);
    b = glm::linearRand(0.2f, 0.8f);
    mInput = LevelManager::mInput;
    size = glm::vec2(64, 64);
    vel = glm::vec2(0, 0);
}

//update for it the ball is colliding with a wall
void Ball::tick() {
    if (pos.y < Squishy::floorHeight+48) {
        if (!(mInput.mouseOver(pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y) && mInput.buttonPressed(0))) {
            vel.y += 0.5f;
            falling = true;
        }
    }
    else {
        falling = false;
        vel.y = 0;
        pos.y = Squishy::floorHeight + 48;
    }
    if (pos.y < size.y / 2) {
        pos.y = size.y / 2;
    }
    if (pos.x > LevelManager::width - size.x / 2) {
        pos.x = LevelManager::width - size.x / 2;
    }
    if (pos.x < size.x / 2) {
        pos.x = size.x / 2;
    }

    if (tracking) {
        falling = false;
        vel.y = 0;
    }

    updatePos();
}

//maths for throwing balls
void Ball::updatePos() {

    prevPos.x = pos.x;
    prevPos.y = pos.y;
    if (mInput.mouseOver(pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y) && mInput.buttonPressed(0) && LevelManager::holdingObj != "ball" || tracking) {
        tracking = true;
        LevelManager::holdingObj = "ball";
        glm::vec2 mPos = mInput.mPos();
        if (mPos.x > 0 && mPos.x < LevelManager::width && mPos.y > 0 && mPos.y < Squishy::floorHeight + size.y) {
            pos.x = mPos.x;
            pos.y = mPos.y;
        }
    }
    if (mInput.buttonReleased(0) && tracking) {
        LevelManager::holdingObj = "";
        tracking = false;
        vel.x = (pos.x - prevPos.x) * 0.6f;
        vel.y = (pos.y - prevPos.y) * 0.6f;

    }
    vel.x *= 0.94f;
    if (vel.x < 0.02f && vel.x > -0.02f) {
        vel.x = 0;
    }

    if (vel.y < 0.002f && vel.y > -0.002f) {
        vel.y = 0;
    }

    if (pos.y + vel.y <= Squishy::floorHeight+48 && pos.y + vel.y >= size.y / 2) {
        pos.y += vel.y;
    }
    else {
        vel.y *= -0.9f;
    }
    if (pos.x + vel.x > 0 + size.x / 2 && pos.x + vel.x < LevelManager::width - size.x / 2) {
        pos.x += vel.x;
    }
    else {
        vel.x *= -0.8f;
        pos.x += vel.x;
    }
    if (vel.y < 0) {
        vel.y *= 0.9f;
    }
}

//render
void Ball::render(TextureRenderer r) {
    r.render(tex, glm::vec2(pos.x - size.x / 2, pos.y - size.y / 2), size, 0, glm::vec3(this->r, g, b), 1);
}
