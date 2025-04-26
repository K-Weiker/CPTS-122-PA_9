#include "Bishop.h"
#include <iostream>

Bishop::Bishop(Team team, std::pair<int, int> pos, SDL_Handler* handler)
	:Piece(team, pos, handler, BISHOP)
{
	std::string filename;
	if (team == BLACK)
	{
		filename = "res/black-bishop.png";
	}
	else
	{
		filename = "res/white-bishop.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);
	render();
}

void Bishop::callName()
{
	if (m_team == BLACK)
	{
		std::cout << "BLACK BISHOP" << std::endl;
	}
	else
	{
		std::cout << "WHTIE BISHOP" << std::endl;
	}
}

void Bishop::calPosMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<std::tuple<int, int, Piece::MoveType>> moves;

	// Bishop moves in 4 diagonal directions
	const int directions[4][2] = {
		{  1,  1 },  // down-right
		{  1, -1 },  // up-right
		{ -1,  1 },  // down-left
		{ -1, -1 }   // up-left
	};

	for (const auto& dir : directions)
	{
		int x = m_pos.first + dir[0];
		int y = m_pos.second + dir[1];

		// Slide until blocked
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

		// Capture if enemy piece at end
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


