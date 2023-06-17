#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include <iostream>
#include <fstream>
#include <string>

class MapGenerator
{
private:
	std::string mapPath;
	const unsigned int rows = 8;
	const unsigned int columns = 8;

public:

	const unsigned int GetRows()
	{
		return rows;
	}

	const unsigned int GetColumns()
	{
		return columns;
	}

	MapGenerator(std::string loadMapPath)
	{
		mapPath = loadMapPath;
	}

	void PrintGrid(char** grid)
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

	void ReadGridFromFile(char**& grid)
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
};
#endif