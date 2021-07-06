#include <iostream>
#include "PieceQi.hpp"
#define INITIAL_QI 7
#include "Constants.h"


PieceQi::PieceQi()
{
    _raduis = QI_RADIUS;
    _qiShapes.reserve(4);
}

std::map<int, bool>* PieceQi::initializeQi(sf::Vector2f pieceMarkPoint, bool player, float propotion)
{
    _propotion = propotion;
    //气的颜色
    _qiColor = player ? BLACK_QI_COLOR : WHITE_QI_COLOR;
    //究极关键，避免内存泄漏，保证气的状态正确
    _qiShapes.clear();
    _pieceQi.clear();
    //用于判断气是否显示在棋盘内
    sf::Vector2f validPosition;
    //气的参数配置
    for (int i = 0; i<4; i++)
    {
        _qiCircle.setFillColor(_qiColor);
        //需要进行一波坐标转换
        validPosition = sf::Vector2f(pieceMarkPoint.x + _qiOffset[i][0], pieceMarkPoint.y + _qiOffset[i][1]);
        _qiCircle.setPosition(markToPixel(validPosition));
        _qiCircle.setRadius(_raduis * propotion);
        _qiShapes.push_back(_qiCircle);
        _pieceQi.insert(std::pair<int, bool>(i, (validPosition.x > 0 && validPosition.y > 0) && (validPosition.x < 20 && validPosition.y < 20) ? true : false));
    }
    return &_pieceQi;
}

void PieceQi::setTrue()
{
    sf::Vector2f validPosition;
    forEach( _pieceQi )
    {
        //拿到四个气的像素坐标，然后转成标记坐标
        validPosition = pixelToMark(sf::Vector2f(_qiShapes.at((*iter).first).getPosition().x, _qiShapes.at((*iter).first).getPosition().y));
        //气不能超出棋盘
        (*iter).second = (validPosition.x > 0 && validPosition.y > 0) && (validPosition.x < 20 && validPosition.y < 20) ? true : false;
    }
}


bool PieceQi::isQiExistence()
{
    forEach( _pieceQi )
    {
        if ((*iter).second)
            return true;
    }
    return false;
}


sf::Vector2f PieceQi::markToPixel(sf::Vector2f markPoint)
{
    //公式照旧
    float pixelPoint_x = BOARD_OFFSET + CIRCLE_OFFSET + markPoint.x * LINE_OFFSET * _propotion,
          pixelPoint_y = BOARD_OFFSET + CIRCLE_OFFSET + markPoint.y * LINE_OFFSET * _propotion; 
    return sf::Vector2f(pixelPoint_x, pixelPoint_y);

}

sf::Vector2f PieceQi::pixelToMark(sf::Vector2f pixelPoint)
{
    float markPoint_x = (pixelPoint.x -(BOARD_OFFSET + CIRCLE_OFFSET))/(LINE_OFFSET * _propotion),
          markPoint_y = (pixelPoint.y -(BOARD_OFFSET + CIRCLE_OFFSET))/(LINE_OFFSET * _propotion);
    return sf::Vector2f(markPoint_x, markPoint_y);
}


void PieceQi::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    forEach(_pieceQi)
    {
        //有气则显示
        if ((*iter).second)
            target.draw(_qiShapes.at((*iter).first), states);
    }
}
