#pragma once
#include <iostream>
#include <vector>

struct MapData
{
	std::string tilesheet = "";
	std::string name = "";

	unsigned int mapWidth = 0;
	unsigned int mapHeight = 0;

	unsigned int tileWidth = 0;
	unsigned int tileHeight = 0;

	int scaleX = 0;
	int scaleY = 0;

	int dataSize = 0;
	std::vector<int> data;
};