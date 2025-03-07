#include "MapLoader.h"

#include <fstream>
#include <string>
#include <sstream>

void MapLoader::Save(const std::string& fileName)
{
	std::ofstream file(fileName);
	if (!file) {
		std::cerr << "ERROR: Could not open file for writing: " << fileName << std::endl;
		return;
	}
	file << "[Map]" << std::endl;
	file << "tilesheet=\"Assets/World/Prison/tilesheet.png\"" << std::endl;
	file << "name=Level 1" << std::endl;
	file << "tile-width=16" << std::endl;
	file << "tile-height=16" << std::endl;
	file << "scale-x=5" << std::endl;
	file << "scale-y=5" << std::endl;
	file << "data-size=9" << std::endl;
	file << "data=120,121,122,144,145,156,157,158,159" << std::endl;
	file.close();
}

void MapLoader::Load(const std::string& fileName, MapData& mapData)
{
	std::string line;
	std::ifstream file(fileName);

	bool isMapValid = false;

	if (file.is_open())
	{
		char delimiter = '\n';
		while (getline(file, line, delimiter))
		{
			if (!isMapValid)
			{
				if (line == "[Map]")
				{
					isMapValid = true;
					continue;
				}
				else
				{
					std::cout << "Invalid map file!" << std::endl;
					break;
				}
				continue;
			}
			else
			{
				int count = line.find('=');
				if (count == std::string::npos) {
					std::cout << "Invalid line: " << line << std::endl;
					continue; // Skip invalid lines
				}
				std::string variable = line.substr(0, count);
				std::string value = line.substr(count + 1, line.length() - count);
				try
				{
					if (variable == "tilesheet")
					{
						mapData.tilesheet = value;
					}
					else if (variable == "name")
					{
						mapData.name = value;
					}
					else if (variable == "map-width")
					{
						mapData.mapWidth = std::stoi(value);
					}
					else if (variable == "map-height")
					{
						mapData.mapHeight = std::stoi(value);
					}
					else if (variable == "tile-width")
					{
						mapData.tileWidth = std::stoi(value);
					}
					else if (variable == "tile-height")
					{
						mapData.tileHeight = std::stoi(value);
					}
					else if (variable == "scale-x")
					{
						mapData.scaleX = std::stoi(value);
					}
					else if (variable == "scale-y")
					{
						mapData.scaleY = std::stoi(value);
					}
					else if (variable == "data-size")
					{
						mapData.dataSize = std::stoi(value);
						mapData.data.resize(mapData.dataSize);
					}
					else if (variable == "data")
					{
						// std::stringstream ss(value);
						// std::string token;
						// int index = 0;
						// 
						// while (getline(ss, token, ',')) {
						// 	mapData.data[i] = std::stoi(token);
						// }
						int n = 0;
						int start = 0;
						int i = 0;
						while (value[n] != '\0')
						{
							if (value[n] == ',' || value[n + 1] == '\0') // Risk of out-of-bounds access
							{
								int number = std::stoi(value.substr(start, n)); // Incorrect substring extraction
								start = n + 1;
								mapData.data[i] = number;
								i++;
							}
							n++;
						}
					}
				}
				catch (const std::exception& e)
				{
					std::cout << "Failed to parse map file!" << e.what() << std::endl;
				}
			}
		}
		file.close();
	}
	else
	{
		std::cerr << "ERROR: Could not parse line in " << fileName << ": " << line << std::endl;
	}
}
