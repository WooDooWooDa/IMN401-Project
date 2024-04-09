#ifndef __TEXTURE2D__
#define __TEXTURE2D__



#include <string>
#include "Scene.h"


class Texture2D
{
public:

	Texture2D(const std::string& filename, bool noRepeat = false);

	//Create an empty texture
	Texture2D(int _width = 1024, int _height = 1024);

	//Create an empty texture
	Texture2D(int _width = 1024, int _height = 1024,GLint format = GL_RGBA8);


	~Texture2D();


	void createEmptyTexture();
	void createEmptyTextureNoRepeat();
	void loadToGPU(bool noRepeat);
	void makeResident();

	void noRepeat();


	GLuint getId() {
		return id;
	};
	GLuint64 getHandle()
	{
		return handle;
	};

protected:
	GLuint id;
	GLuint64 handle;
	string name;
	int width, height;
	GLint format;
	

	unsigned char* image;



};
#endif