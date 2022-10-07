#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>
#include "stb_image.h"
#include <map>

//texture class
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


//manages all textures
class TextureManager {


	//map to store all textures
	static std::map<std::string, Texture> textures;
public:

	TextureManager();

	//add texture to map
	static Texture initTex(const char* path, const char* name, bool alpha) {
		textures.insert(std::pair<const char*, Texture>( name, Texture(path, name, alpha) ));
		return textures.at(name);
	}

	//get texture from map
	static Texture getTex(const char* name) {
		if (textures.count(name) > 0) {
			return textures.at(name);
		}
		return textures.at("void");
	}
};


#endif