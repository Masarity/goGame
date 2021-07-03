#include <iostream>
#define INITIAL_RULE 3
#include "Locals.h"
#include "GoRule.hpp"

GoRule::GoRule(ChessBoard* chessBoard)
{
    //拿到棋盘的指针，操作它（应用之后的规则）
    _myChessBoardPoint = chessBoard;
}

void GoRule::showAlphaPiece(sf::Event::MouseMoveEvent& mouse)
{
    float propotion = (float)NINETEEN / _myChessBoardPoint->_chooseLineNumber;
    float division = BASE_DIVISION_30 * propotion;
    //显示悬停棋子的范围
    if ((mouse.x > 25 && mouse.x < 595)&&(mouse.y > 25 && mouse.y < 595))
    {
        //起始点
        int basePoint_x = mouse.x / division, basePoint_y = mouse.y / division;
        //进位判断
        int carry_x = mouse.x % (int)division, carry_y = mouse.y % (int)division;
        //获得棋子的标记坐标
        int piecePoint_x = basePoint_x + (carry_x > 25 * propotion ? 1 : 0);
        int piecePoint_y = basePoint_y + (carry_y > 25 * propotion ? 1 : 0);
        _alphaPiece._markPoint = sf::Vector2f(piecePoint_x, piecePoint_y);
        //进行坐标转换
        _alphaPiece._pixelPoint = _myChessBoardPoint->markToPixel(_alphaPiece._markPoint);
        std::cout << "捕捉到的棋盘标记坐标：" << _alphaPiece._markPoint.x << ", " << _alphaPiece._markPoint.y  << std::endl;
        std::cout << "对应的棋盘像素坐标：" << _alphaPiece._pixelPoint.x << ", " << _alphaPiece._pixelPoint.y  << std::endl;
        std::cout << "mouse at " << mouse.x << ", " << mouse.y << std::endl;
        //修改棋子的位置
        _alphaPiece._pieceCircle.setPosition(_alphaPiece._pixelPoint.x * propotion, _alphaPiece._pixelPoint.y * propotion);
        /* _alphaPiece._raduis *= propotion; */
        _alphaPiece._pieceCircle.setRadius(_alphaPiece._raduis);
        _alphaPiece._pieceCircle.setFillColor(BLACK_ALPHA);

    }

}

void GoRule::showBoardLineNumber()
{
    std::cout << _myChessBoardPoint->_lines.size() << std::endl;
    /* std::cout << "还就呐个难受~" << std::endl; */
}

void GoRule::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_alphaPiece._pieceCircle, states);
    /* std::cout << _alphaPiece._pieceCircle.getPosition().x << std::endl; */
}
