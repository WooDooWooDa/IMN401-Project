
#include "FlickeringLightColor.h"
#include <random>

void LightNode::animate(const float elapsedTime) {
	changeColor(elapsedTime);
}

void LightNode::changeColor(float delta) {
	color = baseColor;
}