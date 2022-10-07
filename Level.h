#ifndef LEVEL_H
#define LEVEL_H

#include "SpriteRenderer.h"
#include "Entity.h"
#include "Input.h"
#include <glm/gtc/random.hpp>

//Levelmanager handles all things on the game screen (in this tech demo at least)
extern class LevelManager {

public:
	//only 1 state, the main game. In the version I am actively working on there is also a menu and the park
	enum state {
		main
	};

	//list of all balls and squishies in the scene (future versions allow for interaction between 2 or more squishies)
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