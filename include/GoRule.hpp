#pragma once
#include <SFML/Graphics.hpp>
#include "ChessBoard.hpp"

class GoRule: public sf::Drawable
{
public:
    GoRule(ChessBoard* chessBoard);
    //测试函数
    void showBoardLineNumber();
    //检查光标下是否有棋子，若没有则显示悬停棋子
    void isPieceUnderCursor(sf::Event::MouseMoveEvent& mouse);
    //添加棋子到棋盘->把悬停棋子改个颜色，添加到棋盘对应的vector数组里,添加成功返回true
    bool addPieceToChessBoard();

private:
    ChessBoard* _myChessBoardPoint;
    //保存光标的标记坐标
    sf::Vector2f _markPoint;
    //是否显示悬停棋子bool量
    bool _showAlphaPiece = false;
    //悬停的棋子对象
    ChessPiece _alphaPiece;
    //棋子计数
    int _pieceCount = 0;
    //棋手颜色(true -> black; false -> white)
    bool _player = true;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
