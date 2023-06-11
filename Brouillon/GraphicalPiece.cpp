#include "GraphicalPiece.h"

GraphicalPiece::GraphicalPiece(int px, int py, int id, sf::Texture TEXT)
{
	this->id=id;
	texture = TEXT;
	sprite.setTexture(texture);
	sprite.setScale(0.20, 0.21);
	sprite.setPosition(px, py);
	bound = sprite.getGlobalBounds();
}

GraphicalPiece::GraphicalPiece(int x, int y, int id, sf::Texture TEXT, sf::Texture boardTexture)
{
	sf::Vector2u t_size = boardTexture.getSize();
	float pos_x = t_size.x / 8.0f;
	float pos_y = t_size.y / 8.0f;
	sprite.setScale(0.20 , 0.21);

	
	this->x = x;
	this->y = y;
	this->id = id;
	size = 100;
	texture = TEXT;
	sprite.setTexture(texture);
	sprite.setPosition(x * pos_x, y * pos_y);
	bound = sprite.getGlobalBounds();
}

GraphicalPiece::~GraphicalPiece()
{

}

void GraphicalPiece::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}