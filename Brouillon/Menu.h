#pragma once
#include "SFML/Graphics.hpp"
#include <string>

#define MAX_NB 3

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int getPressed() { return selectedItemIndex; };
	void UpdateWithMouse(sf::RenderWindow& window);

private:
	int selectedItemIndex=0;
	sf::Font font;
	sf::Text menu[MAX_NB];
	sf::FloatRect bounds[MAX_NB];
};

