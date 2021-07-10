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



    //黑白棋状态的显示
    _blackFrame.setPosition(BLACK_FRAME_POSITION);
    _blackFrame.setFillColor(BLACK_FRAME_COLOR);
    _blackFrame.setSize(BLACK_FRAME_SIZE);
    _blackFrame.setOutlineThickness(LINE_OFFSET);
    _blackFrame.setOutlineColor(BLACK_FRAME_OL_COLOR);
    _whiteFrame.setPosition(WHITE_FRAME_POSITION);
    _whiteFrame.setFillColor(WHITE_FRAME_COLOR);
    _whiteFrame.setSize(BLACK_FRAME_SIZE);
    _whiteFrame.setOutlineThickness(LINE_OFFSET);
    _whiteFrame.setOutlineColor(WHITE_FRAME_OL_COLOR);

    /* _blackFramePosition = BLACK_FRAME_POSITION; */
    /* _whiteFramePosition = WHITE_FRAME_POSITION; */
    /* _blackFrameSize = BLACK_FRAME_SIZE; */
    /* _whiteFrameSize = WHITE_FRAME_SZIE; */
    if (isLoadSuccess)
    {
        //计时器的配置
        _blackTimer.setFont(_myFont);
        _blackTimer.setString("Time ->00:00:00");
        _blackTimer.setFillColor(BLACK_TIMER_COLOR);
        _blackTimer.setPosition(BLACK_FRAME_POSITION + BLACK_TIMER_OFFSET);
        _blackTimer.setCharacterSize(LINE_OFFSET * 1.5);
        _blackClock.restart();
        _whiteTimer.setFont(_myFont);
        _whiteTimer.setString("Time ->00:00:00");
        _whiteTimer.setFillColor(WHITE_TIMER_COLOR);
        _whiteTimer.setPosition(WHITE_FRAME_POSITION + WHITE_TIMER_OFFSET);
        _whiteTimer.setCharacterSize(LINE_OFFSET * 1.5);
        _whiteClock.restart();

        //坐标显示的配置
        std::cout << "Font loading successflly~" << std::endl;
        _blackMarkPoint.setFont(_myFont);
        _blackMarkPoint.setString("Pos\t->");
        _blackMarkPoint.setFillColor(BLACK_TIMER_COLOR);
        _blackMarkPoint.setPosition(BLACK_FRAME_POSITION + POS_OFFSET);
        _blackMarkPoint.setCharacterSize(LINE_OFFSET * 1.5);
        _whiteMarkPoint.setFont(_myFont);
        _whiteMarkPoint.setString("Pos\t->");
        _whiteMarkPoint.setFillColor(WHITE_TIMER_COLOR);
        _whiteMarkPoint.setPosition(WHITE_FRAME_POSITION + POS_OFFSET);
        _whiteMarkPoint.setCharacterSize(LINE_OFFSET * 1.5);
    }
}


void StatusPanel::update(sf::Time deltaTime)
{
    if (_blackTimerController)
    {
        std::string blackClock = "Time ->";
        /* int dms = _blackClock.getElapsedTime().asMilliseconds(); */
        _blackDMS += _blackClock.restart().asMilliseconds();
        /* int ds = dms / 1000; */
        _blackDS = _blackDMS / 1000;
        /* _blackTimeCounter = sf::Vector3i(ds/3600, (ds/60)%60, ds%60); */
        _blackTimeCounter = sf::Vector3i(_blackDS/3600, (_blackDS/60)%60, _blackDS%60);
        if (_blackTimeCounter.z >= 60)
        {
            _blackTimeCounter.y += _blackTimeCounter.x / 60;
            _blackTimeCounter.z %= 60;
        }
        if (_blackTimeCounter.y >= 60)
        {
            _blackTimeCounter.x += _blackTimeCounter.y / 60;
            _blackTimeCounter.y %= 60;
        }
        blackClock += (_blackTimeCounter.x ? "0" + std::to_string(_blackTimeCounter.x) + ":" : "00:");
        blackClock += (_blackTimeCounter.y == 0 ? "00:" : _blackTimeCounter.y < 10 ? "0" + std::to_string(_blackTimeCounter.y) + ":"
                       : std::to_string(_blackTimeCounter.y) + ":");
        blackClock += (_blackTimeCounter.z == 0 ? "00" : _blackTimeCounter.z < 10 ? "0" + std::to_string(_blackTimeCounter.z)
                       : std::to_string(_blackTimeCounter.z));
        _blackTimer.setString(blackClock);
    }
    if (_whiteTimerController)
    {
        std::string whiteClock = "Time ->";
        /* int dms = _whiteClock.getElapsedTime().asMilliseconds(); */
        _whiteDMS += _whiteClock.restart().asMilliseconds();
        /* int ds = dms / 1000; */
        _whiteDS = _whiteDMS / 1000;
        /* _whiteTimeCounter = sf::Vector3i(ds/3600, (ds/60)%60, ds%60); */
        _whiteTimeCounter = sf::Vector3i(_whiteDS/3600, (_whiteDS/60)%60, _whiteDS%60);
        if (_whiteTimeCounter.z >= 60)
        {
            _whiteTimeCounter.y += _whiteTimeCounter.x / 60;
            _whiteTimeCounter.z %= 60;
        }
        if (_whiteTimeCounter.y >= 60)
        {
            _whiteTimeCounter.x += _whiteTimeCounter.y / 60;
            _whiteTimeCounter.y %= 60;
        }
        whiteClock += (_whiteTimeCounter.x ? "0" + std::to_string(_whiteTimeCounter.x) + ":" : "00:");
        whiteClock += (_whiteTimeCounter.y == 0 ? "00:" : _whiteTimeCounter.y < 10 ? "0" + std::to_string(_whiteTimeCounter.y) + ":"
                       : std::to_string(_whiteTimeCounter.y) + ":");
        whiteClock += (_whiteTimeCounter.z == 0 ? "00" : _whiteTimeCounter.z < 10 ? "0" + std::to_string(_whiteTimeCounter.z)
                       : std::to_string(_whiteTimeCounter.z));
        _whiteTimer.setString(whiteClock);
    }
}


void StatusPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //绘制状态面板&棋盘标记点
    target.draw(_panelBoard, states);
    target.draw(_divisionLine, states);
    target.draw(_showChessManual, states);
    target.draw(_blackFrame, states);
    target.draw(_whiteFrame, states);
    target.draw(_blackTimer, states);
    target.draw(_whiteTimer, states);
    target.draw(_blackMarkPoint, states);
    target.draw(_whiteMarkPoint, states);
}

//花里胡哨
/* if (count >= 0) */
/*     { */
/*         count--; */
/*         float blackFrameVelocity_pos = wh_v; */
/*         float blackFrameVelocity_size = size_v; */
/*         if (count == 10) */
/*         { */
/*             wh_v = -wh_v; */
/*             size_v = -size_v; */
/*             count = 20; */
/*         } */
/*         if (_blackFrameSize.y > 0 && _blackFrameSize.y < 30) */
/*             _blackFrame.setFillColor(_blackFrame.getFillColor() == BLACK_FRAME_COLOR ? WHITE_FRAME_COLOR : BLACK_FRAME_COLOR); */
/*         if (_blackFramePosition.y < 117) */
/*         { */
/*             blackFrameVelocity_size = -size_v; */
/*         } */
/*         _blackFramePosition.y += deltaTime.asSeconds() * blackFrameVelocity_pos; */
/*         _blackFrameSize.y += deltaTime.asSeconds() * blackFrameVelocity_size; */

/*         _blackFrame.setPosition(_blackFramePosition); */
/*         _blackFrame.setSize(_blackFrameSize); */
/*         /1* if (count == 0) *1/ */
/*         /1* { *1/ */
/*         /1*     wh_v = 255; *1/ */
/*         /1*     size_v = 450; *1/ */
/*         /1* } *1/ */
/*     } */
