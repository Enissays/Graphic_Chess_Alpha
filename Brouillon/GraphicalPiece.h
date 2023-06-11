#pragma once
#include "SFML/Graphics.hpp"



class GraphicalPiece
{
public:
	GraphicalPiece(int px, int py, int id, sf::Texture);
	GraphicalPiece(int x, int y, int id, sf::Texture, sf::Texture);
	~GraphicalPiece();
	void draw(sf::RenderWindow &);
	int getId() { return id; }
	bool collides(sf::RenderWindow &window) { 
		int mx = sf::Mouse::getPosition(window).x;
		int my = sf::Mouse::getPosition(window).y;
		sf::Vector2f points;
		points.x = float(mx);
		points.y = float(my);
		return bound.contains(points);
	}
	void move(int x, int y) { sprite.setPosition(x, y); }
	int getX() { return x; }
	int getY() { return y; }

	sf::Vector2f getPos() { return { sprite.getPosition().x, sprite.getPosition().y}; }

private:
	int x;
	int y;
	int id;

	sf::Sprite sprite;
	sf::Texture texture;
	int size;
	sf::FloatRect bound;
};

