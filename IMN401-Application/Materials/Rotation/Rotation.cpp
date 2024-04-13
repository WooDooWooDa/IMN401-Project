
#include "Rotation.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>
#include <chrono>


Rotation::Rotation(string name) :
	MaterialGL(name)
{
	start_time = std::chrono::high_resolution_clock::now();
	timePassed = 0;
}

Rotation::~Rotation()
{
}

void Rotation::render(Node* o)
{
}
void Rotation::animate(Node* o, const float elapsedTime)
{
	o->frame()->rotate(glm::vec3(0, 1, 0), elapsedTime / 1000);

	std::chrono::time_point<std::chrono::high_resolution_clock> now_time = std::chrono::high_resolution_clock::now();

	float millis = 0.01f * std::chrono::duration_cast<std::chrono::milliseconds>(now_time - start_time).count();
	float jump = sin(millis) / 50;

	if (millis < 1000) {
		o->frame()->translate(glm::vec3(0, jump, 0));
	}
	else if (millis < 4000) {

	}
	else
		timePassed = 0;
		
}
