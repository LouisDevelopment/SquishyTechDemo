#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <C:\Users\Louis\Desktop\Project1\Vector.h>
#include <C:\Users\Louis\Desktop\Project1\Texture.h>
#include <C:\Users\Louis\Desktop\Project1\Shader.h>
#include <iostream>

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

	void render(Vec2f pos, Vec2f size, float rotate, Vec3f colour) {
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
		glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 2, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

};

class TextureRenderer {


public:


	int indices[6] = {
			0,1,3,1,2,3
	};
	Shader shader;
	unsigned int quadVAO, triVAO, EBO, VBO;

	TextureRenderer() {
		shader = Shader();
		TextureRenderer(shader);
	}

	TextureRenderer(Shader s) {
		shader = s;
		initRenderData();
	}

	void render(Texture tex, Vec2f pos, Vec2f size, float rotate, Vec3f colour) {
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
		glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 2, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

};