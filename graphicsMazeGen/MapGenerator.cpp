#include "MapGenerator.h"

/// <summary>
/// Creates a MapGenerator instance and sets the mapPath to the passed argument.
/// </summary>
/// <param name="loadMapPath"></param>
MapGenerator::MapGenerator(std::string loadMapPath)
{
	mapPath = loadMapPath;
}

/// <summary>
/// Returns the rows of the map
/// </summary>
const unsigned int MapGenerator::GetRows()
{ return rows; }
\
/// <summary>
/// Returns the columns of the map
/// </summary>
const unsigned int MapGenerator::GetColumns()
{ return columns; }

/// <summary>
/// Prints the passed 2d array to the console
/// </summary>
/// <param name="grid">The 2d char array to print</param>
void MapGenerator::PrintGrid(char** grid)
{
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < columns; ++col)
		{
			std::cout << grid[row][col] << ' ';
		}
		std::cout << std::endl;
	}
}

/// <summary>
/// Populates the passed 2d char array with the loaded symbols from the map file.
/// </summary>
void MapGenerator::ReadGridFromFile(char**& grid)
{
	std::ifstream file(mapPath);
	if (!file.is_open())
	{
		std::cout << "Failed to open the file." << std::endl;
		return;
	}

	//Memory allocation
	grid = new char* [rows];
	for (int row = 0; row < rows; ++row)
	{
		grid[row] = new char[columns];
	}

	//Reads the file and writes the chars to a 2d array.
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < columns; ++col)
		{
			file >> grid[row][col];
		}
	}

	file.close();
}