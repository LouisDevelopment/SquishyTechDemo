#ifndef LEVEL_H
#define LEVEL_H

#include "SpriteRenderer.h"
#include "Entity.h"
#include "Input.h"
#include <glm/gtc/random.hpp>

extern class LevelManager {

public:
	enum state {
		main
	};

	static std::vector<Ball> balls;
	static std::vector<Squishy> squishies;

	static const char* holdingObj;
	int floorHeight;
	static MouseInput mInput;
	static int width, height;
	glm::vec2 mPos;
	Button addItem, removeItem;

	state CURRENT = main;

	LevelManager();
	LevelManager(int, int);

	void tick();

	void render(TextureRenderer r);

	const void addBall(Ball);
	const void removeBall();
	static const Ball getBall(int);
	static const void swapBall(int, Ball);
	const void addSquishy(Squishy);
};

#endif