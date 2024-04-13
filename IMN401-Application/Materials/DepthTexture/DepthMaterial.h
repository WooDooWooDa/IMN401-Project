

#ifndef _DepthMaterial_
#define _DepthMaterial_


#include "MaterialGL.h"
#include "Texture2D.h"

class DepthMaterial : public MaterialGL
{
public:

	DepthMaterial(string name = "");

	~DepthMaterial();

	virtual void render(Node* o);

	virtual void animate(Node* o, const float elapsedTime);


protected:
	GLProgram* vp;
	GLProgram* fp;

	GLuint l_View, l_Proj, l_Model;
};

#endif