#include "Menu.h"

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("C:\\Users\\yassi\\source\\repos\\Enissays\\Brouillon\\Brouillon\\images\\comic.ttf"));
    
    std::string liste[MAX_NB] = {"Jouer", "Options", "Quitter"};
    for (int i = 0;i < MAX_NB;i++)
    {
        menu[i].setFont(font);
        menu[i].setFillColor(sf::Color::White);
        menu[i].setString(liste[i]);
        menu[i].setPosition(sf::Vector2f(width / 2 - 50, height / (MAX_NB + 1) * i + 100));

        bounds[i] = menu[i].getGlobalBounds();
    }

    menu[selectedItemIndex].setFillColor(sf::Color::Red);
}

Menu::~Menu()
{

}

void Menu::MoveUp()
{
    menu[selectedItemIndex].setFillColor(sf::Color::White);
    if (selectedItemIndex > 0) selectedItemIndex--;
}

void Menu::MoveDown()
{
    menu[selectedItemIndex].setFillColor(sf::Color::White);
    if (selectedItemIndex < MAX_NB - 1) selectedItemIndex++;
}

void Menu::draw(sf::RenderWindow& window)
{
    menu[selectedItemIndex].setFillColor(sf::Color::Red);
    for (int i = 0; i < MAX_NB; i++)
    {
        window.draw(menu[i]);
    }
    menu[selectedItemIndex].setFillColor(sf::Color::White);
}

void Menu::UpdateWithMouse(sf::RenderWindow& window)
{
    int mx = sf::Mouse::getPosition(window).x;
    int my = sf::Mouse::getPosition(window).y;
    sf::Vector2f points;
    points.x = float(mx);
    points.y = float(my);
    
    for (int i = 0; i < MAX_NB; i++) if (bounds[i].contains(points)) selectedItemIndex = i;

}