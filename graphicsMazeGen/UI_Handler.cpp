#include "UI_Handler.h"

UI_Handler::UI_Handler(){}

void UI_Handler::Draw2DCharArrayAsMap(char** array, int rows, int columns)
{
	ImGui::Text("Map");

	if (ImGui::BeginTable("", 8, ImGuiTableFlags_Resizable + ImGuiTableFlags_Borders) == 1)
	{
		for (int row = 0; row < 8; ++row)
		{
			for (int col = 0; col < 8; ++col)
			{
				ImGui::TableNextColumn();
				ImGui::Text("%c", array[row][col]);
			}
			ImGui::TableNextRow();
		}

		ImGui::EndTable();
	}
}

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