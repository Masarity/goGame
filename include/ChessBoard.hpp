#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include "ChessPiece.hpp"

class ChessBoard: public sf::Drawable 
{
    friend class GoRule;
public:
    //拒绝拷贝
    /* ChessBoard(const ChessBoard&) = delete; */
    /* ChessBoard& operator=(const ChessBoard&) = delete; */
    //初始化棋盘
    ChessBoard();
    //模板函数，不清楚什么时候使用
    template<typename ... Args>
        void setPosition(Args&& ... args)
        {
            _chessBoard.setPosition(std::forward<Args>(args)...);
        }
    //更新
    void update(sf::Time deltaTime);
    //棋盘坐标与像素坐标的相互转换
    sf::Vector2f pixelToMark(sf::Vector2f& pixelPoint);
    sf::Vector2f markToPixel(sf::Vector2f& markPoint);

private:
    //棋盘属性
    sf::RectangleShape _chessBoard;
    //交错的直线
    std::vector<sf::RectangleShape> _lines;
    sf::RectangleShape _line;
    //让子点
    std::vector<sf::CircleShape> _circles;
    sf::CircleShape _circle;
    //数字（1-19）（1-13）（1-9）
    enum lineNumber
    { 
        nineteen = 19,
        thirteen = 13,
        nine     =  9,
    }chooseLineNumber = nineteen;
    //棋子（黑白棋）
    std::stack<ChessPiece> _whitePiece;
    std::stack<ChessPiece> _blackPiece;   

private:
    //重写渲染虚函数
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
