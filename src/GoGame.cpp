#include <iostream>
#include "GoGame.h"
#define INITIAL_MYWINDOW 0
#include "Constants.h"

GoGame::GoGame()
{
    //抗锯齿化
    _settings.antialiasingLevel = 0;
    //模板缓冲
    _settings.stencilBits = 8;
    //深度缓冲
    _settings.depthBits = 24;
    //最高版本
    _settings.majorVersion = 2;
    //最低版本
    _settings.minorVersion = 1;
    //设置窗口的参数
    _window.create(sf::VideoMode(MYWINDOW_WIDTH, MYWINDOW_HEIGHT),
                  "goGame", sf::Style::Close, _settings);
    _window.setPosition(sf::Vector2i(460, 231));

}

void GoGame::run(int frame_per_second)
{
    //游戏时钟
    sf::Clock myClock;
    //帧率刷新的时间差
    sf::Time deltaTime = sf::Time::Zero;
    //一帧的秒数
    sf::Time timePerFrame = sf::seconds(1.f / (float)frame_per_second);
    //游戏主循环
    while (_window.isOpen())
    {
        //处理事件
        processEvents();
        //是否刷新一帧画面（围棋似乎只有在状态面板里会用到）
        bool repaint = false;
        //一次游戏的耗时累加进时间差
        deltaTime += myClock.restart();
        while (deltaTime > timePerFrame)
        {
            //按帧率更新游戏内容
            deltaTime -= timePerFrame;
            repaint = true;
            update(timePerFrame);
        }
        //刷新画面
        if (repaint)
            render();
    }
}

void GoGame::processEvents()
{
    //创建事件结构体
    sf::Event event;
    //事件处理循环
    while (_window.pollEvent(event))
    {
        //关闭窗口事件
        if ((event.type == sf::Event::Closed) ||
            ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
        {
            _window.close();
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            /* std::cout << "mouse wa~ moved~~ to: " << event.mouseMove.x << ", " << event.mouseMove.y << std::endl; */
            //棋子跟随
            _myGoRole.isPieceUnderCursor(event.mouseMove);
            _myGoRole.updateAlphaPieceQi();
            _myGoRole.updatePieceQi();
            _myGoRole.isPieceUnderCursor(event.mouseMove);
            _myGoRole.showChessManual();
            _myGoRole.dividePieceGroups();
        }
        //左键点击下子
        if (event.type == sf::Event::MouseButtonPressed && 
            event.mouseButton.button == sf::Mouse::Left)
        {
            bool putPieceSuccess = false;
            putPieceSuccess = _myGoRole.addPieceToChessBoard();
            _myGoRole.showChessManual();
            /* _myGoRole.updatePieceQi(); */
            /* if (!putPieceSuccess) */
            /*     std::cout << "下子失败~" << "\t在像素点: " << event.mouseButton.x << ", " << event.mouseButton.y << "请在棋盘内下子" << std::endl; */
        }
    }
}

void GoGame::update(sf::Time deltaTime)
{
    _myChessBoard.update(deltaTime);
}

void GoGame::render()
{
    //着色器（目前没啥用）
    sf::Shader shader;
    _window.clear();
    if (sf::Shader::isAvailable())
    {
        /* std::cout << "shader is available" << std::endl; */
        //渲染三个主要框架：棋盘、状态面板、规则
        _window.draw(_myChessBoard);
        _window.draw(_myStatusPanel);
        _window.draw(_myGoRole);
    }
    else
    {
        std::cout << "shader is not availiable" << std::endl;
    }
    _window.display();
}
