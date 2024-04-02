#pragma once

#include "EffectGL.h"

#include "Texture2D.h"

class Flou : public EffectGL
{
public:



	Flou(string name);

	
	~Flou();



	virtual void apply(FrameBufferObject* src, FrameBufferObject* target);

	virtual void animate(const float elapsedTime);


	virtual void displayInterface();


protected:
	FrameBufferObject* tmpFBO;
	GLProgram* vp;
	GLProgram* fp;
	GLProgram* fpH;
	GLProgram* fpV;
	GLuint l_Texture;

	bool show_interface;
	float blurValue;
};