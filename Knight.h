#pragma once
#include "Piece.h"

class Knight :
    public Piece
{
public:
    Knight(Team team, std::pair<int, int> pos, SDL_Handler* handler);

    // calls name an
    void callName();

    // calculates the possible moves
    void calPosMoves(Piece* field[8][8], bool checkCheck);
};

