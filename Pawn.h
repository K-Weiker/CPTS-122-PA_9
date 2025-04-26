#pragma once
#include "Piece.h"

class Pawn :
    public Piece
{
public:
    // constructor
    Pawn(Team team, std::pair<int, int> pos, SDL_Handler* handler);

    // prints name of piece
    void callName();

    // calculates possible moves
    void calPosMoves(Piece* field[8][8], bool checkCheck);

    // direction the pawn moves
    int m_dy;

    // getter enPassantMov
    std::pair<bool, int> getEnPassant() { return enPassantMov; };

    // set enPassantMov
    void setEnPassant(std::pair<bool, int> modifi) { enPassantMov = modifi; };

private:
    // if true, en passant is possible in the int direction
    std::pair<bool, int> enPassantMov;
};

