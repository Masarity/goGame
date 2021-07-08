#include <iostream>
#define INITIAL_RULE 3
#include "Constants.h"
#include "GoRule.hpp"

GoRule::GoRule(ChessBoard* chessBoard, StatusPanel* statusPanel)
{
    /* bool isLoadSuccess = _myFont.loadFromFile("../res/fonts/FreeSans.ttf"); */   
    //拿到棋盘的指针，操作它（应用围棋的规则）
    _myChessBoardPoint = chessBoard;
    //拿到状态面板的指针，操作它
    _myStatusPanelPoint = statusPanel;

    //红叉基本配置
    /* if (isLoadSuccess) */
    /* { */
    /*     _myText.setFont(_myFont); */
    /*     _myText.setString("X"); */
    /*     _myText.setFillColor(COLOR_ALPHA); */
    /* } */
}

void GoRule::staticUpdateDynamic()
{
    for (int i=0; i<=_myChessBoardPoint->_chooseLineNumber; i++)
        for (int j=0; j<=_myChessBoardPoint->_chooseLineNumber; j++)
            _chessManualDynamic[i][j] = _chessManualStatic[i][j];
}

void GoRule::dynamicChessBoard(sf::Event::MouseMoveEvent& mouse)
{
    mouseEvent(mouse);
    updateStatusPanel();
    updateAlphaPieceQi();
    updatePieceQi();
    dividePieceGroups();
    updatePieceGroup();
    showPieceQi();
    findNoneQiPieces();
    showChessManual();
}

void GoRule::mouseEvent(sf::Event::MouseMoveEvent& mouse)
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
        _alphakey = (int)_markPoint.x + (int)_markPoint.y * 19;
        staticUpdateDynamic();

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
            _alphakey = 0;
            //显示黑棋的气
            return;
        }
        else if (checkPieceExistence(_myChessBoardPoint->_whitePieces, _markPoint))
        {
            _showAlphaPiece = false;
            _alphakey = 0;
            return;
        }
        //如果光标在棋盘空地处，那么不显示棋盘上棋子的气,并且重置棋盘上棋子气的状态
        _chessManualDynamic[(int)_markPoint.y][(int)_markPoint.x] = _player ? 1 : 2;       
        controlPieceVectorQi( &_myChessBoardPoint->_whitePieces, false, true);
        controlPieceVectorQi( &_myChessBoardPoint->_blackPieces, false, true);
        //显示悬停棋子
        _showAlphaPiece = true;
    }
    else
        _showAlphaPiece = false;
}

void GoRule::updateStatusPanel()
{
        //状态面板上显示标记坐标
        std::string showText = "At: ";
        showText += _myChessBoardPoint->_markPoint.substr(_markPoint.x, ONE);
        showText += ", ";
        showText += std::to_string(_myChessBoardPoint->_chooseLineNumber + 1 - (int)_markPoint.y);
        _myStatusPanelPoint->_showMarkPoint.setString(showText);

}

void GoRule::updateChessBoard()
{
    if (addPieceToChessBoard())
    {
        _capturedPiecesCount.push((int)_NoneQiPiece.size());
        forEach( _NoneQiPiece )
        {
            std::cout << "remove key:" << (*iter) << std::endl;
            removeNoneQiPiece((*iter));
        }
        _repentance.push( _capturedPiecesCount.top() ? true : false);
        //棋谱入队
        if ((int)_chessBoardStatus.size() == 2)
            _chessBoardStatus.pop();
        for (int i=1; i<=19; i++)
            for (int j=1; j<=19; j++)
                _cms.manual[i][j] = _chessManualStatic[i][j];
        _chessBoardStatus.push(_cms);
    }
}

void GoRule::controlPieceVectorQi(std::map<int, ChessPiece>* chessPiece, bool isVisible, bool reset)
{
    forEach( (*chessPiece) )
    {
        (*iter).second.isQiVisible(isVisible);
        (*iter).second.isNumberVisible(isVisible);
        //每次被悬停棋子修改过的棋子的气都要重置（可以做优化：这边是全部重置了（其实最多重置4个就够了））
        if (reset)  (*iter).second._pieceQi.setTrue();
    }
}

void GoRule::controlPieceVectorQi(std::map<int, ChessPiece>* chessPiece)
{
    forEach( (*chessPiece) )
        (*iter).second._pieceQi.setTrue();
}

void GoRule::showPieceQi()
{
        if (checkPieceExistence(_myChessBoardPoint->_blackPieces, _markPoint))
        {
            //显示黑棋的气
            showTheGoupQiUnderCursor( &_myChessBoardPoint->_blackPieces, _pieceGroupName[(int)_markPoint.y][(int)_markPoint.x]);
            //不显示白棋的气
            controlPieceVectorQi( &_myChessBoardPoint->_whitePieces, false);           
            return;
        }
        else if (checkPieceExistence(_myChessBoardPoint->_whitePieces, _markPoint))
        {
            showTheGoupQiUnderCursor( &_myChessBoardPoint->_whitePieces, _pieceGroupName[(int)_markPoint.y][(int)_markPoint.x]);
            controlPieceVectorQi( &_myChessBoardPoint->_blackPieces, false );
            return;
        }

}

void GoRule::showTheGoupQiUnderCursor(std::map<int, ChessPiece>* chessPiece, int groupName)
{
    forEach( (*chessPiece) )
    {
        //开启相同组号的棋子的状态可视化
        if ((*iter).second._pieceGroup == groupName)
        {
            /* std::cout << "key: " << (*iter).first << "groupName: " << groupName << std::endl; */
            (*iter).second.isQiVisible(true);
            (*iter).second.isNumberVisible(true);
        }
    }

}

bool GoRule::addPieceToChessBoard()
{
    //如果显示悬停棋子
    /* std::cout << "_isAlphaPieceExistence:\t" << _isAlphaPieceExistence << std::endl; */
    if (_showAlphaPiece && _isAlphaPieceExistence)
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
        int key = (int)_markPoint.x + (int)_markPoint.y * 19;
        if (_player)
        {
            chessPiece._text.setFillColor(PLAYER_WHITE);
            _myChessBoardPoint->_blackPieces.insert(std::pair<int, ChessPiece>(key, chessPiece));
            _chessManualStatic[(int)_markPoint.y][(int)_markPoint.x] = 1;
        }
        else
        {
            chessPiece._text.setFillColor(PLAYER_BLACK);
            _myChessBoardPoint->_whitePieces.insert(std::pair<int, ChessPiece>(key, chessPiece));
            _chessManualStatic[(int)_markPoint.y][(int)_markPoint.x] = 2;
        }
        //交换棋手
        _player = !_player;
       return true;
    }
    std::cout << "这里下子犯规呐~" << std::endl;
    return false;
}

void GoRule::showChessManual()
{
    std::string chessManual;
    for(int i=1; i<=_myChessBoardPoint->_chooseLineNumber ; i++)
    {
        for(int j=1; j<=_myChessBoardPoint->_chooseLineNumber; j++)
        {
            /* if (_pieceGroupName[i][j]) */
            /* { */
            /*     auto piece_iter = _myChessBoardPoint->findChessPiece(sf::Vector2f(j, i)); */
            /*     if (piece_iter != nullptr) */
            /*     { */
            /*         piece_iter->_pieceGroup = _pieceGroupName[i][j]; */
            /*     } */
            /*     else if (_alphaPiece._markPoint == sf::Vector2f(j, i)) */
            /*         _alphaPiece._pieceGroup = _pieceGroupName[i][j]; */
            /* } */
            chessManual += _pieceGroupName[i][j] == 0 ? "  .   " :  _pieceGroupName[i][j] < 10 ? 
                                                                   "  " + std::to_string(_pieceGroupName[i][j]) + "  ":
                                                                   _pieceGroupName[i][j] < 100 ?
                                                                   " " + std::to_string(_pieceGroupName[i][j]) + " ":
                                                                   "" + std::to_string(_pieceGroupName[i][j]) + "";

        }
            //这边是012的棋谱
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
    //如果已经标记过了就返回，并且计数减一
    if (_pieceGroupName[markPoint[0]][markPoint[1]])    return --groupName;
    //满足同色且相邻或重叠且未被标记的条件
    /* if ((_chessManualDynamic[markPoint[0]][markPoint[1]] == markName) && (groupName != _pieceGroupName[markPoint[0]][markPoint[1]])) */
    if ((_chessManualDynamic[markPoint[0]][markPoint[1]] == markName) && (0 == _pieceGroupName[markPoint[0]][markPoint[1]]))
    {
        //添加组
        _pieceGroupName[markPoint[0]][markPoint[1]] = groupName;
        int offset[][2] = PIECE_QI_OFFSET;
        int newMarkPoint[2];
        //向四个方向继续搜索
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
    //分组前初始化数组，应为组号是动态变化的
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
                int key = j + i * 19;
                if (key == _alphakey)
                {
                    _alphaPiece._pieceGroup = _pieceGroupName[i][j];
                }
                auto piece_pointer = _myChessBoardPoint->findChessPiece(sf::Vector2f(j, i));
                if (piece_pointer != nullptr)
                {
                    piece_pointer->_pieceGroup = _pieceGroupName[i][j];
                }

            }
        }
    }
}

int GoRule::isPieceAlive(ChessPiece* chessPiece)
{  
    if (chessPiece->_player)
    {
        //如果该棋子和悬停棋子属于同一组且悬停棋子有气
        if (chessPiece->_pieceGroup == _alphaPiece._pieceGroup && !_alphaPiece._pieceQi.isQiExistence())
        {
            return false;
        }
        forEach( _myChessBoardPoint->_blackPieces )
        {
            //若不是同一个棋子且属于同一组且该棋子的气存在
            if (((*iter).second._pieceNumber != chessPiece->_pieceNumber) && ((*iter).second._pieceGroup == chessPiece->_pieceGroup) && !(*iter).second._pieceQi.isQiExistence())
            {
                return false; 
            }
        }
    }
    else 
    {
        if (chessPiece->_pieceGroup == _alphaPiece._pieceGroup && !_alphaPiece._pieceQi.isQiExistence())
        {
            /* std::cout << "mark1\t" << "cpg:\t" << chessPiece->_pieceGroup << "\tapg:\t" << _alphaPiece._pieceGroup << std::endl; */
            return false;
        }
        forEach( _myChessBoardPoint->_whitePieces )
        {
            if (((*iter).second._pieceNumber != chessPiece->_pieceNumber) && ((*iter).second._pieceGroup == chessPiece->_pieceGroup) && !(*iter).second._pieceQi.isQiExistence())
            {
                /* std::cout << "mark2\n"; */
                return false;
            }
        }
    }
    //最后是返回棋子本身的气的状态
    //棋子无气则会返回它的key值，用来删掉它或者改变它的颜色
    return chessPiece->_pieceQi.isQiExistence();
}

/* void GoRule::removeNoneQiPiece(sf::Vector2f markPoint) */
/* { */
/*     int key = (int)markPoint.x + (int)markPoint.y * 19; */
/*     auto piece_iter_black = _myChessBoardPoint->_blackPieces.find(key); */
/*     auto piece_iter_white = _myChessBoardPoint->_whitePieces.find(key); */
/*     if (piece_iter_black != _myChessBoardPoint->_blackPieces.find(key)) */
/*     { */   
/*         _myChessBoardPoint->_blackPieces.erase(piece_iter_black); */
/*     } */
/*     else if (piece_iter_white != _myChessBoardPoint->_whitePieces.find(key)) */
/*     { */
/*         _myChessBoardPoint->_whitePieces.erase(piece_iter_white); */
/*     } */
/* } */

void GoRule::removeNoneQiPiece(int key)
{
    auto piece_iter_black = _myChessBoardPoint->_blackPieces.find(key);
    auto piece_iter_white = _myChessBoardPoint->_whitePieces.find(key);
    if (piece_iter_black != _myChessBoardPoint->_blackPieces.end())
    {   
        std::cout << "remove:~" << std::endl;
        _chessManualStatic[key/19][key%19] = 0;
        _capturedPieces.push((*piece_iter_black).second);
        _myChessBoardPoint->_blackPieces.erase(piece_iter_black);
    }
    else if (piece_iter_white != _myChessBoardPoint->_whitePieces.end())
    {
        _chessManualStatic[key/19][key%19] = 0;
        _capturedPieces.push((*piece_iter_white).second);
        _myChessBoardPoint->_whitePieces.erase(piece_iter_white);
    }
}

void GoRule::resetNoneQiPiece()
{
    if (!_alphaPiece._pieceQi.isQiExistence())
    {
        _isAlphaPieceExistence = true;
        _alphaPiece._text.setFillColor(COLOR_ALPHA);
    }

    forEach( _NoneQiPiece )
    {
        //调用棋盘提供的查找函数(类型比较长：用auto自动推导)
        auto piece_iter = _myChessBoardPoint->findChessPiece((*iter));
        if (piece_iter != nullptr)
            piece_iter->_pieceCircle.setFillColor(piece_iter->_player ? PLAYER_BLACK : PLAYER_WHITE);
    }
    //清空存无气棋子key的容器
    _NoneQiPiece.clear();
}

void GoRule::findNoneQiPieces()
{
    //查找前先重置
    resetNoneQiPiece();
    bool whiteFlag = false, blackFlag = false;

    forEach( _myChessBoardPoint->_blackPieces )
    {
        int key = isPieceAlive(&(*iter).second);
        if (key)
        {
            whiteFlag = true;
            _NoneQiPiece.push_back(key);
            _chessManualDynamic[key/19][key%19] = 0;
        }
    }
    forEach( _myChessBoardPoint->_whitePieces )
    {
        int key = isPieceAlive(&(*iter).second);
        if (key)
        {
            blackFlag = true;
            _NoneQiPiece.push_back(key);
            _chessManualDynamic[key/19][key%19] = 0;
        }
    }

    //改透明色
    forEach( _NoneQiPiece )
    {
        auto piece_iter = _myChessBoardPoint->findChessPiece((*iter));
        piece_iter->_pieceCircle.setFillColor(piece_iter->_player ? BLACK_ALPHA:WHITE_ALPHA);
    }

    if (_alphaPiece._pieceQi.isQiExistence())
    {
        /* std::cout << "wf:\t" << whiteFlag << "\tbf:\t" << blackFlag << "\tap:\t" << _alphaPiece._player << std::endl; */
        //如果悬停棋子处于无气状态的判断~
        if (((!_alphaPiece._player && whiteFlag) || (_alphaPiece._player && blackFlag)) && (((int)_chessBoardStatus.size() == 2) && (isRepeatedBoardPosition())))
            return;
        else if (isPieceAlive(&_alphaPiece))
        {
            _alphaPiece._text.setFillColor(RED);
            _alphaPiece._text.setString("X");
            _alphaPiece._text.setPosition(_alphaPiece._pixelPoint.x + _alphaPiece._raduis/3, _alphaPiece._pixelPoint.y - X_OFFSET_Y);
            _alphaPiece._text.setCharacterSize(X_SIZE);
            _isAlphaPieceExistence = false;
        }
        //全局同形判断
    }
}

bool GoRule::isRepeatedBoardPosition()
{
    /* std::cout << "cms:\n"; */
    /* for (int i=1; i<=19; i++) */
    /* { */
    /*     for (int j=1; j<=19; j++) */
    /*     { */
    /*         std::cout << _chessBoardStatus.front().manual[i][j] << " "; */
    /*     } */
    /*     std::cout << '\n'; */
    /* } */
 
    /* std::cout << "cmd:\n"; */
    /* for (int i=1; i<=19; i++) */
    /* { */
    /*     for (int j=1; j<=19; j++) */
    /*     { */
    /*         std::cout << _chessManualDynamic[i][j] << " "; */
    /*     } */
    /*     std::cout << '\n'; */
    /* } */
 

    for (int i=1; i<=19; i++)
        for (int j=1; j<=19; j++)
            if (_chessBoardStatus.front().manual[i][j] != _chessManualDynamic[i][j])
                return true;
    return false;
}

void GoRule::updatePieceQiByAlphaPiece(std::map<int, ChessPiece>* chessPiece)
{
    forEach( (*chessPiece) )
    {
        for (auto it = (*iter).second._pieceQi._pieceQi.begin(); it != (*iter).second._pieceQi._pieceQi.end(); it++)
        {
            if (sf::Vector2f((*iter).second._markPoint.x + (*iter).second._pieceQi._qiOffset[(*it).first][0],
                             (*iter).second._markPoint.y + (*iter).second._pieceQi._qiOffset[(*it).first][1]) == _alphaPiece._markPoint)
                (*it).second = false;
        }
    }
}

void GoRule::updateSingleColorPieceQi(std::map<int, ChessPiece>* chessPiece)
{
    forEach( (*chessPiece) )
    {
        for (auto it = (*iter).second._pieceQi._pieceQi.begin(); it != (*iter).second._pieceQi._pieceQi.end(); it++)
        {
            if (checkPieceExistence(_myChessBoardPoint->_blackPieces, sf::Vector2f((*iter).second._markPoint.x + (*iter).second._pieceQi._qiOffset[(*it).first][0],
                                                                                   (*iter).second._markPoint.y + (*iter).second._pieceQi._qiOffset[(*it).first][1])))
                (*it).second = false;
            if (checkPieceExistence(_myChessBoardPoint->_whitePieces, sf::Vector2f((*iter).second._markPoint.x + (*iter).second._pieceQi._qiOffset[(*it).first][0],
                                                                                   (*iter).second._markPoint.y + (*iter).second._pieceQi._qiOffset[(*it).first][1])))
                (*it).second = false;
        }
    }
}

void GoRule::updatePieceQi()
{
    _alphaPiece.isQiVisible(true);
    _alphaPiece.isNumberVisible(true);
    //先更新棋盘上棋子之间的气，然后在根据悬停棋子的位置改变棋盘上棋子的气
    controlPieceVectorQi( &_myChessBoardPoint->_blackPieces);   
    controlPieceVectorQi( &_myChessBoardPoint->_whitePieces);
    updateSingleColorPieceQi(&_myChessBoardPoint->_blackPieces);
    updateSingleColorPieceQi(&_myChessBoardPoint->_whitePieces);
    updatePieceQiByAlphaPiece(&_myChessBoardPoint->_whitePieces);
    updatePieceQiByAlphaPiece(&_myChessBoardPoint->_blackPieces);
}

bool GoRule::checkPieceExistence(std::map<int, ChessPiece>& pieces, sf::Vector2f markPoint)
{
    int key = (int)markPoint.x + (int)markPoint.y * 19;
    auto piece_iter = pieces.find(key);
    if (piece_iter != pieces.end())
        return true;
    return false;
}

void GoRule::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (_showAlphaPiece)
    {
        target.draw(_alphaPiece, states);
    }
}
