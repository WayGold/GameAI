#include "Obstacle.h"

Obstacle::Obstacle()
{
	obstacleRB = new RigidBody();
	width = 0.0f;
	height = 0.0f;
	obstacleColor = ofColor(0, 0, 0);

	top_left = glm::vec2(0.0f, 0.0f);
	top_right = glm::vec2(0.0f, 0.0f);
	bottom_left = glm::vec2(0.0f, 0.0f);
	bottom_right = glm::vec2(0.0f, 0.0f);
}

Obstacle::Obstacle(glm::vec2 i_pos, float i_width, float i_height, ofColor i_Color) : 
	width(i_width), height(i_height), obstacleColor(i_Color) {
	obstacleRB = new RigidBody();
	obstacleRB->position = i_pos;

	top_left = glm::vec2(i_pos.x - (width) / 2, i_pos.y - (height) / 2);
	top_right = glm::vec2(i_pos.x + (width) / 2, i_pos.y - (height) / 2);
	bottom_left = glm::vec2(i_pos.x - (width) / 2, i_pos.y + (height) / 2);
	bottom_right = glm::vec2(i_pos.x + (width), i_pos.y + (height) / 2);
}

Obstacle::~Obstacle()
{
	delete obstacleRB;
}

void Obstacle::draw()
{
	ofSetColor(obstacleColor);
	// Body
	ofDrawRectangle(glm::vec2(obstacleRB->position.x - width / 2, obstacleRB->position.y - height / 2), width, height);
}
