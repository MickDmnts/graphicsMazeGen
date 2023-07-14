#pragma once

#include <iostream>
#include <fstream>
#include <string>

class MapGenerator
{
private:
	std::string mapPath;
	const unsigned int rows = 3;
	const unsigned int columns = 3;

public:
	const unsigned int GetRows();

	const unsigned int GetColumns();

	MapGenerator(std::string loadMapPath);

	void PrintGrid(char** grid);

	void ReadGridFromFile(char**& grid);
};