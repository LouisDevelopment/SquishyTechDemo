#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

//framebuffer class
class FrameBuffer{

private:
	unsigned int fbo;
	unsigned int tex;
	unsigned int rbo;

	int windowWidth, windowHeight;


	unsigned int quadVAO, quadVBO;
	//screen quad vertices
	float quadVertices[24] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

public: 
	
	//constructor to build framebuffer
	FrameBuffer(int width, int height) {
		windowWidth = width;
		windowHeight = height;
		prepareScreen();
		check();
	}
	//creates the framebuffer texture
	void createTexture() {
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowWidth, windowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);


	}
	//attaches the texture
	void attachTexture() {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
	}
	//creates the RBO
	void createRBO() {
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);

		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
	//attaches the RBO
	void attachRBO() {
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	}
	//binds the framebuffer
	void bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	}
	//unbinds the frame buffer
	void unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	//draws trhe framebuffer onto the screen
	void draw() {
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(quadVAO);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	//deletes the framebuffer
	void deleteFBO() {
		glDeleteFramebuffers(1, &fbo);
	}

	//Check if the framebuffer is implemented correctly and unbind it
	void check() {
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	//create the framebuffer
	void createFBO() {
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	}

	//prepare the quad VAO and properly create/attach the things needed
	void prepareScreen() {
		// screen quad VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(0));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(2*sizeof(float)));


		createFBO();
		createTexture();
		attachTexture();
		createRBO();
		attachRBO();

	}

	

};