#include <iostream>
#include <algorithm>
#include "ChessBoard.hpp"
#define INITIAL_BOARD 1
#include "Constants.h"

ChessBoard::ChessBoard()
{
    //棋盘的大小、颜色、位置
    _chessBoard.setSize(sf::Vector2f(BOARD_WIDTH, BOARD_HEIGHT));
    _chessBoard.setPosition(BOARD_OFFSET, BOARD_OFFSET);
    _chessBoard.setFillColor(BOARD_COLOR);
    _chessBoard.setOutlineThickness(BOARD_OFFSET);
    _chessBoard.setOutlineColor(WHITE_ALPHA);

    //棋盘直线的配置
    _lines.reserve(_chooseLineNumber * 2);
    //获得棋盘比例
    _propotion = (float) (nineteen -1) / (_chooseLineNumber - 1);
    _line.setFillColor(BLACK);
    for (int line_id=1; line_id <= _chooseLineNumber; line_id++)
    {
        //水平线
        _line.setSize(LEVEL_LINE_THICKNESS);
        _line.setPosition(sf::Vector2f(BOARD_OFFSET + LINE_OFFSET * (1 + _propotion * (line_id - 1)), BOARD_OFFSET + LINE_OFFSET));
        _lines.push_back(_line);
        //竖直线
        _line.setSize(VERTICAL_LINE_THICKNESS);
        _line.setPosition(sf::Vector2f(BOARD_OFFSET + LINE_OFFSET, BOARD_OFFSET + LINE_OFFSET * (1 + _propotion * (line_id - 1))));
        _lines.push_back(_line);
    }

    //棋盘让子点的配置
    _handicapCircles.reserve(nine);
    //起点偏移
    float circle_x_offset=BOARD_OFFSET + LINE_OFFSET + CIRCLE_OFFSET, circle_y_offset=BOARD_OFFSET + LINE_OFFSET + CIRCLE_OFFSET;
    //圆左上角坐标
    float circle_x, circle_y;
    //每种线数棋盘间距不同：（效果不是很理想（~**~）
    int circle_points_19[] = CIRCLE_POINTS_19;
    int circle_points_9[] = CIRCLE_POINTS_9;
    int circle_points_13[] = CIRCLE_POINTS_13;
    //让子点的配置
    _handicapCircle.setFillColor(BLACK);
    _handicapCircle.setRadius(CIRCLE_RADIUS);
    for (int circle_level_id=0; circle_level_id < 3; circle_level_id++)
    {
        for (int circle_vertical_id=0; circle_vertical_id < 3; circle_vertical_id++)
        {
            switch (_chooseLineNumber)
            {
            case nineteen:
                //圆左上角计算公式：起点偏移＋间距*间距数*棋盘比例
                circle_x = circle_x_offset + LINE_OFFSET * circle_points_19[circle_level_id]     * _propotion;
                circle_y = circle_y_offset + LINE_OFFSET * circle_points_19[circle_vertical_id]  * _propotion;
                _handicapCircle.setPosition(circle_x, circle_y);
                //顺便配置标记点
                _markPoint = MARK_POINTS_19;
                break;
            case thirteen:
                circle_x = circle_x_offset + LINE_OFFSET * circle_points_13[circle_level_id]     * _propotion;
                circle_y = circle_y_offset + LINE_OFFSET * circle_points_13[circle_vertical_id]  * _propotion;
                _handicapCircle.setPosition(circle_x, circle_y);
                _markPoint = MARK_POINTS_13;
                break;
            case nine:
                circle_x = circle_x_offset + LINE_OFFSET * circle_points_9[circle_level_id]      * _propotion;
                circle_y = circle_y_offset + LINE_OFFSET * circle_points_9[circle_vertical_id]   * _propotion;
                _handicapCircle.setPosition(circle_x, circle_y);
                _markPoint = MARK_POINTS_9;
                break;
            }
            _handicapCircles.push_back(_handicapCircle);
        }
    }
}

sf::Vector2f ChessBoard::markToPixel(sf::Vector2f& markPoint)
{
    //坐标转换公式：小偏移为棋盘比例*5 + 大偏移为0、20、50；（需要修改的）
    float offset_small = _propotion * 5;
    int   offset_big   = _propotion == 1 ? 0 : _propotion == 1.5 ? 20 : 50;
    return sf::Vector2f(LINE_OFFSET * _propotion * markPoint.x - (offset_small + offset_big) , LINE_OFFSET * _propotion * markPoint.y - (offset_small + offset_big));    
}

sf::Vector2f ChessBoard::pixelToMark(sf::Vector2f& pixelPoint)
{
    //将上面的公式反一反
    float offset_small = _propotion * 5;
    int offset_big     = _propotion == 1 ? 0 : _propotion == 1.5 ? 20 : 50;
    return sf::Vector2f((int)((pixelPoint.x + (offset_small + offset_big))/(LINE_OFFSET * _propotion)), (int)((pixelPoint.y + (offset_small + offset_big))/(LINE_OFFSET * _propotion)));
}

ChessPiece* ChessBoard::findChessPiece(sf::Vector2f markPoint)
{
    int key = (int)markPoint.x + (int)markPoint.y * 10;
    auto piece_black = _blackPieces.find(key);
    auto piece_white = _whitePieces.find(key);
    if (piece_black != _blackPieces.end())
    {
        return &(*piece_black).second;
    }
    if (piece_white != _whitePieces.end())
    {
        return &(*piece_white).second;
    }
    return nullptr;
}

void ChessBoard::update(sf::Time deltaTime)
{

}



void ChessBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //绘制棋盘
    target.draw(_chessBoard, states);
    //绘制直线
    forEach(_lines)          target.draw(*iter, states);
    //绘制让子圆
    forEach(_handicapCircles)        target.draw(*iter, states);
    //绘制棋子
    forEach(_whitePieces)    target.draw((*iter).second, states);
    forEach(_blackPieces)    target.draw((*iter).second, states);
}
