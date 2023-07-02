#ifndef GLOBAL_H
#define GLOBAL_H

#include <glm/ext/vector_float3.hpp>

class Global
{
public:

	const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

	// Cubemap for skybox
	const std::vector<std::string> cubeFaces
	{
		"Textures/skybox_2/0_right.png",
		"Textures/skybox_2/1_left.png",
		"Textures/skybox_2/2_top.png",
		"Textures/skybox_2/3_bottom.png",
		"Textures/skybox_2/4_front.png",
		"Textures/skybox_2/5_back.png",
	};
};
#endif