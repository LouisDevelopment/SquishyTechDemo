#include "Level.h"

//Init static variables
int LevelManager::width = 1280;
int LevelManager::height = 720;
MouseInput LevelManager::mInput;

LevelManager::LevelManager(int scr_width, int scr_height) {
	//set width and height to actual current window width and height
	LevelManager::width = scr_width;
	LevelManager::height = scr_height;

	addItem = Button(glm::vec2(scr_width / 2 - 200, scr_height - 128), glm::vec2(128, 64), "Add Ball", glm::vec3(0.53, 0.31, 0.35), mInput, false);
	removeItem = Button(glm::vec2(scr_width / 2 + 72, scr_height - 128), glm::vec2(128, 64), "Remove Ball", glm::vec3(0.53, 0.31, 0.35), mInput, false);

}

const char* LevelManager::holdingObj = "";


void LevelManager::tick() {
	mPos = mInput.mPos();
	
	if (CURRENT == main) {
		for (int i = 0; i < balls.size(); i++) {
			balls.at(i).tick();
		}
		if (addItem.pressed()) {
			if (balls.size() < 50) {
				Ball ball = Ball(TextureManager::getTex("ball"), glm::vec2(width / 2, 100));
				addBall(ball);
			}
		}
		if (removeItem.pressed()) {
			if (balls.size() > 0) {
				removeBall();
			}
		}
		for (int i = 0; i < squishies.size(); i++) {
			if (balls.size() == 0) {
				squishies.at(i).holdingBall = false;
			}
			squishies.at(i).tick();
		}
	}
}

std::vector<Ball> LevelManager::balls;
std::vector<Squishy> LevelManager::squishies;

void LevelManager::render(TextureRenderer r) {
	if (CURRENT == main) {
		for (int i = 0; i < squishies.size(); i++) {
			squishies.at(i).render(r);
		}
		for (int i = 0; i < balls.size(); i++) {
			balls.at(i).render(r);
		}

		addItem.render(r);
		removeItem.render(r);
	}
}

const void LevelManager::addBall(Ball b) {
	balls.push_back(b);
	std::cout << balls.size();
}

const void LevelManager::removeBall() {
	balls.pop_back();
}

const Ball LevelManager::getBall(int i) {
	return balls.at(i);
}
const void LevelManager::swapBall(int i, Ball ball) {
	balls.at(i) = ball;
}

const void LevelManager::addSquishy(Squishy s) {
	squishies.push_back(s);
	std::cout << squishies.size();
}

