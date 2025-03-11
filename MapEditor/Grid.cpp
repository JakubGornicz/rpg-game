#include "Grid.h"

Grid::Grid(const sf::Vector2i& cellNumber,
		   const sf::Vector2i& cellSize,
		   const sf::Vector2i& scale,
		   const sf::Vector2f& position,
		   const sf::Color& color,
		   int lineThickness) :
	totalCells(cellNumber), cellSize(cellSize), scale(scale),
	lineThickness(lineThickness),position(position), color(color)
{
	totalLines = sf::Vector2i(totalCells.x + 1, totalCells.y + 1);
	hLine = new sf::RectangleShape[totalLines.y];
	vLine = new sf::RectangleShape[totalLines.x];
}

Grid::~Grid()
{
	delete[] hLine;
	delete[] vLine;
}

void Grid::Initialize()
{
	

	int horizontalLineLength = totalCells.x * cellSize.x * scale.x + lineThickness;
	int verticalLineLength = totalCells.y * cellSize.y * scale.y;

	for (size_t i = 0; i < totalLines.y; i++)
	{
		hLine[i].setSize(sf::Vector2f(horizontalLineLength, lineThickness));
		hLine[i].setPosition(position + sf::Vector2f(0, i * cellSize.y * scale.y));
		hLine[i].setFillColor(color);
	}

	for (size_t j = 0; j < totalLines.x; j++)
	{
		vLine[j].setSize(sf::Vector2f(lineThickness, verticalLineLength));
		vLine[j].setPosition(position + sf::Vector2f(j * cellSize.x * scale.x, 0));
		vLine[j].setFillColor(color);
	}
}

void Grid::Load()
{
}

void Grid::Update(float deltaTimeMs)
{
}

void Grid::Draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < totalLines.y; i++)
	{
		window.draw(hLine[i]);
	}
	for (size_t j = 0; j < totalLines.x; j++)
	{
		window.draw(vLine[j]);
	}
}
