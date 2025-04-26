#include "King.h"
#include "Pawn.h"
#include <iostream>
#include <stdlib.h>

King::King(Team team, std::pair<int, int> pos, SDL_Handler* handler)
	:Piece(team, pos, handler, KING), m_check(false)
{
	std::string filename;
	if (team == BLACK)
	{
		filename = "res/black-nrking.png";
	}
	else
	{
		filename = "res/white-king.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);

	render();
}

void King::callName()
{
	if (m_team == BLACK)
	{
		std::cout << "BLACK KING" << std::endl;
	}
	else
	{
		std::cout << "WHTIE KING" << std::endl;
	}
}

void King::calPosMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<std::tuple<int, int, Piece::MoveType>> moves;

	// Normal 1-square moves in all directions
	for (int dx = -1; dx <= 1; ++dx)
	{
		for (int dy = -1; dy <= 1; ++dy)
		{
			if (dx == 0 && dy == 0) continue;

			int x = m_pos.first + dx;
			int y = m_pos.second + dy;

			if (x >= 0 && x <= 7 && y >= 0 && y <= 7)
			{
				Piece* target = field[x][y];
				if (target == nullptr || target->getTeam() != m_team)
				{
					moves = pushMove(moves, { x, y, Piece::NORMAL }, getOwnKing(field), field, checkCheck);
				}
			}
		}
	}

	// Castling (if King hasn't moved)
	if (!m_hasMoved)
	{
		int row = m_pos.second;

		// Queenside
		Piece* leftRook = field[0][row];
		if (leftRook && leftRook->getType() == ROOK && leftRook->getTeam() == m_team && !leftRook->m_hasMoved)
		{
			if (field[1][row] == nullptr && field[2][row] == nullptr && field[3][row] == nullptr)
			{
				moves.emplace_back(0, row, Piece::CASTLE);
			}
		}

		// Kingside
		Piece* rightRook = field[7][row];
		if (rightRook && rightRook->getType() == ROOK && rightRook->getTeam() == m_team && !rightRook->m_hasMoved)
		{
			if (field[5][row] == nullptr && field[6][row] == nullptr)
			{
				moves.emplace_back(7, row, Piece::CASTLE);
			}
		}
	}

	mPosMoves = moves;
}

void King::setCheck(Piece* field[8][8], int x, int y)
{
	bool check = false;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (field[i][j] != nullptr)
			{
				if (field[i][j]->getTeam() != m_team)
				{
					if (field[i][j]->getType() == KING)
					{
						if (abs(field[i][j]->getPos().first - x) <= 1 && abs(field[i][j]->getPos().second - y) <= 1)
						{
							check = true;
						}

					}
					else if (field[i][j]->getType() == PAWN)
					{
						int dy_pawn;
						if (field[i][j]->getTeam() == WHITE)
						{
							dy_pawn = 1;
						}
						else
						{
							dy_pawn = -1;
						}
						if ((x == field[i][j]->getPos().first + 1 || x == field[i][j]->getPos().first - 1) && y == field[i][j]->getPos().second + dy_pawn)
						{
							check = true;
						}
					}
					else
					{
						field[i][j]->calPosMoves(field, false);
						std::vector<std::tuple<int, int, Piece::MoveType>> notPossible = field[i][j]->getPossibleMoves();
						for (const auto& value : notPossible)
						{
							if (std::get<0>(value) == x && std::get<1>(value) == y)
							{
								check = true;
							}
						}
					}
				}
			}
		}
	}

	m_check = check;
}
