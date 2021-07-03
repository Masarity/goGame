#include <iostream>
#define INITIAL_RULE 3
#include "Constants.h"
#include "GoRule.hpp"

GoRule::GoRule(ChessBoard* chessBoard)
{
    //拿到棋盘的指针，操作它（应用围棋的规则）
    _myChessBoardPoint = chessBoard;
}

void GoRule::isPieceUnderCursor(sf::Event::MouseMoveEvent& mouse)
{
    float propotion = (float)(NINETEEN - ONE) / (_myChessBoardPoint->_chooseLineNumber - ONE);
    float division = BASE_DIVISION_30 * propotion;
    //显示悬停棋子的范围
    if ((mouse.x > MIN_BOUND && mouse.x < MAX_BOUND)&&(mouse.y > MIN_BOUND && mouse.y < MAX_BOUND))
    {
        //起始点
        int basePoint_x = mouse.x / division, basePoint_y = mouse.y / division;
        //进位判断
        int carry_x = mouse.x % (int)division, carry_y = mouse.y % (int)division;
        //获得棋子的标记坐标
        int piecePoint_x = basePoint_x + (carry_x > MIN_BOUND / propotion ? ONE : ZERO);
        int piecePoint_y = basePoint_y + (carry_y > MIN_BOUND / propotion ? ONE : ZERO);
        _markPoint = sf::Vector2f(piecePoint_x, piecePoint_y);
        _alphaPiece._markPoint = _markPoint;
        //进行坐标转换
        _alphaPiece._pixelPoint = _myChessBoardPoint->markToPixel(_alphaPiece._markPoint, propotion);
        /* std::cout << "捕捉到的棋盘标记坐标：" << _alphaPiece._markPoint.x << ", " << _alphaPiece._markPoint.y  << std::endl; */
        /* std::cout << "对应的棋盘像素坐标：" << _alphaPiece._pixelPoint.x << ", " << _alphaPiece._pixelPoint.y  << std::endl; */
        /* std::cout << "mouse at " << mouse.x << ", " << mouse.y << std::endl; */
        //修改棋子的位置
        _alphaPiece._pieceCircle.setPosition(_alphaPiece._pixelPoint.x, _alphaPiece._pixelPoint.y);
        _alphaPiece._raduis = _alphaPiece._raduis * propotion;
        _alphaPiece._pieceCircle.setRadius(_alphaPiece._raduis);
        _alphaPiece._pieceCircle.setFillColor(_player ? BLACK_ALPHA : WHITE_ALPHA);
        
        //检查是否已经有棋子存在了
        forEach(_myChessBoardPoint->_blackPieces)
        {
            if ((*iter)._markPoint == _markPoint)
            {
                _showAlphaPiece = false;
                return;
            }
        }
        forEach(_myChessBoardPoint->_whitePieces)
        {
            if ((*iter)._markPoint == _markPoint)
            {
                _showAlphaPiece = false;
                return;
            }
        }
        _showAlphaPiece = true;
    }
    else
        _showAlphaPiece = false;
}

bool GoRule::addPieceToChessBoard()
{
    //如果显示悬停棋子
    if (_showAlphaPiece)
    {
        _pieceCount++;
        ChessPiece chessPiece = _alphaPiece;
        if (_player)
            chessPiece._pieceColor = PLAYER_BLACK;
        else 
            chessPiece._pieceColor = PLAYER_WHITE;
        //配置文字
        chessPiece._pieceCircle.setFillColor(chessPiece._pieceColor);
        chessPiece._pieceNumber = _pieceCount;
        chessPiece._text.setString(std::to_string(_pieceCount));
        chessPiece._text.setPosition(chessPiece._pixelPoint.x + chessPiece._raduis/4, chessPiece._pixelPoint.y);
        std::cout << "文字点x位置：" << chessPiece._text.getPosition().x << "\t文字内容： " << _pieceCount << std::endl;
        chessPiece._text.setCharacterSize(chessPiece._raduis);
        if (_player)
        {
            chessPiece._text.setFillColor(PLAYER_WHITE);
            _myChessBoardPoint->_blackPieces.push_back(chessPiece);
        }
        else
        {
            chessPiece._text.setFillColor(PLAYER_BLACK);
            _myChessBoardPoint->_whitePieces.push_back(chessPiece);
        }
        _player = !_player;
        return true;
    }
    return false;
}

void GoRule::showBoardLineNumber()
{
    std::cout << _myChessBoardPoint->_lines.size() << std::endl;
    /* std::cout << "还就呐个难受~" << std::endl; */
}

void GoRule::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (_showAlphaPiece)
    {
        /* std::cout << "show alpha piece~" << std::endl; */
        target.draw(_alphaPiece._pieceCircle, states);
    }
    /* else std::cout << "hide alpha piece~" << std::endl; */
    /* std::cout << _alphaPiece._pieceCircle.getPosition().x << std::endl; */
}
