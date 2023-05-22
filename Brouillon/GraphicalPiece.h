#pragma once
#include "SFML/Graphics.hpp"



class GraphicalPiece
{
public:
	GraphicalPiece();
	GraphicalPiece(int x, int y, int id, sf::Texture, sf::Texture);
	~GraphicalPiece();
	void draw(sf::RenderWindow &);
	int getId() { return id; }
	bool collides() { return bound.contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);  }

private:
	int x;
	int y;
	int id;

	sf::Sprite sprite;
	sf::Texture texture;
	int size;
	sf::FloatRect bound;
};

