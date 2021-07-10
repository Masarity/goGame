#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class StatusPanel: public sf::Drawable
{
    //友元类为了让围棋规则类直接操作状态面板
    friend class GoRule;
public:
    StatusPanel();

    void update(sf::Time deltaTime);

private:
    //状态面板底板
    sf::RectangleShape _panelBoard;
    //分割线
    sf::RectangleShape _divisionLine;
    //显示棋谱
    sf::Text _showChessManual;
    //下子点的标记坐标
    sf::Font _myFont;
    std::string _markPoint;
    sf::Text _showMarkPoint;
    //黑白棋子状态框
    sf::RectangleShape _blackFrame;
    sf::RectangleShape _whiteFrame;
    //计时器
    sf::Text _blackTimer;
    sf::Text _whiteTimer;
    sf::Clock _blackClock;
    int _blackDMS = 0;
    int _blackDS  = 0;
    sf::Vector3i _blackTimeCounter = sf::Vector3i(0, 0, 0);
    bool _blackTimerController = false;
    sf::Clock _whiteClock;
    int _whiteDMS = 0;
    int _whiteDS  = 0;
    sf::Vector3i _whiteTimeCounter = sf::Vector3i(0, 0, 0);
    bool _whiteTimerController = false;
    //花里胡哨
    /* sf::Vector2f _blackFramePosition; */
    /* sf::Vector2f _whiteFramePosition; */
    /* sf::Vector2f _blackFrameSize; */
    /* sf::Vector2f _whiteFrameSize; */
    /* /1* float wh_v = 85; *1/ */
    /* /1* float size_v = 150; *1/ */
    /* float wh_v = 255; */
    /* float size_v = 450; */
   
    /* int count = 20; */
    /* int cc = 0; */

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

