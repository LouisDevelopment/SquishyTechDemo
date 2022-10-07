#ifndef BUTTON_H
#define BUTTON_H


#include <glm/glm.hpp>
#include "SpriteRenderer.h"
#include "Input.h"
#include <iostream>


//Header based class used to create UI buttons
class Button {
	
public:

	glm::vec2 pos, size;
	glm::vec3 colour;
	int textLength;
	const char* text;
	glm::vec2 statBar;
	float statAmount;
	Texture tex;
	MouseInput m;

	//empty default constructor, never used
	Button() {

	}

	//Constructors

	//Some features of the button class are not relevant in this tech demo, they are to be used in the final game. For example, statBar


	//Buytton type for buttons that allow a stat bar and text
	Button(glm::vec2 pos, glm::vec2 size, const char* text, glm::vec3 colour, MouseInput input, bool stat) {
		this->pos = pos;
		this->size = size;
		this->colour = colour;
		this->text = text;
		if (stat) {
			statBar = glm::vec2(size.x - size.x / 16, size.y / 16);
			statAmount = 1.f;
		}
		else {
			statBar = glm::vec2(0, 0);
			statAmount = 0;
		}
		std::string a = text;
		textLength = a.size();
		m = input;
	}

	//Button type for buttons that allow a stat bar but no text
	Button(glm::vec2 pos, glm::vec2 size, glm::vec3 colour, MouseInput input, bool stat) {
		this->pos = pos;
		this->size = size;
		if (stat) {
			statBar = glm::vec2(size.x - size.x / 16, size.y / 16);
			statAmount = 1.f;
		}
		else {
			statBar = glm::vec2(0, 0);
			statAmount = 0;
		}
		text = "";
		this->colour = colour;
		textLength = 0;
		m = input;
	}


	//Render using TextureRenderer class
	void render(TextureRenderer r) {
		//First render the background
		r.render(pos, size, 0, colour);
		//next render the stat bar if there is one
		if (statBar.x > 0) {
			r.render(glm::vec2(pos.x + size.x / 32, pos.y + size.y - size.y / 8), glm::vec2(statBar.x * statAmount, statBar.y), 0, glm::vec3(1.f, 1.f, 1.f));
		}
		//next render text if there is any
		if(textLength > 0)
			r.renderText(text, glm::vec2(pos.x + size.x/2 - textLength*5, pos.y + size.y / 6), size.x / 220, 0, glm::vec3(1, 1, 1));
	}

	//Simple boolean checking for if the button is left clicked
	bool pressed() {
		if (m.mouseOver(pos.x, pos.y, size.x, size.y)) {
			if (m.buttonReleased(0)) {
				return true;
			}
		}
		return false;
	}

};

#endif