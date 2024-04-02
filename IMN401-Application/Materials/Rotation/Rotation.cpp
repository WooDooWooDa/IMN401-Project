
#include "Rotation.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>
#include <chrono>


Rotation::Rotation(string name) :
	MaterialGL(name)
{
}

Rotation::~Rotation()
{
}

void Rotation::render(Node* o)
{
}
void Rotation::animate(Node* o, const float elapsedTime)
{
	o->frame()->rotate(glm::vec3(0,1,0), elapsedTime/1000);
}
