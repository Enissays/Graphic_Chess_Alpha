#include "GraphicalBoard.h"

GraphicalBoard::GraphicalBoard() : graphical_pieces(8, std::vector<GraphicalPiece*>(8, nullptr))
{
	board =     { 
        {-2, -1, 0, 0, 0, 0, 1, 2},
        {-3, -1, 0, 0, 0, 0, 1, 3},
        {-4, -1, 0, 0, 0, 0, 1, 4},
        {-5, -1, 0, 0, 0, 0, 1, 5},
        {-6, -1, 0, 0, 0, 0, 1, 6},
        {-4, -1, 0, 0, 0, 0, 1, 4},
        {-3, -1, 0, 0, 0, 0, 1, 3},
        {-2, -1, 0, 0, 0, 0, 1, 2}
    };

	if (!texture.loadFromFile("C:\\Users\\yassi\\source\\repos\\Enissays\\Brouillon\\Brouillon\\images\\board.jpg")) std::cout << "Unable to load file";
	sprite.setTexture(texture);


	for (int j = 0; j < 6; j++)
		{
			textures_white[j].loadFromFile("C:\\Users\\yassi\\source\\repos\\Enissays\\Brouillon\\Brouillon\\images\\1x\\w_" + p_names[j] + ".png");
			textures_black[j].loadFromFile("C:\\Users\\yassi\\source\\repos\\Enissays\\Brouillon\\Brouillon\\images\\1x\\b_" + p_names[j] + ".png");
		}
	
}

void GraphicalBoard::update()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			// todo fix conditions here
			if (board[i][j] == 0 && graphical_pieces[i][j] != nullptr) {
				delete graphical_pieces[i][j];
				graphical_pieces[i][j] = nullptr;
				std::cout << "Deleted sprite at position : " << i << j << std::endl;
			}

				else if (board[i][j] != (graphical_pieces[i][j] != nullptr ? graphical_pieces[i][j]->getId() : 0))
				{
					int id = board[i][j];
					//std::cout << "ID : " << id << "; = " << p_names[id-1] << std::endl;
					GraphicalPiece* gPiece = new GraphicalPiece(i, j, id, id < 0 ? textures_black[-(id+1)] : textures_white[id-1], texture);
					graphical_pieces[i][j] = gPiece;
				}
			
		}
	}
}

GraphicalBoard::~GraphicalBoard()
{

}

void GraphicalBoard::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (graphical_pieces[i][j] != nullptr) graphical_pieces[i][j]->draw(window);
		}
	}
}

void GraphicalBoard::check_mouse(sf::RenderWindow &window)
{
	if (selected_dnd != nullptr) 
	{
		// remove it from its previous position and add it to its new one
		board[selected_dnd->getX()][selected_dnd->getY()] = 0;
		int mx = sf::Mouse::getPosition(window).x;
		int my = sf::Mouse::getPosition(window).y;
		unsigned int nx = sf::Mouse::getPosition(window).x / 100 ;
		unsigned int ny = sf::Mouse::getPosition(window).y / 75 ;
		board[nx][ny] = selected_dnd->getId();

		selected_dnd = nullptr;
		update();
	}
	else {
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (graphical_pieces[i][j] != nullptr && graphical_pieces[i][j]->collides(window)) selected_dnd = graphical_pieces[i][j];
			}
		}
	}
}

void GraphicalBoard::drag(sf::RenderWindow &window)
{
	if (selected_dnd != nullptr)
	{
		selected_dnd->move(sf::Mouse::getPosition(window).x - 40, sf::Mouse::getPosition(window).y - 40);
	}
}