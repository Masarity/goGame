#include <iostream>
#include "GoRule.hpp"

GoRule::GoRule(ChessBoard& chessBoard)
{
    _mychessBoard = chessBoard;
}

void GoRule::showBoardLineNumber()
{
    std::cout << _mychessBoard._lines.size() << std::endl;
    /* std::cout << "还就呐个难受~" << std::endl; */
}
