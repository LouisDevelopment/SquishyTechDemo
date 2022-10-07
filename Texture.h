#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>
#include "stb_image.h"
#include <map>

class Texture {

	unsigned int texture = 0;
	bool alpha = true;

public:
	int width = 0, height = 0;

	unsigned char *data;

	Texture();

	Texture(char const*, char const*, bool);

	
	void bind();

	void unbind();

private:

	void generateTexture(unsigned char*);

};

static std::map<std::string, Texture> textures;

class TextureManager {


	static std::map<std::string, Texture> textures;
public:

	TextureManager();

	static Texture initTex(const char* path, const char* name, bool alpha) {
		textures.insert(std::pair<const char*, Texture>( name, Texture(path, name, alpha) ));
		return textures.at(name);
	}
	static Texture getTex(const char* name) {
		if (textures.count(name) > 0) {
			return textures.at(name);
		}
		return textures.at("void");
	}
};


#endif