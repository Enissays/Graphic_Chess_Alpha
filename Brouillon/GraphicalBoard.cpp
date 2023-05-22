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

	if (!texture.loadFromFile("..\\..\\..\\..\\OneDrive\\Bureau\\images\\board.jpg")) std::cout << "Unable to load file";
	sprite.setTexture(texture);


	for (int j = 0; j < 6; j++)
		{
			textures_white[j].loadFromFile("C:\\Users\\yassi\\OneDrive\\Bureau\\images\\1x\\w_" + p_names[j] + ".png");
			textures_black[j].loadFromFile("C:\\Users\\yassi\\OneDrive\\Bureau\\images\\1x\\b_" + p_names[j] + ".png");
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