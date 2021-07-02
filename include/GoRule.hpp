#pragma once
#include "ChessBoard.hpp"

class GoRule
{
public:
    GoRule(ChessBoard& chessBoard);
    ~GoRule() {}
    void showBoardLineNumber();

private:
    ChessBoard _mychessBoard;

};
