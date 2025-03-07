#pragma once
#include "MapData.h"
#include <iostream>

class MapLoader
{
public:
	void Load(const std::string& fileName, MapData& mapData);
	void Save(const std::string& fileName);
};

