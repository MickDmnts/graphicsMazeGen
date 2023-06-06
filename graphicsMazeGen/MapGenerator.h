#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class MapGenerator
{
private:
	string mapPath;
	const unsigned int width = 8;
	const unsigned int height = 8;

	string getMapFileContent()
	{
		fstream mapFile;
		string txt;

		mapFile.open(mapPath, ios::in);
		if (mapFile.is_open())
		{
			while (getline(mapFile, txt))
			{
				//TODO: Return the whole text file
				txt.append(txt);
			}
		}

		mapFile.close();

		return txt;
	}

public:
	MapGenerator()
	{
		mapPath = "ActiveMap/map01.mmp";
	}

	string printMap()
	{
		return getMapFileContent();
	}

	char** getMap()
	{
		string mapContent = getMapFileContent();

		char** maze = new char* [height];
		for (int i = 0; i < height; i++)
		{
			maze[i] = new char[width];
		}

		int index = 0;
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if (index < mapContent.length())
				{
					maze[i][j] = mapContent[index++];
				}
				else
				{
					maze[i][j] = '\0';
				}
			}
		}

		return maze;
	}
};

#endif