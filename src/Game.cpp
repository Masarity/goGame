#include <iostream>
#include "Game.h"
#define INITIAL_WINDIW 0
#include "Locals.h"

Game::Game()
{
    //抗锯齿化
    settings.antialiasingLevel = 0;
    //模板缓冲
    settings.stencilBits = 8;
    //深度缓冲
    settings.depthBits = 24;
    //最高版本
    settings.majorVersion = 2;
    //最低版本
    settings.minorVersion = 1;
    //设置窗口的参数
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                  "goGame", sf::Style::Close, settings);
    window.setPosition(sf::Vector2i(460, 231));

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
    while (window.isOpen())
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
    while (window.pollEvent(event))
    {
        //关闭窗口事件
        if ((event.type == sf::Event::Closed) ||
            ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
        {
            window.close();
        }
    }
}

void Game::update(sf::Time deltaTime)
{
}

void Game::render()
{
    sf::Shader shader;
    window.clear();
    if (sf::Shader::isAvailable())
    {
        /* std::cout << "shader is available" << std::endl; */
    }
    else
    {
        std::cout << "shader is not availiable" << std::endl;
    }
    window.display();
}
