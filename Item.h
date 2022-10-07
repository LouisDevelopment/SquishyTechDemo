#ifndef ITEM_H
#define ITEM_H

#include "SpriteRenderer.h"
#include "Entity.h"
#include <list>
#include <glm/gtc/random.hpp>

extern class Ball{

public:

	bool falling = false;
	MouseInput mInput;
	glm::vec2 pos, prevPos;
	glm::vec2 vel, size;
	bool held = false;

	float r, g, b;
	Texture tex;
	bool tracking = false;

	Ball();

	Ball(Texture, glm::vec2);

	void tick();
	void render(TextureRenderer r);
	void updatePos();
	const char* getName();
};

#endif