#pragma once 

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "EntityStats.h"

class UI_Handler
{
public:
	UI_Handler();

	void Draw2DCharArrayAsMap(char** array, int rows, int columns);

	void DrawPlayerInfo(EntityStats playerStats);
};