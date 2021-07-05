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
}

void ChessPiece::update(sf::Time deltaTime)
{
}

void ChessPiece::isNumberVisible(bool isVisible)
{
    _isNumberVisible = isVisible;
}

void ChessPiece::isQiVisible(bool isVisible)
{
    _isQiVisible = isVisible;
}

void ChessPiece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //绘制棋子和棋子的数字
    target.draw(_pieceCircle, states);
    if (_isNumberVisible)
        target.draw(_text,    states);
    if (_isQiVisible)
        target.draw(_pieceQi, states);
}
