#include <SFML/Graphics.hpp>
#include "Menu.h"
#include"GraphicalBoard.h"
enum scenes { MENU = 0, PLAY = 1};


int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 620), "Mon premier projet wouhou");
    Menu menu(window.getSize().x, window.getSize().y);
    GraphicalBoard GB;

    int scene = MENU;

    base_test: 
    switch (scene)
    {
    case MENU:
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;
                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;
                       
                    case sf::Mouse::Left:
                    case sf::Keyboard::Return:
                        switch (menu.getPressed())
                        {
                        case 0:
                            scene = PLAY;
                            goto base_test;
                            break;
                        case 1:

                            break;

                        case 2:
                            window.close();
                            break;
                        }
                    }
                    break;


                case sf::Event::Closed:
                    window.close();
                    break;
                }
            }


            window.clear();

            menu.UpdateWithMouse(window);
            menu.draw(window);

            window.display();
        }
        break;

    case PLAY:
        GB.update();
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
						GB.check_mouse(window);
					}
					break;

                case sf::Event::MouseMoved:
                    GB.drag(window);
                    break;
                }
            }

            window.clear();

            GB.draw(window);

            window.display();
        }
    }

    return 0;
}