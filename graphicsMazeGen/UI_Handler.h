#pragma once 

#include <vector>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "EntityStats.h"
#include "Shader.h"

class UI_Handler
{
public:
	UI_Handler();

	void Draw2DCharArrayAsMap(char** array, int rows, int columns);

	void DrawPlayerInfo(EntityStats playerStats);

	void DrawFPS(std::vector<float> fpsData);
};