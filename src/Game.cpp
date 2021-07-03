#include <iostream>
#include "Game.h"
#define INITIAL_MYWINDOW 0
#include "Locals.h"

Game::Game()
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
    /* _window.setPosition(sf::Vector2i(460, 231)); */
    _window.create(sf::VideoMode(MYWINDOW_WIDTH, MYWINDOW_HEIGHT),
                  "goGame", sf::Style::Close, _settings);
    _window.setPosition(sf::Vector2i(460, 231));

}

void Game::run(int frame_per_second)
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
        processEvents();
        bool repaint = false;
        deltaTime += myClock.restart();
        while (deltaTime > timePerFrame)
        {
            deltaTime -= timePerFrame;
            repaint = true;
            update(timePerFrame);
        }
        if (repaint)
            render();
    }
}

void Game::processEvents()
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
            _myGoRole.showBoardLineNumber();
            _window.close();
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            /* std::cout << "mouse wa~ moved~~ to: " << event.mouseMove.x << ", " << event.mouseMove.y << std::endl; */
            _myGoRole.showAlphaPiece(event.mouseMove);
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    _myChessBoard.update(deltaTime);
}

void Game::render()
{
    sf::Shader shader;
    _window.clear();
    if (sf::Shader::isAvailable())
    {
        /* std::cout << "shader is available" << std::endl; */
        _window.draw(_myChessBoard);
        _window.draw(_myGoRole);
    }
    else
    {
        std::cout << "shader is not availiable" << std::endl;
    }
    _window.display();
}
