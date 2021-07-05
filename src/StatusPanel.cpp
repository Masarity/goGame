#include <iostream>
#include "StatusPanel.hpp"
#define INITIAL_PANEL 6
#include "Constants.h"


StatusPanel::StatusPanel()
{
    bool isLoadSuccess = _myFont.loadFromFile("../res/fonts/FreeSans.ttf");
    //面板底板参数
    _panelBoard.setPosition(PANEL_POSITION_X + LINE_OFFSET, PANEL_POSITION_Y + LINE_OFFSET);
    _panelBoard.setFillColor(PANEL_COLOR);
    _panelBoard.setSize(sf::Vector2f(MYWINDOW_WIDTH-PANEL_POSITION_X - LINE_OFFSET * 2, PANEL_POSITION_X - LINE_OFFSET * 2));
    _panelBoard.setOutlineThickness(LINE_OFFSET);
    _panelBoard.setOutlineColor(PANEL_ALPHA);

    //分割线的配置
    _divisionLine.setSize(DIVISION_LINE_SIZE);
    _divisionLine.setPosition(DIVISION_LINE_POSITION.x, DIVISION_LINE_POSITION.y);
    _divisionLine.setFillColor(DIVISION_LINE_COLOR);

    //棋谱文字的配置
    _showChessManual.setFont(_myFont);
    _showChessManual.setString("");
    _showChessManual.setFillColor(sf::Color(255, 255, 255));
    _showChessManual.setPosition(CHESS_MANUAL_POSITION.x, CHESS_MANUAL_POSITION.y);
    _showChessManual.setCharacterSize(CHESS_MANUAL_FONT_SIZE);
    _showChessManual.setOutlineThickness(1);
    _showChessManual.setOutlineColor(sf::Color(0, 0, 0, 80));


    //坐标显示的配置
    if (isLoadSuccess)
    {
        std::cout << "Font loading successflly~" << std::endl;
        _showMarkPoint.setFont(_myFont);
        _showMarkPoint.setString("");
        _showMarkPoint.setFillColor(TEXT_COLOR);
        _showMarkPoint.setPosition(DIVISION_LINE_POSITION.x + LINE_OFFSET, DIVISION_LINE_POSITION.y + LINE_OFFSET);
        _showMarkPoint.setCharacterSize(LINE_OFFSET * 1.5);
    }
}


void StatusPanel::update(sf::Time deltaTime)
{
}


void StatusPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //绘制状态面板&棋盘标记点
    target.draw(_panelBoard, states);
    target.draw(_showMarkPoint, states);
    target.draw(_divisionLine, states);
    target.draw(_showChessManual, states);
}
