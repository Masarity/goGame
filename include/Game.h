#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game {
       public:
           //删除拷贝构造
           Game(const Game&) = delete;
           //删除赋值
           Game& operator=(const Game&) = delete;
           //游戏构造函数
           Game();
           //游戏启动函数（刷新帧率）
           void run(int frame_per_second);
       private:
           //处理各种事件
           void processEvents();
           //更新画面（时间差）
           void update(sf::Time deltaTime);
           //渲染画面
           void render();
           //一些参数设置
           sf::ContextSettings settings;
           //窗口设置
           sf::RenderWindow window;
};
