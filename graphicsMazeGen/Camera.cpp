#include "Camera.h"

/// <summary>
/// Creates a camera instance with default camera values
/// </summary>
Camera::Camera()
{
	position = glm::vec3(0.0f);
	forward = glm::vec3(0.0f);

	pitch = 0.0f;
	yaw = -90.0f;

	movementSpeed = 2.0f;
	rotationSpeed = 5.0;

	fov = 45;

	UpdateCameraVectors();
};

/// <summary>
/// Creates a camera instance with the passed position and forward, the rest of the camera information is automatically set.
/// </summary>
Camera::Camera(glm::vec3 startingPosition, glm::vec3 startingForward)
{
	position = startingPosition;
	forward = startingForward;

	pitch = 0.0f;
	yaw = -90.0f;

	movementSpeed = 2.0f;
	rotationSpeed = 5.0;

	fov = 45;

	UpdateCameraVectors();
};

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + forward, up);
}

/// <summary>
/// Handles the position of the camera based on the passed direction by deltaTime
/// </summary>
void Camera::HandleKeyboard(CameraMovement direction, float deltaTime)
{
	float finalSpeed = movementSpeed * deltaTime;

	if (direction == FORWARD)
		position += forward * finalSpeed;
	if (direction == BACKWARD)
		position -= forward * finalSpeed;

	if (direction == LEFT)
		position -= right * finalSpeed;
	if (direction == RIGHT)
		position += right * finalSpeed;

	if (direction == UP)
		position += up * finalSpeed;
	if (direction == DOWN)
		position -= up * finalSpeed;
}

/// <summary>
/// Rotates the camera by xOffset and yOffset of the camera based on mouse movement in the screen.
/// </summary>
void Camera::HandleMouseMovement(float xOffset, float yOffset, float deltaTime)
{
	float finalSpeed = rotationSpeed * deltaTime;

	yaw += xOffset * finalSpeed;
	pitch -= yOffset * finalSpeed;
	if (pitch < -90.0f)
		pitch = -90.0f;
	if (pitch > 90.0f)
		pitch = 90.0f;

	UpdateCameraVectors();
}

/// <summary>
/// Handles the FOV of the camera based on the passed offset.
/// </summary>
void Camera::HandleMouseScroll(float offset)
{
	fov -= offset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 90.0f)
		fov = 90.0f;
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 direction;
	direction.x = glm::cos(glm::radians(yaw));
	direction.y = glm::sin(glm::radians(pitch));
	direction.z = glm::sin(glm::radians(yaw));

	forward = glm::normalize(direction);
	right = glm::normalize(glm::cross(forward, WORLD_UP)); // works because we do not have ROLL
	up = glm::normalize(glm::cross(right, forward));
}