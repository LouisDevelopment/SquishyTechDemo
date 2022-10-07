#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <map>

//Mouseinput
class MouseInput {

public:
	GLFWwindow* window;
	int width, height;
	bool left, right, middle;

	//default constructor (never used)
	MouseInput() {
		width = 1280;
		height = 720;
		left = false;
		right = false;
		middle = false;

	}

	//main constructor for input
	MouseInput(GLFWwindow* window, int windowWidth, int windowHeight) {
		this->window = window;
		width = windowWidth;
		height = windowHeight;
		left = false;
		right = false;
		middle = false;
	}

	//return current mouse position in the window
	glm::vec2 mPos() {
		double mouseX;
		double mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		return glm::vec2(mouseX, mouseY);

	}

	//return true if the defined button is pressed, false otherwise (0 = left, 1 = middle, 2 = right)
	bool buttonPressed(int button) {
		int mButton = -132;
		bool pressed = false;

		if (button == 0) {
			mButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
			if (mButton == GLFW_TRUE) {
				left = true;
			}
		}
		if (button == 1) {
			mButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
			if (mButton == GLFW_TRUE) {
				middle = true;
			}
		}
		if (button == 2) {
			mButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
			if (mButton == GLFW_TRUE) {
				right = true;
			}
		}

		if (mButton == GLFW_TRUE) {
			pressed = true;
		}

		return pressed;

	}

	//if a button has just been released (end of a click) return true, else false
	bool buttonReleased(int button) {
		if (button == 0) {
			if (!buttonPressed(button) && left) {
				left = false;
				return true;
			}
		}
		if (button == 1) {
			if (!buttonPressed(button) && middle) {
				middle = false;
				return true;
			}
		}
		if (button == 2) {
			if (!buttonPressed(button) && right) {
				right = false;
				return true;
			}
		}
		return false;
	}

	//if the mouse is over a certain portion of the window return true, else false
	bool mouseOver(int x, int y, int width, int height) {
		glm::vec2 pos = mPos();
		if (pos.x >= x && pos.x < x + width) {
			if (pos.y >= y && pos.y < y + height) {
				return true;
			}
		}
		return false;
	}

	//update whether a button is pressed
	void tick() {
		buttonPressed(0);
		buttonPressed(1);
		buttonPressed(2);
	}
};

//Keyboard input (NOT USED IN TECH DEMO other than "ENTER" making the window fullscreen)
class KeyInput {

public:
	GLFWwindow* window;
	std::map<int, bool> keys;

	//default constructor never used
	KeyInput() {
	}

	//main constructor
	KeyInput(GLFWwindow* window) {
		this->window = window;
	}

	//check if this is a first time a key has been pressed, return true if it is
	bool firstInstance(int key) {
		int x = glfwGetKey(window, key);
		if (x == GLFW_PRESS && keys.find(key) == keys.end()) {
			return true;
		}
		else return false;
	}

	//check if a key is pressed, true if it is, false otherwise
	bool keyPressed(int key) {
		int x = glfwGetKey(window, key);
		if (x == GLFW_PRESS) {
			keys.insert(std::pair<int, bool>(key, true));
			return true;
		}

		keys.erase(key);
		return false;
	}

	//check if a key is not pressed, true if it isnt, false otherwise
	bool keyReleased(int key) {
		int x = glfwGetKey(window, key);
		if (x != GLFW_PRESS) {
			if (keys.find(key) != keys.end()) {
				if (keys.at(key)) {
					keys.insert(std::pair<int, bool>(key, false));
					return true;
				}
			}
		}
		return false;
	}

	//check if enter is pressed (only key used in this demo)
	void tick() {
		keyPressed(GLFW_KEY_ENTER);
	}

};

#endif
