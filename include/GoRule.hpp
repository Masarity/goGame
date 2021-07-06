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
    //检查是否有棋子存在
    bool checkPieceExistence(std::map<int, ChessPiece>& pieces, sf::CircleShape circleShape);
    bool checkPieceExistence(std::map<int, ChessPiece>& pieces, sf::Vector2f markPoint);
    //检查光标下是否有棋子，若没有则显示悬停棋子
    void isPieceUnderCursor(sf::Event::MouseMoveEvent& mouse);
    //添加棋子到棋盘->把悬停棋子改个颜色，添加到棋盘对应的vector数组里,添加成功返回true
    bool addPieceToChessBoard();
    //更新悬停棋子的气
    void updateAlphaPieceQi();
    //通过悬停的棋子更新棋盘上棋子的气
    void updatePieceQiByAlphaPiece(std::map<int, ChessPiece>* chessPiece);
    //更新一种颜色棋子的气
    void updateSingleColorPieceQi(std::map<int, ChessPiece>* chessPiece);
    //更新棋盘棋子的气
    void updatePieceQi();
    //显示光标所在棋子对应组的气&数字
    void showTheGoupQiUnderCursor(std::map<int, ChessPiece>* chessPiece, int groupName);
    //控制是否显示传入棋子指针所含的气&数字
    void controlPieceVectorQi(std::map<int, ChessPiece>* chessPiece, bool isVisible, bool reset=false);
    //终端输出棋谱
    void showChessManual();
    void staticUpdateDynamic();
    //贪搜棋子分组
    int greedySearch(int groupName, int markName, int markPoint[]);
    void dividePieceGroups();
    void updatePieceGroup();
    //棋子不存在条件(如果是棋盘上的棋子，那么它们会变半透明；若是悬停棋子，那么会在棋子上出现一个红色的X)
    bool isPieceExistence(ChessPiece* chessPiece);
    //删除无气的棋子(通过标记坐标点来找棋子并删除，压到被吃棋子栈(并且计数)->为悔棋做准备)
    void removeNoneQiPiece(sf::Vector2f markPoint);

private:
    //棋盘指针
    ChessBoard* _myChessBoardPoint;
    //状态面板指针
    StatusPanel* _myStatusPanelPoint;
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
    //棋盘状态队列（保存3个）（出现问题了，悔棋出现问题，之后想一波）
    std::queue<int[21][21]> _chessBoardStatus;
    //棋子的分组元组
    int _pieceGroupName[21][21] = {{0}};
    std::map<int, std::vector<ChessPiece>> _pieceGroups;
    //被吃棋子个数栈
    std::stack<int> _capturedPiecesCount;
    //被吃棋子储存栈
    std::stack<ChessPiece> _capturedPieces;
    //悔棋 (map) -> (key,value) -> key=棋子计数 ；value: true -> 退回被吃棋子&前一手棋； false -> 退回前一手棋；
    std::map<int, bool> repentance;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
