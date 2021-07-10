#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>
#include <map>
#include <queue>
#include "ChessBoard.hpp"
#include "StatusPanel.hpp"

class GoRule: public sf::Drawable
{
public:
    //围棋规则类构造函数
    GoRule(ChessBoard* chessBoard, StatusPanel* statusPanel);
    //检查是否有棋子存在(函数重载：通过标记坐标点或棋子图形对象都可以检查)
    bool checkPieceExistence(std::map<int, ChessPiece>& pieces, sf::CircleShape circleShape);
    bool checkPieceExistence(std::map<int, ChessPiece>& pieces, sf::Vector2f markPoint);
    //检查光标下是否有棋子，若没有则显示悬停棋子
    void mouseEvent(sf::Event::MouseMoveEvent& mouse);
    //随着光标动态更新各种状态参数
    void dynamicChessBoard(sf::Event::MouseMoveEvent& mouse);
    //更新状态面板
    void updateStatusPanel();
    //鼠标左击后刷新棋盘
    void updateChessBoard();
    //添加棋子到棋盘->把悬停棋子改个颜色，添加到棋盘对应的vector数组里,添加成功返回true
    int  addPieceToChessBoard();
    //更新悬停棋子的气
    void updateAlphaPieceQi();
    //通过悬停的棋子更新棋盘上棋子的气
    void updatePieceQiByAlphaPiece(std::map<int, ChessPiece>* chessPiece);
    //更新一种颜色棋子的气
    void updateSingleColorPieceQi(std::map<int, ChessPiece>* chessPiece);
    //更新棋盘棋子的气
    void updatePieceQi();
    //显示光标所在棋子对应组的气&数字
    void isQiAndNumberVisible(bool control);
    void showPieceQi();
    void showTheGoupQiUnderCursor(std::map<int, ChessPiece>* chessPiece, int groupName);
    //控制是否显示传入棋子指针所含的气&数字
    void controlPieceVectorQi(std::map<int, ChessPiece>* chessPiece, bool isVisible, bool reset=false);
    void controlPieceVectorQi(std::map<int, ChessPiece>* chessPiece);

    /* 棋谱这一块可以优化，实际上一个数组再外带一个变量就行，这样悔棋也好做了，做悔棋模块的时候，再改~ */
    //优化棋谱（首先定义）

    //终端输出棋谱(棋盘上棋子的分组状态可视化：调试小有用)
    void showChessManual();
    //每次一次刷新后都要用静态的棋谱去重置动态棋谱
    void staticUpdateDynamic();
    //贪搜棋子分组
    int greedySearch(int groupName, int markName, int markPoint[]);
    //分组棋子，调用贪搜
    void dividePieceGroups();
    //将棋子的分组情况反映到棋子的属性上去(其实可以和终端输出棋谱一起写，但是总归要分出来的~)
    void updatePieceGroup();
    //棋子不存在条件(如果是棋盘上的棋子，那么它们会变半透明；若是悬停棋子，那么会在棋子上出现一个红色的X)
    int isPieceAlive(ChessPiece* chessPiece);
    //删除无气的棋子(通过标记坐标点来找棋子并删除，压到被吃棋子栈(并且计数)->为悔棋做准备)
    void removeNoneQiPiece(int key);
    //重置无气棋子的状态，把透明状态改回来，红色的X不显示
    void resetNoneQiPiece();
    //查找没有气的棋子
    void findNoneQiPieces();
    //是否全局同形
    bool isRepeatedBoardPosition();
    //悔棋
    void repentance();
    //退回被吃棋子
    void returnCapturedPieces(std::pair<int, ChessPiece> chessPiece);
    //删除棋子，不进栈
    void deletePiece(int key);
    //修改队列棋谱
    void modifyChessManualQueue(int key, int kind);

private:
    //棋盘指针
    ChessBoard* _myChessBoardPoint;
    //状态面板指针
    StatusPanel* _myStatusPanelPoint;
    //是否显示棋子的气和数字
    bool _showVisualizaions = false;
    //保存光标的标记坐标
    sf::Vector2f _markPoint;
    //是否显示悬停棋子bool量
    bool _showAlphaPiece = false;
    bool _isAlphaPieceExistence = true;
    //悬停的棋子对象
    ChessPiece _alphaPiece;
    int _alphakey;
    //棋子计数
    int _pieceCount = 0;
    //棋手颜色(true -> black; false -> white)
    bool _player = true;
    //棋谱
    int  _chessManualStatic[21][21] = {{0}};
    int  _chessManualDynamic[21][21] = {{0}};
    //记录下子的key值
    /* std::vector<int> _chessManualStorage; */
    //棋盘状态队列（保存2个）（出现问题了，悔棋会出现问题，之后想一波）
    struct _chessManualStatus
    {
        int manual[21][21] = {{0}};
    }_cms;
    std::queue<_chessManualStatus> _chessBoardStatus;
    //棋子的分组map
    int _pieceGroupName[21][21] = {{0}};
    std::map<int, std::vector<ChessPiece>> _pieceGroups;
    //无气棋子的vector
    std::vector<int> _NoneQiPiece;
    //被吃棋子个数栈
    std::stack<int> _capturedPiecesCount;
    //被吃棋子储存栈
    std::stack<std::pair<int,ChessPiece>> _capturedPieces;
    //悔棋 (stack<int, bool>) -> 没有没吃棋子false，有被吃棋子数true, int 记录每一手下的棋子的编号
    std::stack<std::pair<int, bool>> _repentance;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
