#pragma once
#include<vector>
#include<iostream>
#include "SFML/Graphics.hpp"
#include "GraphicalPiece.h"


class GraphicalBoard
{
private:
	std::vector<std::vector<int>> board;
	sf::Texture texture;
	sf::Sprite sprite;

	std::vector<std::vector<GraphicalPiece*>> graphical_pieces;

	std::vector<std::string> p_names = { "pawn" ,"rook", "knight", "bishop", "queen", "king" };
	sf::Texture textures_white[6];
	sf::Texture textures_black[6];
public:
	GraphicalBoard();
	~GraphicalBoard();

	void update();
	void draw(sf::RenderWindow& window);
};

