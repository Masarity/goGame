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
    float propotion = (float) (nineteen -1) / (_chooseLineNumber - 1);
    for (int line_id=1; line_id <= _chooseLineNumber; line_id++)
    {
        _line.setFillColor(BLACK);
        _line.setSize(LEVEL_LINE_THICKNESS);
        _line.setPosition(sf::Vector2f(BOARD_OFFSET + LINE_OFFSET * (1 + propotion * (line_id - 1)), BOARD_OFFSET + LINE_OFFSET));
        _lines.push_back(_line);
        _line.setSize(VERTICAL_LINE_THICKNESS);
        _line.setPosition(sf::Vector2f(BOARD_OFFSET + LINE_OFFSET, BOARD_OFFSET + LINE_OFFSET * (1 + propotion * (line_id - 1))));
        _lines.push_back(_line);
    }

    //棋盘让子点的配置
    _circles.reserve(nine);
    float circle_x_offset=BOARD_OFFSET + LINE_OFFSET + CIRCLE_OFFSET, circle_y_offset=BOARD_OFFSET + LINE_OFFSET + CIRCLE_OFFSET;
    float circle_x, circle_y;
    int circle_points_19[] = CIRCLE_POINTS_19;
    int circle_points_9[] = CIRCLE_POINTS_9;
    int circle_points_13[] = CIRCLE_POINTS_13;
    _circle.setFillColor(BLACK);
    _circle.setRadius(CIRCLE_RADIUS);
    for (int circle_level_id=0; circle_level_id < 3; circle_level_id++)
    {
        for (int circle_vertical_id=0; circle_vertical_id < 3; circle_vertical_id++)
        {
            switch (_chooseLineNumber)
            {
            case nineteen:
                circle_x = circle_x_offset + LINE_OFFSET * circle_points_19[circle_level_id]     * propotion;
                circle_y = circle_y_offset + LINE_OFFSET * circle_points_19[circle_vertical_id]  * propotion;
                _circle.setPosition(circle_x, circle_y);
                break;
            case thirteen:
                circle_x = circle_x_offset + LINE_OFFSET * circle_points_13[circle_level_id]     * propotion;
                circle_y = circle_y_offset + LINE_OFFSET * circle_points_13[circle_vertical_id]  * propotion;
                _circle.setPosition(circle_x, circle_y);
                break;
            case nine:
                circle_x = circle_x_offset + LINE_OFFSET * circle_points_9[circle_level_id]      * propotion;
                circle_y = circle_y_offset + LINE_OFFSET * circle_points_9[circle_vertical_id]   * propotion;
                _circle.setPosition(circle_x, circle_y);
                break;
            }
            _circles.push_back(_circle);
        }
    }
}

sf::Vector2f ChessBoard::markToPixel(sf::Vector2f& markPoint, float propotion)
{
    float offset_small = propotion * 5;
    int   offset_big   = propotion == 1 ? 0 : propotion == 1.5 ? 20 : 50;
    return sf::Vector2f(LINE_OFFSET * propotion *markPoint.x - (offset_small + offset_big) , LINE_OFFSET * propotion * markPoint.y - (offset_small + offset_big));    
}

void ChessBoard::update(sf::Time deltaTime)
{

}



void ChessBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_chessBoard, states);
    //绘制直线
    forEach(_lines)          target.draw(*iter, states);
    //绘制让子圆
    forEach(_circles)        target.draw(*iter, states);
    //绘制棋子
    forEach(_whitePieces)    target.draw((*iter), states);
    forEach(_blackPieces)    target.draw((*iter), states);
}
