#pragma once
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

enum CameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
public:
	//Camera transform
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;

	//Camera parameters
	float movementSpeed;
	float rotationSpeed;
	float fov;
	float pitch;
	float yaw;

	Camera();

	Camera(glm::vec3 startingPosition, glm::vec3 startingForward);

	glm::mat4 GetViewMatrix();

	void HandleKeyboard(CameraMovement direction, float deltaTime);

	void HandleMouseMovement(float xOffset, float yOffset, float deltaTime);

	void HandleMouseScroll(float offset);

private:
	void UpdateCameraVectors();
};