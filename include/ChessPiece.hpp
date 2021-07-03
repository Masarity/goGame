#pragma once
#include <iostream>
#define TRANSPARENT_PIECE sf::Color(0, 0, 0, 0)
#include <SFML/Graphics.hpp>

class ChessPiece: public sf::Drawable
{
    friend class ChessBoard;
    friend class GoRule;
//公共成员函数
public:
    //初始化：棋子序号、棋子位置（像素坐标）、颜色、棋盘类型（19、13、9）
    /* ChessPiece(sf::Text pieceNumber, sf::Vector2f piecePosition, sf::Color pieceColor, int boardKind); */
    ChessPiece();
    template<typename ... Args>
        void setPosition(Args&& ... args)
        {

        }
    void update(sf::Time deltaTime);

//私有成员变量
private:
    //棋子的编号（记录顺序）
    sf::Font _myFont;
    sf::Text _pieceNumber;
    //棋子的半径
    float _raduis;
    //表示棋子的圆
    sf::CircleShape _pieceCircle;
    //棋子的像素坐标
    sf::Vector2f _pixelPoint;
    //棋子的棋盘坐标
    sf::Vector2f _markPoint;
    //棋子的颜色
    sf::Color _pieceColor = TRANSPARENT_PIECE;
    //棋子的气（是不是可以写一个气的类~）

private:
    //重写虚函数
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


