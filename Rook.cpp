#include "Rook.h"
#include <iostream>

Rook::Rook(Team team, std::pair<int, int> pos, SDL_Handler* handler)
	:Piece(team, pos, handler, ROOK)
{
	std::string filename;
	if (team == BLACK)
	{
		filename = "res/black-rook4.png";
	}
	else
	{
		filename = "res/white-rook4.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);

	render();
}

void Rook::callName()
{
	if (m_team == BLACK)
	{
		std::cout << "BLACK ROOK" << std::endl;
	}
	else
	{
		std::cout << "WHITE ROOK" << std::endl;
	}
}

void Rook::calPosMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<std::tuple<int, int, Piece::MoveType>> moves;

	// Rook moves in straight lines: up, down, left, right
	int directions[4][2] = {
		{  0, -1 }, // Up
		{  0,  1 }, // Down
		{ -1,  0 }, // Left
		{  1,  0 }  // Right
	};

	for (auto& dir : directions)
	{
		int x = m_pos.first + dir[0];
		int y = m_pos.second + dir[1];

		// Slide in the direction while empty
		while (x >= 0 && x <= 7 && y >= 0 && y <= 7 && field[x][y] == nullptr)
		{
			moves = pushMove(
				moves,
				{ x, y, Piece::NORMAL },
				getOwnKing(field),
				field,
				checkCheck
			);
			x += dir[0];
			y += dir[1];
		}

		// Capture if enemy piece is found
		if (x >= 0 && x <= 7 && y >= 0 && y <= 7)
		{
			Piece* target = field[x][y];
			if (target != nullptr && target->getTeam() != m_team)
			{
				moves = pushMove(
					moves,
					{ x, y, Piece::NORMAL },
					getOwnKing(field),
					field,
					checkCheck
				);
			}
		}
	}

	mPosMoves = moves;
}


Rook::~Rook()
{
}
