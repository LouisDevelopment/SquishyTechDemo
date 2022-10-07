#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Font.h"
#include "Texture.h"
#include "Shader.h"
#include <iostream>
#include <vector>

class TileRenderer {

	
public:

	int indices[6] = {
			0,1,3,1,2,3
	};
	Shader shader;
	unsigned int quadVAO, triVAO, EBO, VBO;

	TileRenderer(Shader s) {
		shader = s;
		initRenderData();
	}

	void render(glm::vec2 pos, glm::vec2 size, float rotate, glm::vec3 colour) {
		shader.use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
		model = glm::translate(model, glm::vec3(size.x*0.5f, size.y*0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));
		model = glm::translate(model, glm::vec3(size.x * -0.5f, size.y * -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
		shader.setMat4("model", model, false);
		shader.setBool("invert", false);
		shader.setVec3("color", colour.x, colour.y, colour.z);
		shader.setFloat("alpha", 1.0f);

		//glActiveTexture(GL_TEXTURE0);
		//tex.bind();

		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		//tex.unbind();

	}

	void initRenderData() {
		float vertices[] = {
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f
		};

		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(quadVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float)*2, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float)*2, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

};

class TextureRenderer {

public:


	Texture tex;
	int indices[6] = {
			0,1,3,1,2,3
	};
	Shader shader, shader2;
	unsigned int quadVAO, triVAO, EBO, VBO;
	unsigned int quadVAO2, triVAO2, EBO2, VBO2;

	Font font;

	TextureRenderer() {
		shader = Shader();
		TextureRenderer(shader);
	}
	TextureRenderer(Shader s) {
		shader = s;
		initRenderData();
		tex = Texture("C:/Users/Louis/Pictures/Cpp game/Textures/colourTile.png", "col", false);
	}

	TextureRenderer(Shader s, Font f) {
		shader = s;
		font = f; 
		tex = Texture("C:/Users/Louis/Pictures/Cpp game/Textures/colourTile.png", "col", false);
		initRenderData();
	}
	
	void render(glm::vec2 pos, glm::vec2 size, float rotate, glm::vec3 colour) {
		shader.use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
		model = glm::translate(model, glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.0f));
		model = glm::rotate(model, rotate, glm::vec3(0.0, 0.0, 1.0));
		model = glm::translate(model, glm::vec3(size.x * -0.5f, size.y * -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
		shader.setMat4("model", model, false);
		shader.setBool("invert", false);
		shader.setVec3("color", colour.x, colour.y, colour.z);
		shader.setFloat("alpha", 1.0f);

		glActiveTexture(GL_TEXTURE0);
		tex.bind();

		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		tex.unbind();
		shader.unbind();

	}

	void render(glm::vec2 pos, glm::vec2 size, float rotate, glm::vec3 colour, float alpha) {
		shader.use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
		model = glm::translate(model, glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.0f));
		model = glm::rotate(model, rotate, glm::vec3(0.0, 0.0, 1.0));
		model = glm::translate(model, glm::vec3(size.x * -0.5f, size.y * -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
		shader.setMat4("model", model, false);
		shader.setBool("invert", false);
		shader.setVec3("color", colour.x, colour.y, colour.z);
		shader.setFloat("alpha", alpha);

		glActiveTexture(GL_TEXTURE0);
		tex.bind();

		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		tex.unbind();
		shader.unbind();

	}

	void render(Texture tex, glm::vec2 pos, glm::vec2 size, float rotate, glm::vec3 colour) {
		shader.use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
		model = glm::translate(model, glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));
		model = glm::translate(model, glm::vec3(size.x * -0.5f, size.y * -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
		shader.setMat4("model", model, false);
		shader.setBool("invert", false);
		shader.setVec3("color", colour.x, colour.y, colour.z);
		shader.setFloat("alpha", 1.0f);

		glActiveTexture(GL_TEXTURE0);
		tex.bind();

		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		tex.unbind();
		shader.unbind();

	}

	void render(Texture tex, glm::vec2 pos, glm::vec2 size, float rotate, glm::vec3 colour, float alpha) {
		shader.use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
		model = glm::translate(model, glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));
		model = glm::translate(model, glm::vec3(size.x * -0.5f, size.y * -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
		shader.setMat4("model", model, false);
		shader.setBool("invert", false);
		shader.setVec3("color", colour.x, colour.y, colour.z);
		shader.setFloat("alpha", alpha);

		glActiveTexture(GL_TEXTURE0);
		tex.bind();

		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		tex.unbind();
		shader.unbind();

	}

	void renderText(const char* text, glm::vec2 pos, float scale, float rotate, glm::vec3 colour) {
		font.renderText(text, pos.x, pos.y, scale, colour);
	}

	void renderShape(glm::vec2* points, glm::vec2 center, int totalPoints, glm::vec3 colour, float alpha, bool fill) {
		
		shader.use();

		glActiveTexture(GL_TEXTURE0);

		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		tex.bind(); 
		for (int i = 0; i < totalPoints; i++) {
			int dist = 0;
			if (points[i].x > points[(i + 1) % totalPoints].x) {
				if (points[i].y > points[(i + 1) % totalPoints].y) {
					dist = (points[i].x - points[(i + 1) % totalPoints].x) + (points[i].y - points[(i + 1) % totalPoints].y);
				}
				else {
					dist = (points[i].x - points[(i + 1) % totalPoints].x) + (points[(i + 1) % totalPoints].y - points[i].y);
				}
			}
			else {
				if (points[i].y > points[(i + 1) % totalPoints].y) {
					dist = (points[(i + 1) % totalPoints].x - points[i].x) + (points[i].y - points[(i + 1) % totalPoints].y);
				}
				else {
					dist = (points[(i + 1) % totalPoints].x - points[i].x) + (points[(i + 1) % totalPoints].y - points[i].y);
				}
			}
			int width = glm::sqrt(glm::pow(points[i].x-center.x, 2) + glm::pow(points[i].y - center.y, 2))*2;
			float angle = atan2(points[i].y - center.y, points[i].x - center.x) * glm::radians(180.f) / glm::pi<float>();

			if (i < totalPoints/4*3-1 || i > totalPoints/4*3+1) {
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(points[i].x, points[i].y, 0.0f));
				model = glm::rotate(model, angle, glm::vec3(0.0, 0.0, 1.0));
				model = glm::scale(model, glm::vec3(-width / 2 - 3, dist, 1.0f));
				shader.setMat4("model", model, false);
				shader.setBool("invert", false);
				shader.setVec3("color", colour.x, colour.y, colour.z);
				shader.setFloat("alpha", alpha);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}


		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		tex.unbind();
		shader.unbind();
	}

	void renderShape(glm::vec2* points, glm::vec2 offset, int totalPoints, glm::vec3 colour, float alpha, float scale, bool fill) {
		int width = -1;
		for (int i = 0; i < totalPoints; i++) {
			if (width < points[i % (totalPoints / 2)].x - points[i].x || width < -(points[i % (totalPoints / 2)].x - points[i].x)) {
				if (points[i % (totalPoints / 2)].x - points[i].x > 0) {
					width = points[i % (totalPoints / 2)].x - points[i].x;
				}
				else {
					width = -(points[i % (totalPoints / 2)].x - points[i].x);
				}
			}
		}
		shader.use();

		glActiveTexture(GL_TEXTURE0);

		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		tex.bind();
		for (int i = 0; i < totalPoints; i++) {
			int dist = 0;
			if (points[i].x > points[(i + 1) % totalPoints].x) {
				if (points[i].y > points[(i + 1) % totalPoints].y) {
					dist = (points[i].x - points[(i + 1) % totalPoints].x) + (points[i].y - points[(i + 1) % totalPoints].y);
				}
				else {
					dist = (points[i].x - points[(i + 1) % totalPoints].x) + (points[(i + 1) % totalPoints].y - points[i].y);
				}
			}
			else {
				if (points[i].y > points[(i + 1) % totalPoints].y) {
					dist = (points[(i + 1) % totalPoints].x - points[i].x) + (points[i].y - points[(i + 1) % totalPoints].y);
				}
				else {
					dist = (points[(i + 1) % totalPoints].x - points[i].x) + (points[(i + 1) % totalPoints].y - points[i].y);
				}
			}
			float angle = glm::radians((360.f / totalPoints) * i);

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(points[i].x*scale + offset.x, points[i].y*scale + offset.y, 0.0f));
			model = glm::rotate(model, angle, glm::vec3(0.0, 0.0, 1.0));
			model = glm::scale(model, glm::vec3((- width / 2 - 3) * scale, (dist)*scale, 1.0f));
			shader.setMat4("model", model, false);
			shader.setBool("invert", false);
			shader.setVec3("color", colour.x, colour.y, colour.z);
			shader.setFloat("alpha", alpha);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		tex.unbind();
		shader.unbind();
	}

	void initRenderData() {
		float vertices[] = {
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f
		};

		float tex[] = {
			0, 1,
			0, 0,
			1, 0,
			1, 1
		};

		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tex), tex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(quadVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 2, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
};

#endif