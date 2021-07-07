#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>


class PieceQi: public sf::Drawable
{
    //友元交给规则类控制
    friend class ChessPiece;
    friend class GoRule;
public:
    PieceQi();
    
    //初始化函数
    std::map<int, bool>* initializeQi(sf::Vector2f pieceMarkPoint, bool player, float propotion);

    //对于气的坐标变换
    sf::Vector2f markToPixel(sf::Vector2f markPoint);
    sf::Vector2f pixelToMark(sf::Vector2f pixelPoint);

    //将四个方位的气都显示为真
    void setTrue();

    //判断棋子是否还有气
    int isQiExistence();


private:
    //对应棋子的标记位置
    sf::Vector2f _pieceMarkPoint;
    //气的颜色
    sf::Color _qiColor;
    //气的偏移向量
    int _qiOffset[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    //气的形状
    sf::CircleShape _qiCircle;
    //比例
    float _propotion;
    //半径
    float _raduis;
    //4个方位气的vector容器
    std::vector<sf::CircleShape> _qiShapes;
    //map容器用于判断是否显示气
    std::map<int, bool> _pieceQi;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

