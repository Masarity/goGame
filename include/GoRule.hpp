#pragma once
#include <SFML/Graphics.hpp>
#include "ChessBoard.hpp"

class GoRule: public sf::Drawable
{
public:
    GoRule(ChessBoard* chessBoard);
    void showBoardLineNumber();
    void showAlphaPiece(sf::Event::MouseMoveEvent& mouse);

private:
    ChessBoard* _myChessBoardPoint;
    //显示悬停的棋子
    ChessPiece _alphaPiece;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
