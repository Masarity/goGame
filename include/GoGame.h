#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ChessBoard.hpp"
#include "StatusPanel.hpp"
#include "GoRule.hpp"

//围棋游戏类
class GoGame
{
public:
    //删除拷贝构造
    GoGame(const GoGame&) = delete;
    //删除赋值
    GoGame& operator=(const GoGame&) = delete;
    //游戏构造函数
    GoGame();
    //游戏启动函数（刷新帧率）
    void run(int frame_per_second);

private:
    //处理各种事件
    void processEvents();
    //更新画面（时间差）
    void update(sf::Time deltaTime);
    //渲染画面
    void render();

private:
    //一些参数设置
    sf::ContextSettings _settings;
    //窗口设置
    sf::RenderWindow _window;
    //棋盘对象
    ChessBoard _myChessBoard;
    //状态面板对象
    StatusPanel _myStatusPanel;
    //规则对象
    GoRule _myGoRole = GoRule(&_myChessBoard, &_myStatusPanel);    
};
