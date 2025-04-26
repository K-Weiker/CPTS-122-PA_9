#include "Knight.h"
#include <iostream>

Knight::Knight(Team team, std::pair<int, int> pos, SDL_Handler* handler)
	:Piece(team, pos, handler, KNIGHT)
{
	std::string filename;
	if (team == BLACK)
	{
		filename = "res/black-nightrd.png";
	}
	else
	{
		filename = "res/white-nightrd.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);
	render();
}

void Knight::callName()
{
	if (m_team == BLACK)
	{
		std::cout << "BLACK KNIGHT" << std::endl;
	}
	else
	{
		std::cout << "WHTIE KNIGHT" << std::endl;
	}
}

void Knight::calPosMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<std::tuple<int, int, Piece::MoveType>> moves;

	// All possible L-shaped moves for a knight
	const int offsets[8][2] = {
		{-2, -1}, {-2,  1}, { 2, -1}, { 2,  1},
		{-1, -2}, { 1, -2}, {-1,  2}, { 1,  2}
	};

	for (const auto& offset : offsets)
	{
		int x = m_pos.first + offset[0];
		int y = m_pos.second + offset[1];

		if (x >= 0 && x <= 7 && y >= 0 && y <= 7)
		{
			Piece* target = field[x][y];
			if (target == nullptr || target->getTeam() != m_team)
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
