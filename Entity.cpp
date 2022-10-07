#include "Entity.h"
#include "Level.h"

SquishyPoint::SquishyPoint() {
    vel = glm::vec2(0, 0);
}

SquishyPoint::SquishyPoint(glm::vec2 pos) {
    this->pos = pos;
    nextPos = pos;
    vel = glm::vec2(0, 0);
}

void SquishyPoint::updateX(float k) {
    float x = nextPos.x - pos.x;
    float acceleration = -k * x;

    vel.x += acceleration;
    nextPos.x += vel.x;

}
void SquishyPoint::updateY(float k) {
    float y = nextPos.y - pos.y;
    float acceleration = -k * y;

    vel.y += acceleration;
    nextPos.y += vel.y;

}

Squishy::Squishy(glm::vec2 pos, glm::vec2 size, int numOfRigidPoints, MouseInput m, int id) {
    totalPoints = numOfRigidPoints;

    SquishyPoint* rigidPoints = new SquishyPoint[totalPoints];

    for (int i = 0; i < numOfRigidPoints; i++) {
        float angle = glm::radians((360.f / numOfRigidPoints) * i);
        rigidPoints[i] = SquishyPoint(glm::vec2((glm::cos(angle) * (size.x / 2)+ glm::sin(angle)*8) + pos.x, glm::sin(angle) * (size.y / 2) + pos.y));
    }
    this->m = m;
    this->rigidPoints = rigidPoints;
    this->size = size;

    prevPos = pos;
    this->pos = pos;
}

void Squishy::tick() {
    prevPos.x = pos.x;
    prevPos.y = pos.y;
    Entity::tick();
    if (!(m.mouseOver(pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y) && m.buttonPressed(0) && LevelManager::holdingObj != "ball")) {
        vel.y += 0.4f;
    }
    if (pos.y < size.y / 2) {
        pos.y = size.y / 2;
    }
    if (pos.y > floorHeight) {
        pos.y = floorHeight;
    }
    if (pos.x > LevelManager::width - size.x / 2) {
        pos.x = LevelManager::width - size.x / 2;
    }
    if (pos.x < size.x / 2) {
        pos.x = size.x / 2;
    }

    if (LevelManager::balls.size() > 0) {
        int closestBallx = 10000, closestBally = 10000;
        int tempIndex;
        for (int i = 0; i < LevelManager::balls.size(); i++) {
            Ball temp = LevelManager::balls.at(i);
            if ((temp.pos.x-pos.x)*(temp.pos.x-pos.x) <= (closestBallx-pos.x)*(closestBallx - pos.x) && (temp.pos.y - pos.y)* (temp.pos.y - pos.y) <= (closestBally - pos.y) * (closestBally - pos.y)) {
                
                closestBallx = temp.pos.x;
                closestBally = temp.pos.y;
                tempIndex = i;
                std::cout << tempIndex << ", ";
            }
        }
        if (closestBallx > pos.x - 1 && closestBallx < pos.x + 1) {
            vel.x = 0;
            closestBallx = pos.x;
        }

        if (closestBallx >= pos.x - 1 && closestBallx <= pos.x + 1 && closestBally - pos.y > -164 && closestBally - pos.y < 164 && !holdingBall) {
            heldBallID = tempIndex;
            holdingBall = true;
        }

        if (LevelManager::balls.size() > heldBallID) {
            if (!holdingBall || LevelManager::balls.at(heldBallID).tracking) {
                holdingBall = false;
                heldBallID = -1;
                if (closestBallx < 9000) {
                    if (pos.y >= floorHeight - 2 && LevelManager::balls.size() > 0) {
                        vel.y = -20;
                    }
                    if (closestBallx < pos.x) {
                        vel.x = -1.4f;
                    }
                    else if (closestBallx > pos.x) {
                        vel.x = 1.4f;
                    }
                }
            }

            if (tracking) {
                holdingBall = false;
            }
            if (holdingBall) {
                LevelManager::balls.at(heldBallID).pos.x = pos.x - 106;
                LevelManager::balls.at(heldBallID).pos.y = pos.y - 32;
            }
        }
        else if (!holdingBall) {
            holdingBall = false;
            heldBallID = -1;
            if (closestBallx < 9000) {
                if (pos.y >= floorHeight - 2 && LevelManager::balls.size() > 0) {
                    vel.y = -20;
                }
                if (closestBallx < pos.x) {
                    vel.x = -1.4f;
                }
                else if (closestBallx > pos.x) {
                    vel.x = 1.4f;
                }
            }
        }
    }


    updateVel();
    updatePos();


    center = glm::vec2(rigidPoints[0].nextPos.x - size.x / 2, rigidPoints[0].nextPos.y);
}

void Squishy::updateVel() {
    for (int i = 0; i < totalPoints; i++) {
        float angle = glm::radians((360.f / totalPoints) * i);
        if (i >= totalPoints / 4*3) {
            rigidPoints[i].pos = glm::vec2((glm::cos(angle) * (size.x / 2) + glm::sin(angle) * 16) + pos.x, glm::sin(angle) * (size.y / 2) + pos.y);
        } else if (i >= totalPoints / 2 && i < totalPoints/4*3) {
            rigidPoints[i].pos = glm::vec2((glm::cos(angle) * (size.x / 2) - glm::sin(angle) * 16) + pos.x, glm::sin(angle) * (size.y / 2) + pos.y);
        }
        else {
            rigidPoints[i].pos = glm::vec2((glm::cos(angle) * (size.x / 2)) + pos.x, glm::sin(angle) * (size.y / 2) + pos.y);
        }

        rigidPoints[i].updateY(0.16f);
        rigidPoints[i].updateX(0.16f);

    }
}

void Squishy::updatePos() {
    for (int j = 0; j <10; j++) {
        for (int i = 0; i < totalPoints; i++) {
            
                rigidPoints[i].vel.x += (0.003f * rigidPoints[((i - 1)%totalPoints+totalPoints)% totalPoints].vel.x) + (0.003f * rigidPoints[((i+1)%totalPoints-1 % totalPoints + totalPoints) % totalPoints].vel.x);
                rigidPoints[i].vel.y += (0.003f * rigidPoints[((i - 1) % totalPoints + totalPoints) % totalPoints].vel.y) + (0.003f * rigidPoints[((i + 1) % totalPoints + totalPoints) % totalPoints].vel.y);

        }
    }

    for (int i = 0; i < totalPoints; i++) {
        rigidPoints[i].nextPos.x += rigidPoints[i].vel.x;
        rigidPoints[i].nextPos.y += rigidPoints[i].vel.y;
        if (rigidPoints[i].nextPos.y > floorHeight + (size.y / 2 - size.y / 6)) {
            rigidPoints[i].nextPos.y = floorHeight + (size.y / 2 - size.y / 6);
        }
        else if (rigidPoints[i].nextPos.y < 0) {
            rigidPoints[i].nextPos.y = 0;
        }
        if (rigidPoints[i].nextPos.x > LevelManager::width + (size.x / 2 - size.x / 6) - 8) {
            rigidPoints[i].nextPos.x = LevelManager::width + (size.x / 2 - size.x / 6) - 8;
        }
        else if (rigidPoints[i].nextPos.x < 0) {
            rigidPoints[i].nextPos.x = 0;
        }

        rigidPoints[i].vel.x *= 0.7f;
        rigidPoints[i].vel.y *= 0.7f;

    }

    if (m.mouseOver(pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y) && m.buttonPressed(0) && LevelManager::holdingObj != "ball" && LevelManager::holdingObj != "squishy" || tracking) {
        tracking = true;
        glm::vec2 mPos = m.mPos();
        if (mPos.x > 0 && mPos.x < LevelManager::width && mPos.y > 0 && mPos.y < floorHeight) {
            pos.x = mPos.x;
            pos.y = mPos.y;
            LevelManager::holdingObj = "squishy";
        }
    }
    if (m.buttonReleased(0) && tracking) {
        tracking = false;
        LevelManager::holdingObj = "";
        vel.x = (pos.x - prevPos.x) * 0.6f;
        vel.y = (pos.y - prevPos.y) * 0.6f;

    }
    vel.x *= 0.88f;

    if (vel.x < 0.002f && vel.x > -0.002f) {
        vel.x = 0;
    }

    if (vel.y < 0.002f && vel.y > -0.002f) {
        vel.y = 0;
    }

    if (pos.y + vel.y <= floorHeight && pos.y + vel.y >= size.y / 2) {
        pos.y += vel.y;
    }
    else {
        vel.y *= -0.6f;
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

void Squishy::render(TextureRenderer r) {

    Entity::render(r);
    shape = new glm::vec2[totalPoints];
    stomach = new glm::vec2[totalPoints / 2];
    offset = pos;
    for (int i = 0; i < totalPoints; i++) {
        //r.render(tex, Vec2f(x - width / 2, y - height / 2), Vec2f(width, height), 0, Vec3f(1.f, 1.f, 1.f));
        shape[i] = glm::vec2(rigidPoints[i].nextPos.x, rigidPoints[i].nextPos.y);
        if (i < totalPoints / 2) {
            stomach[i] = glm::vec2((rigidPoints[i * 2].nextPos.x - pos.x), rigidPoints[i * 2].nextPos.y - pos.y + (rigidPoints[totalPoints / 4].nextPos.y - pos.y));
        }
    }
    r.renderShape(shape, center, totalPoints, colour, 1.f, true);
    r.renderShape(stomach, pos, totalPoints / 2, glm::vec3(0.98f, 1.f, 0.9f), 1.f, 0.5f, true);

    offset.x = center.x-46;
    offset.y = center.y-78;
    r.render(TextureManager::getTex("colourCircle"), offset, glm::vec2(16,26), 0, glm::vec3(0, 0, 0));
    offset.x = center.x + 30;
    offset.y = center.y - 78;
    r.render(TextureManager::getTex("colourCircle"), offset, glm::vec2(16, 26), 0, glm::vec3(0, 0, 0));
    offset.x = center.x - 9;
    offset.y = center.y - 42;
    r.render(TextureManager::getTex("squishyMouth"), offset, glm::vec2(18, 12), 0, glm::vec3(1, 1, 1));

    r.render(glm::vec2(0, floorHeight + (size.y / 2 - size.y / 6) - 4), glm::vec2(LevelManager::width, LevelManager::height - floorHeight), 0, glm::vec3(0.47f, 0.27f, 0.28f));
}