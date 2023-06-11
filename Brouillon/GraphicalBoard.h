#pragma once
#include<vector>
#include<iostream>
#include "SFML/Graphics.hpp"
#include "GraphicalPiece.h"
#include "Piece.h"


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
	sf::Texture textures_moves[2];

	sf::Sprite tiles[2];
	std::vector<std::vector<sf::Sprite*>> graphical_moves;

	GraphicalPiece* selected_dnd;
	sf::Vector2f initial_pos;
	Piece* selected_piece;

	Board * board_logic;

	sf::Font font;
	sf::Text texts [5];
public:
	GraphicalBoard();
	~GraphicalBoard();

	void promote(int x, int y, sf::RenderWindow& window, Piece*);

	void update();
	void check_mouse(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void drag(sf::RenderWindow& window);

};

