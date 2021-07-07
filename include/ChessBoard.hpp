#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "ChessPiece.hpp"

class ChessBoard: public sf::Drawable 
{
    //友元类->围棋规则类
    friend class GoRule;
public:
    //拒绝拷贝(拷贝真bang)
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
    //更新(做动画效果)
    void update(sf::Time deltaTime);
    //棋盘坐标与像素坐标的相互转换
    sf::Vector2f pixelToMark(sf::Vector2f& pixelPoint);
    sf::Vector2f markToPixel(sf::Vector2f& markPoint);
    //查找棋盘上对应点的棋子（map查找）key是标记坐标
    ChessPiece* findChessPiece(sf::Vector2f markPoint);
    ChessPiece* findChessPiece(int key);

private:
    //棋盘属性
    sf::RectangleShape _chessBoard;
    //交错的直线
    std::vector<sf::RectangleShape> _lines;
    sf::RectangleShape _line;
    //让子点
    std::vector<sf::CircleShape> _handicapCircles;
    sf::CircleShape _handicapCircle;
    //三种棋盘的线数
    enum lineNumber
    { 
        nineteen = 19,
        thirteen = 13,
        nine     =  9,
    }_chooseLineNumber = nineteen;
    //线数不同导致的比例改变
    float _propotion = 1;
    //下子点的标记坐标
    std::string _markPoint;
    //棋子（黑白棋）
    std::map<int, ChessPiece> _whitePieces;
    std::map<int, ChessPiece> _blackPieces;   

private:
    //重写渲染虚函数
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
