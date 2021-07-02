#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class ChessPiece: public sf::Drawable
{
//公共成员函数
public:
    ChessPiece(sf::Text pieceNumber, sf::Vector2f piecePosition, sf::Color pieceColor);
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
    //表示棋子的圆
    sf::CircleShape _pieceCircle;
    //棋子的像素坐标
    sf::Vector2f _pixelPoint;
    //棋子的棋盘坐标
    sf::Vector2f _markPoint;
    //棋子的颜色
    sf::Color _pieceColor;

private:
    //重写虚函数
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


