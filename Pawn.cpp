#include "Pawn.h"
#include <iostream>
#include <list>

Pawn::Pawn(Team team, std::pair<int, int> pos, SDL_Handler* handler)
	:Piece(team, pos, handler, PAWN), enPassantMov(std::pair<bool, int>(false, 0))
{
	std::string filename;
	if (team == BLACK)
	{
		filename = "res/black-bpawn2.png";
	}
	else
	{
		filename = "res/white-bpawn2.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);

	if (team == BLACK)
	{
		m_dy = -1;
	}
	else
	{
		m_dy = 1;
	}

	render();
}

void Pawn::callName()
{
	if (m_team == BLACK)
	{
		std::cout << "BLACK PAWN" << std::endl;
	}
	else
	{
		std::cout << "WHITE PAWN" << std::endl;
	}
}

void Pawn::calPosMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<std::tuple<int, int, Piece::MoveType>> moves;

	if (m_pos.second + m_dy == 0 || m_pos.second + m_dy == 7) // check for pawn promotion by see if the pawn is at max collum and there no piece on his way
	{
		if (field[m_pos.first][m_pos.second + m_dy] == nullptr)
		{
			moves = pushMove(moves,
				std::tuple<int, int, Piece::MoveType>(m_pos.first, m_pos.second + m_dy, Piece::NEWPIECE),
				getOwnKing(field),
				field,
				checkCheck);
		}
	}
	else
	{
		if (field[m_pos.first][m_pos.second + m_dy] == nullptr)
		{
			moves = pushMove(moves,
				std::tuple<int, int, Piece::MoveType>(m_pos.first, m_pos.second + m_dy, Piece::NORMAL),
				getOwnKing(field),
				field,
				checkCheck);
		}
	}

	if ((m_pos.second + 2 * m_dy >= 0) && (m_pos.second + 2 * m_dy <= 7))
	{
		if (field[m_pos.first][m_pos.second + 2 * m_dy] == nullptr && !m_hasMoved)
		{
			moves = pushMove(moves,
				std::tuple<int, int, Piece::MoveType>(m_pos.first, m_pos.second + 2 * m_dy, Piece::NORMAL),
				getOwnKing(field),
				field,
				checkCheck);
		}
	}

	if (m_pos.first + 1 <= 7)
	{
		if (field[m_pos.first + 1][m_pos.second + m_dy] != nullptr)
		{
			if (field[m_pos.first + 1][m_pos.second + m_dy]->getTeam() != m_team)
			{
				if (m_pos.second + m_dy == 0 || m_pos.second + m_dy == 7)
				{
					moves = pushMove(moves,
						std::tuple<int, int, Piece::MoveType>(m_pos.first + 1, m_pos.second + m_dy, Piece::NEWPIECE),
						getOwnKing(field),
						field,
						checkCheck);
				}
				else
				{
					moves = pushMove(moves,
						std::tuple<int, int, Piece::MoveType>(m_pos.first + 1, m_pos.second + m_dy, Piece::NORMAL),
						getOwnKing(field),
						field,
						checkCheck);
				}
			}
		}
	}
	if (m_pos.first - 1 >= 0)
	{
		if (field[m_pos.first - 1][m_pos.second + m_dy] != nullptr)
		{
			if (field[m_pos.first - 1][m_pos.second + m_dy]->getTeam() != m_team)
			{
				if (m_pos.second + m_dy == 0 || m_pos.second + m_dy == 7)
				{
					moves = pushMove(moves,
						std::tuple<int, int, Piece::MoveType>(m_pos.first - 1, m_pos.second + m_dy, Piece::NEWPIECE),
						getOwnKing(field),
						field,
						checkCheck);
				}
				else
				{
					moves = pushMove(moves,
						std::tuple<int, int, Piece::MoveType>(m_pos.first - 1, m_pos.second + m_dy, Piece::NORMAL),
						getOwnKing(field),
						field,
						checkCheck);
				}
			}
		}
	}

	if (enPassantMov == std::pair<bool, int>(true, -1))
	{
		moves = pushMove(moves,
			std::tuple<int, int, Piece::MoveType>(m_pos.first + 1, m_pos.second + m_dy, Piece::ENPASSANT),
			getOwnKing(field),
			field,
			checkCheck);
	}
	if (enPassantMov == std::pair<bool, int>(true, 1))
	{
		moves = pushMove(moves,
			std::tuple<int, int, Piece::MoveType>(m_pos.first - 1, m_pos.second + m_dy, Piece::ENPASSANT),
			getOwnKing(field),
			field,
			checkCheck);
	}
	mPosMoves = moves;
}






