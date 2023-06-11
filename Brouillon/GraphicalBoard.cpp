#include "GraphicalBoard.h"


GraphicalBoard::GraphicalBoard() : graphical_pieces(8, std::vector<GraphicalPiece*>(8, nullptr)), graphical_moves(8, std::vector<sf::Sprite*>(8, nullptr))
{
	board =
	{
		{-2, -1, 0, 0, 0, 0, 1, 2},
		{-3, -1, 0, 0, 0, 0, 1, 3},
		{-4, -1, 0, 0, 0, 0, 1, 4},
		{-5, -1, 0, 0, 0, 0, 1, 5},
		{-6, -1, 0, 0, 0, 0, 1, 6},
		{-4, -1, 0, 0, 0, 0, 1, 4},
		{-3, -1, 0, 0, 0, 0, 1, 3},
		{-2, -1, 0, 0, 0, 0, 1, 2}
	};

	board_logic = new Board(board);

	if (!texture.loadFromFile("C:\\Users\\yassi\\source\\repos\\Enissays\\Brouillon\\Brouillon\\images\\board.jpg")) std::cout << "Unable to load file";
	sprite.setTexture(texture);


	for (int j = 0; j < 6; j++)
		{
			textures_white[j].loadFromFile("C:\\Users\\yassi\\source\\repos\\Enissays\\Brouillon\\Brouillon\\images\\1x\\w_" + p_names[j] + ".png");
			textures_black[j].loadFromFile("C:\\Users\\yassi\\source\\repos\\Enissays\\Brouillon\\Brouillon\\images\\1x\\b_" + p_names[j] + ".png");
		}

	textures_moves[0].loadFromFile("C:\\Users\\yassi\\source\\repos\\Enissays\\Brouillon\\Brouillon\\images\\possible_move.png");
	textures_moves[1].loadFromFile("C:\\Users\\yassi\\source\\repos\\Enissays\\Brouillon\\Brouillon\\images\\possible_attack.png");

	tiles[0].setTexture(textures_moves[0]);
	tiles[0].setScale(0.17, 0.17);
	tiles[1].setTexture(textures_moves[1]);
	tiles[1].setScale(0.17, 0.17);

	if (!font.loadFromFile("C:\\Users\\yassi\\source\\repos\\Enissays\\Brouillon\\Brouillon\\images\\comic.ttf")) std::cout << "Unable to load file";
	texts[0].setFont(font);
	texts[0].setString("Blanc ");
	texts[0].setCharacterSize(24);
	texts[0].setFillColor(sf::Color::White);
	texts[0].setPosition(texture.getSize().x + 20, 0);

	texts[1].setFont(font);
	texts[1].setString("Noir ");
	texts[1].setCharacterSize(24);
	texts[1].setFillColor(sf::Color::White);
	texts[1].setPosition(texture.getSize().x + 20, 300);

	texts[2].setFont(font);
	texts[2].setCharacterSize(24);
	texts[2].setFillColor(sf::Color::White);
	texts[2].setPosition(texture.getSize().x + 20, 550);
	
}

void GraphicalBoard::update()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			if ((board[i][j] != 10 || board[i][j] < 20) && graphical_moves[i][j] != nullptr)
			{
				delete graphical_moves[i][j];
				graphical_moves[i][j] = nullptr;
				std::cout << "Deleted move at position : " << i << j << std::endl;
			}
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

	if (board_logic->getCheck()) texts[2].setString("Echec");
	else texts[2].setString("");

	if (board_logic->getCheckMate()) texts[2].setString("Echec et mat");
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
			if (graphical_moves[i][j] != nullptr) window.draw(*graphical_moves[i][j]);
		}
	}

	// writes a text to show the turn
	window.draw(texts[0]);
	window.draw(texts[1]);
	window.draw(texts[2]);
	
}

void GraphicalBoard::promote(int x, int y, sf::RenderWindow &window, Piece* selected_piece)
{
	// add the promotion window here with the 4 pieces and the choice
	// align the pieces in the middle of the board

	// add a square in the middle of the board to show the promotion
	sf::RectangleShape rect(sf::Vector2f(texture.getSize().x, texture.getSize().y / 4));
	rect.setPosition(0, texture.getSize().x / 4);
	rect.setFillColor(sf::Color::Black);
	bool chosen = false;

	// add the 4 pieces
	GraphicalPiece *pieces[4];
	for (int i = 0; i < 4; i++)
	{
		pieces[i] = new GraphicalPiece(i * 100 + 100, 150, i+1 ,(board_logic->getTurn() == -1 ? textures_black[i+1] : textures_white[i+1]));
	}

	// check which piece is selected
	while (!chosen)
	{
		window.clear();
		draw(window);
		window.draw(rect);
		
		for (int i = 0; i < 4; i++)
		{
			pieces[i]->draw(window);
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				for (int i = 0; i < 4; i++)
				{
					if (pieces[i]->collides(window))
					{
						selected_piece->id = i + 2;
						chosen = true;
					}
				}
			}
		}
		window.display();
	}
}

void GraphicalBoard::check_mouse(sf::RenderWindow &window)
{
	if (selected_dnd != nullptr) 
	{
		// TODO : check move validity
		unsigned int nx = sf::Mouse::getPosition(window).x / 75 ;
		unsigned int ny = sf::Mouse::getPosition(window).y / 75 ;


		if (selected_piece->checkMove({ int(nx), int(ny) }, *board_logic))
		{
			if ((ny == 7 || ny == 0) && (selected_piece->getId() == 1 || selected_piece->getId() == -1)) promote(nx, ny, window, selected_piece);
			selected_piece->setPos({int(nx),int(ny)}, *board_logic);
			board=board_logic->getTable();
			board[nx][ny] = selected_piece->getId();
			board[selected_dnd->getX()][selected_dnd->getY()] = 0;


			board_logic->switchTurn();
			if (board_logic->getTurn() == 1) {
				texts[0].setFillColor(sf::Color::Red);
				texts[1].setFillColor(sf::Color::White);
			}
			else
			{
				texts[0].setFillColor(sf::Color::White);
				texts[1].setFillColor(sf::Color::Red);
			}

		}
		else selected_dnd->move(initial_pos.x, initial_pos.y);

		selected_dnd = nullptr;
		board_logic->setTable(board);
		update();

	}
	else {
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				// todo : switch and check turn, fix kill moves display and add scores etc.
				if (!board_logic->checkTurn(board_logic->getPiece(i, j))) continue;
				if (graphical_pieces[i][j] != nullptr && graphical_pieces[i][j]->collides(window)) {
					selected_piece = new Piece(graphical_pieces[i][j]->getId(), i, j);
					selected_piece->getMoves(*board_logic, false);

					selected_dnd = graphical_pieces[i][j];
					initial_pos = selected_dnd->getPos();

					board = board_logic->getTable();
					update();

					// each graphical kill
					for (int k = 0; k < selected_piece->kills.size(); k++) {
						int x = selected_piece->kills[k].x;
						int y = selected_piece->kills[k].y;
						graphical_moves[x][y] = new sf::Sprite(tiles[1]);
						graphical_moves[x][y]->setPosition((x * 76.5) + 5, y * 75 + 10);

					}

					// each graphical move
					for (int k = 0; k < selected_piece->moves.size(); k++) {
						int x = selected_piece->moves[k].x;
						int y = selected_piece->moves[k].y;
						graphical_moves[x][y] = new sf::Sprite(tiles[0]);
						graphical_moves[x][y]->setPosition((x * 76.5) + 5, y * 75 + 10);
					}


					break;
				}
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