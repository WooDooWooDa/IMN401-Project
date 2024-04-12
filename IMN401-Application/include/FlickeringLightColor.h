#ifndef __LightNode__
#define __LightNode__

#include "EngineGL.h"
#include "Node.h"


class LightNode : Node
{
public:
	LightNode(std::string name, glm::vec4 color) : Node(name) { baseColor = color; this->color = color; };
	~LightNode();

	virtual void animate(const float elapsedTime);

	void changeColor(float delta);

	glm::vec4 color;

protected:
	glm::vec4 baseColor;
};
#endif