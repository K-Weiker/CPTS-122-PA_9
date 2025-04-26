#include "Queen.h"
#include <iostream>

Queen::Queen(Team team, std::pair<int, int> pos, SDL_Handler* handler)
	:Piece(team, pos, handler, QUEEN)
{
	std::string filename;
	if (team == BLACK)
	{
		filename = "res/black-grassh.png";
	}
	else
	{
		filename = "res/white-grassh.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);
	render();
}


void Queen::callName()
{
	if (m_team == BLACK)
	{
		std::cout << "BLACK QUEEN" << std::endl;
	}
	else
	{
		std::cout << "WHTIE QUEEN" << std::endl;
	}
}

void Queen::calPosMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<std::tuple<int, int, Piece::MoveType>> moves;

	// Queen moves in 8 directions: horizontal, vertical, diagonal
	int directions[8][2] = {
		{ 1,  0}, { -1,  0}, // Right, Left
		{ 0,  1}, {  0, -1}, // Down, Up
		{ 1,  1}, { -1, -1}, // Down-right, Up-left
		{ 1, -1}, { -1,  1}  // Up-right, Down-left
	};

	for (auto& dir : directions)
	{
		int x = m_pos.first + dir[0];
		int y = m_pos.second + dir[1];

		// Move until hit the board edge or another piece
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

		// If enemy piece is there, add capture move
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
