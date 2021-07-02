#include <iostream>
#include "ChessPiece.hpp"

ChessPiece::ChessPiece(sf::Text pieceNumber, sf::Vector2f piecePosition, sf::Color pieceColor)
{
    _pieceNumber = pieceNumber;
    _pieceColor  = pieceColor;

}

void ChessPiece::update(sf::Time deltaTime)
{
}

void ChessPiece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_pieceCircle, states);
}
