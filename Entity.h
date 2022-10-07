#ifndef ENTITY_H
#define ENTITY_H

#include "Button.h"
#include "SpriteRenderer.h"
#include "Input.h"
#include "Item.h"
#include "FrameBuffer.h"

//Parent entity class (not really used in this techdemo)
class Entity {
public:
    glm::vec2 pos;
    glm::vec2 size;

    void tick() {

    }
    virtual void render(TextureRenderer) {

    }
};


//Represents each vertex of a Squishy object
class SquishyPoint {

public:
    glm::vec2 pos, nextPos, vel;


    SquishyPoint();

    SquishyPoint(glm::vec2);

    //update x and y seperately as the acceleration in each direction is different
    void updateX(float);
    void updateY(float);

};

//Squishy class, handles all changes to squishy and each of its vertices
class Squishy : public Entity {

private:
    
    glm::vec2* shape;
    glm::vec2* stomach;
    glm::vec2 offset;

public:

    //stores the floor height as it is used most often in this class
    static const int floorHeight = 460;
    glm::vec2 vel, center;
    int totalPoints, heldBallID=-1;
    glm::vec2 prevPos; 

    const glm::vec3 colour = glm::vec3(0.55f, 0.8f, 0.50f);
    bool falling = false, tracking = false, holdingBall = false;


    SquishyPoint* rigidPoints; 
    MouseInput m;

    Squishy(glm::vec2, glm::vec2, int, MouseInput, int);

    void tick();

    void updateVel();
    void updatePos();
    
    void render(TextureRenderer);
};

#endif
