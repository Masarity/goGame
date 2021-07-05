#include <iostream>
#define INITIAL_RULE 3
#include "Constants.h"
#include "GoRule.hpp"

GoRule::GoRule(ChessBoard* chessBoard, StatusPanel* statusPanel)
{
    //拿到棋盘的指针，操作它（应用围棋的规则）
    _myChessBoardPoint = chessBoard;
    //拿到状态面板的指针，操作它
    _myStatusPanelPoint = statusPanel;
}

void GoRule::staticUpdateDynamic()
{
    for (int i=0; i<=_myChessBoardPoint->_chooseLineNumber; i++)
        for (int j=0; j<=_myChessBoardPoint->_chooseLineNumber; j++)
            _chessManualDynamic[i][j] = _chessManualStatic[i][j];
}

void GoRule::isPieceUnderCursor(sf::Event::MouseMoveEvent& mouse)
{
    float division = BASE_DIVISION_30 * _myChessBoardPoint->_propotion;
    //显示悬停棋子的范围
    if ((mouse.x > MIN_BOUND && mouse.x < MAX_BOUND)&&(mouse.y > MIN_BOUND && mouse.y < MAX_BOUND))
    {
        //起始点
        int basePoint_x = mouse.x / division, basePoint_y = mouse.y / division;
        //进位判断
        int carry_x = mouse.x % (int)division, carry_y = mouse.y % (int)division;
        //获得棋子的标记坐标
        int piecePoint_x = basePoint_x + (carry_x > MIN_BOUND / _myChessBoardPoint->_propotion ? ONE : ZERO);
        int piecePoint_y = basePoint_y + (carry_y > MIN_BOUND / _myChessBoardPoint->_propotion ? ONE : ZERO);
        _markPoint = sf::Vector2f(piecePoint_x, piecePoint_y);
        _alphaPiece._markPoint = _markPoint;
        staticUpdateDynamic();
        //状态面板上显示标记坐标
        std::string showText = "At: ";
        showText += _myChessBoardPoint->_markPoint.substr(_markPoint.x, ONE);
        showText += ", ";
        showText += std::to_string(_myChessBoardPoint->_chooseLineNumber + 1 - (int)_markPoint.y);
        _myStatusPanelPoint->_showMarkPoint.setString(showText);
        //进行坐标转换
        _alphaPiece._pixelPoint = _myChessBoardPoint->markToPixel(_alphaPiece._markPoint);
        //修改棋子的位置&颜色
        _alphaPiece._player = _player;
        _alphaPiece._pieceCircle.setPosition(_alphaPiece._pixelPoint.x, _alphaPiece._pixelPoint.y);
        _alphaPiece._pieceCircle.setRadius(_alphaPiece._raduis * _myChessBoardPoint->_propotion);
        _alphaPiece._pieceCircle.setFillColor(_player ? BLACK_ALPHA : WHITE_ALPHA);
        
        //检查是否已经有棋子存在了
        if (checkPieceExistence(_myChessBoardPoint->_blackPieces, _markPoint))
        {
            //不显示悬停棋子
            _showAlphaPiece = false;
            //显示黑棋的气
            controlPieceVectorQi( &_myChessBoardPoint->_blackPieces, true  );
            //不显示白棋的气
            controlPieceVectorQi( &_myChessBoardPoint->_whitePieces, false );           
            return;
        }
        else if (checkPieceExistence(_myChessBoardPoint->_whitePieces, _markPoint))
        {
            _showAlphaPiece = false;
            controlPieceVectorQi( &_myChessBoardPoint->_whitePieces, true  );
            controlPieceVectorQi( &_myChessBoardPoint->_blackPieces, false );
            return;
        }
        //如果光标在棋盘空地处，那么不显示棋盘上棋子的气,并且重置棋盘上棋子气的状态
        _chessManualDynamic[(int)_markPoint.y][(int)_markPoint.x] = _player ? 1 : 2;       
        controlPieceVectorQi( &_myChessBoardPoint->_blackPieces, false, true);
        controlPieceVectorQi( &_myChessBoardPoint->_whitePieces, false, true);
        //显示悬停棋子
        _showAlphaPiece = true;
    }
    else
        _showAlphaPiece = false;
}

void GoRule::controlPieceVectorQi(std::vector<ChessPiece>* chessPiece, bool isVisible, bool reset)
{
    forEach( (*chessPiece) )
    {
        (*iter).isQiVisible(isVisible);
        (*iter).isNumberVisible(isVisible);
        if (reset)  (*iter)._pieceQi.setTrue();
    }
}

bool GoRule::addPieceToChessBoard()
{
    //如果显示悬停棋子
    if (_showAlphaPiece)
    {
        //累加棋子数
        _pieceCount++;
        //从悬停棋子获取拷贝
        ChessPiece chessPiece = _alphaPiece;
        //选择棋子颜色
        if (_player)
            chessPiece._pieceColor = PLAYER_BLACK;
        else 
            chessPiece._pieceColor = PLAYER_WHITE;
        //配置文字
        chessPiece._pieceCircle.setFillColor(chessPiece._pieceColor);
        chessPiece._pieceNumber = _pieceCount;
        chessPiece._text.setString(std::to_string(_pieceCount));
        chessPiece._text.setPosition(chessPiece._pixelPoint.x + chessPiece._raduis/4, chessPiece._pixelPoint.y);
        chessPiece._text.setCharacterSize(chessPiece._raduis);
        /* chessPiece._pieceGroup = _pieceGroupName[(int)_markPoint.y][(int)_markPoint.x]; */
        if (_player)
        {
            chessPiece._text.setFillColor(PLAYER_WHITE);
            _myChessBoardPoint->_blackPieces.push_back(chessPiece);
            _chessManualStatic[(int)_markPoint.y][(int)_markPoint.x] = 1;
        }
        else
        {
            chessPiece._text.setFillColor(PLAYER_BLACK);
            _myChessBoardPoint->_whitePieces.push_back(chessPiece);
            _chessManualStatic[(int)_markPoint.y][(int)_markPoint.x] = 2;
        }
        //交换棋手
        _player = !_player;
        return true;
    }
    return false;
}

void GoRule::showChessManual()
{
    std::string chessManual;
    for(int i=1; i<=_myChessBoardPoint->_chooseLineNumber ; i++)
    {
        for(int j=1; j<=_myChessBoardPoint->_chooseLineNumber; j++)
            chessManual += std::to_string(_pieceGroupName[i][j]) + "  ";
            /* chessManual += std::to_string(_chessManualDynamic[i][j]) + "  "; */
        chessManual += "\n";
    }
    _myStatusPanelPoint->_showChessManual.setString(chessManual);
}


void GoRule::updateAlphaPieceQi()
{
    //初始化悬停棋子的气，并且拿到控制气状态的map元组
    std::map<int, bool>* pieceQi = _alphaPiece._pieceQi.initializeQi(_markPoint, _player, _myChessBoardPoint->_propotion);
    forEach( (*pieceQi) )
    {
        //获得每个气的状态
        if (checkPieceExistence(_myChessBoardPoint->_blackPieces, sf::Vector2f(_alphaPiece._markPoint.x + _alphaPiece._pieceQi._qiOffset[(*iter).first][0], 
                                                                               _alphaPiece._markPoint.y + _alphaPiece._pieceQi._qiOffset[(*iter).first][1])))
            (*iter).second = false; 
        if (checkPieceExistence(_myChessBoardPoint->_whitePieces, sf::Vector2f(_alphaPiece._markPoint.x + _alphaPiece._pieceQi._qiOffset[(*iter).first][0],
                                                                               _alphaPiece._markPoint.y + _alphaPiece._pieceQi._qiOffset[(*iter).first][1])))
            (*iter).second = false;
    }
}

int GoRule::greedySearch(int groupName, int markName, int markPoint[])
{
    if (_pieceGroupName[markPoint[0]][markPoint[1]])    return --groupName;
    if ((_chessManualDynamic[markPoint[0]][markPoint[1]] == markName) && (groupName != _pieceGroupName[markPoint[0]][markPoint[1]]))
    {
        _pieceGroupName[markPoint[0]][markPoint[1]] = groupName;
        int offset[][2] = PIECE_QI_OFFSET;
        int newMarkPoint[2];
        for (int i=0; i<4; i++)
        {
            newMarkPoint[0] = markPoint[0] + offset[i][0];newMarkPoint[1] = markPoint[1] + offset[i][1];
            greedySearch(groupName, markName, newMarkPoint);
        }
    }
    return groupName;
}

void GoRule::dividePieceGroups()
{
    for (int i=0; i<21; i++)
        for (int j=0; j<21; j++)
            _pieceGroupName[i][j] = 0;
    int markPoint[2], groupName=0;
    for (int i=0; i<21; i++)
        for (int j=0; j<21; j++)
        {
            markPoint[0] = i;markPoint[1] = j;
            if (_chessManualDynamic[i][j] != 0)
                groupName = greedySearch(++groupName, _chessManualDynamic[i][j], markPoint);
        }
}

void GoRule::updatePieceGroup()
{
    //小问题：如果棋子是有序的话，会更加节省资源~（需要重载ChessPiece类的<， 然后用map来存获得排序好的棋子（用棋子的标记坐标来排序））
    //先捞实现一下10^5小于一秒还是可以接受的
    for (int i=1; i<=_myChessBoardPoint->_chooseLineNumber; i++)
    {
        for (int j=1; j<=_myChessBoardPoint->_chooseLineNumber; j++)
        {
            if (_pieceGroupName[i][j] != 0)
            {

            }
        }
    }
}


void GoRule::updatePieceQiByAlphaPiece(std::vector<ChessPiece>* chessPiece)
{
    forEach( (*chessPiece) )
    {
        for (auto it = (*iter)._pieceQi._pieceQi.begin(); it != (*iter)._pieceQi._pieceQi.end(); it++)
        {
            if (sf::Vector2f((*iter)._markPoint.x + (*iter)._pieceQi._qiOffset[(*it).first][0],
                             (*iter)._markPoint.y + (*iter)._pieceQi._qiOffset[(*it).first][1]) == _alphaPiece._markPoint)
                (*it).second = false;
        }
    }
}


void GoRule::updateSingleColorPieceQi(std::vector<ChessPiece>* chessPiece)
{
    forEach( (*chessPiece) )
    {
        for (auto it = (*iter)._pieceQi._pieceQi.begin(); it != (*iter)._pieceQi._pieceQi.end(); it++)
        {
            if (checkPieceExistence(_myChessBoardPoint->_blackPieces, sf::Vector2f((*iter)._markPoint.x + (*iter)._pieceQi._qiOffset[(*it).first][0],
                                                                                   (*iter)._markPoint.y + (*iter)._pieceQi._qiOffset[(*it).first][1])))
                (*it).second = false;
            if (checkPieceExistence(_myChessBoardPoint->_whitePieces, sf::Vector2f((*iter)._markPoint.x + (*iter)._pieceQi._qiOffset[(*it).first][0],
                                                                                   (*iter)._markPoint.y + (*iter)._pieceQi._qiOffset[(*it).first][1])))
                (*it).second = false;

        }
    }
}


void GoRule::updatePieceQi()
{
    _alphaPiece.isQiVisible(true);
    //先更新棋盘上棋子之间的气，然后在根据悬停棋子的位置改变棋盘上棋子的气
    updateSingleColorPieceQi(&_myChessBoardPoint->_blackPieces);
    updateSingleColorPieceQi(&_myChessBoardPoint->_whitePieces);
    updatePieceQiByAlphaPiece(&_myChessBoardPoint->_whitePieces);
    updatePieceQiByAlphaPiece(&_myChessBoardPoint->_blackPieces);
}

bool GoRule::checkPieceExistence(std::vector<ChessPiece>& pieces, sf::Vector2f markPoint)
{
    forEach( pieces )
    {
        if ((*iter)._markPoint == markPoint)
            return true;
    }
    return false;
}

void GoRule::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (_showAlphaPiece)
    {
        target.draw(_alphaPiece, states);
    }
}
