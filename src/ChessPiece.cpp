#include <iostream>
#include "ChessPiece.hpp"
#define PIECE_ARGS 5
#include "Locals.h"

ChessPiece::ChessPiece()
{
    _pieceCircle.setFillColor(_pieceColor);
    _pieceCircle.setRadius(PIECE_RADIUS);
    _raduis = PIECE_RADIUS;

}

void ChessPiece::update(sf::Time deltaTime)
{
}

void ChessPiece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_pieceCircle, states);
}
