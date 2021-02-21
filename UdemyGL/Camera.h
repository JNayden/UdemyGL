#pragma once
#include "GL/glew.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GLFW/glfw3.h"
#include <iostream>

class Camera
{
public:
	Camera() = default;
	Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed);
	void keyControl(bool* keys, float deltaTime); // bool keys[]
	void mouseControl(float xChange, float  yChange);
	glm::mat4 calculateViewMatrix();
	~Camera();
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float turnSpeed;

	void update();
};

