#include "UI_Handler.h"
#include <string>
#include <vector>
#include "MapGenerator.h"

/// <summary>
/// Default constructor
/// </summary>
UI_Handler::UI_Handler() {}

/// <summary>
/// Draws a 2d character array as a UI table window
/// </summary>
/// <param name="array">The 2d array to draw</param>
/// <param name="rows">Number of rows</param>
/// <param name="columns">Number of cols</param>
void UI_Handler::Draw2DCharArrayAsMap(char** array, int rows, int columns)
{
	ImGui::Begin("Map");

	if (ImGui::BeginTable("", 8, ImGuiTableFlags_Resizable + ImGuiTableFlags_Borders) == 1)
	{
		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < columns; ++col)
			{
				ImGui::TableNextColumn();
				ImGui::Text("%c", array[row][col]);
			}
			ImGui::TableNextRow();
		}

		ImGui::EndTable();
	}

	ImGui::End();
}

/// <summary>
/// Draws the player statistics to a new window
/// </summary>
/// <param name="playerStats">The entity stats</param>
void UI_Handler::DrawPlayerInfo(EntityStats playerStats)
{
	int health = playerStats.GetHealth();
	int mana = playerStats.GetMana();

	ImGui::Begin("Player Stats");
	ImGui::Text("Health");
	ImGui::ProgressBar(static_cast<float>(health) / 100.0f);
	ImGui::Text("Mana");
	ImGui::ProgressBar(static_cast<float>(mana) / 100.0f);

	ImGui::End();
}

/// <summary>
/// Draws an FPS graph based on the passed argument data
/// </summary>
/// <param name="fpsData">A list containing the calculated fps</param>
void UI_Handler::DrawFPS(std::vector<float> fpsData)
{
	ImGui::Begin("FPS");
	ImVec2 graphSize(ImGui::GetContentRegionAvail().x, 200);

	ImGui::PlotLines("##graph", fpsData.data(), static_cast<int>(fpsData.size()), 0, nullptr, FLT_MAX, FLT_MAX, graphSize);

	ImGui::End();
}