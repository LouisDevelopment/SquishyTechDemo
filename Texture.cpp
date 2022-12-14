#include "Texture.h"

//Default texture constructor just creates a colour tile (plain white square)
Texture::Texture() {
	Texture("res/colourTile.png", "default", false);
}

//constructor used for every other texture
Texture::Texture(char const* path, char const* name, bool alpha) {
	int nrChannels = 0;
	this->alpha = alpha;
	//stbi_set_flip_vertically_on_load(true);
	data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data) {
		generateTexture(data);
	}
	else {
		std::cout << "couldn't load texture: " << name << std::endl;
	}

}

//bind/unbind textures
void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

//generate texture, with alpha if the texture was created with alpha = true
void Texture::generateTexture(unsigned char* data) {
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (alpha) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

//TextureManager just has a map of textures
std::map<std::string, Texture> TextureManager::textures;
TextureManager::TextureManager() {

}

