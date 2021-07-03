#include <iostream>
#include "ChessPiece.hpp"
#define PIECE_ARGS 5
#include "Constants.h"

ChessPiece::ChessPiece()
{
    _pieceCircle.setFillColor(_pieceColor);
    _pieceCircle.setRadius(PIECE_RADIUS);
    _raduis = PIECE_RADIUS;
    bool loadSuccess = _myFont.loadFromFile("../res/fonts/FreeSans.ttf");
    if (!loadSuccess)   std::cout << "载入字体失败~" << std::endl;
    else std::cout << "载入字体成功~" << std::endl;
    _text.setFont(_myFont);
    /* _text.setFillColor(_pieceColor); */
}

void ChessPiece::update(sf::Time deltaTime)
{
}

void ChessPiece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_pieceCircle, states);
    target.draw(_text,        states);
}
