#include <iostream>
#include <cstdlib>
#include "GoGame.h"

int main(int argc, char** argv)
{   
    //帧率默认是30，可以通过命令行传参改变（第二个参数）
    int fps = 30;
    if (argc > 1)
        fps = atoi(argv[1]);
    //创建围棋游戏对象
    GoGame goGame;
    //游戏开始，进入游戏循环循环
    std::cout << "Game start!~" << std::endl;
    goGame.run(fps);
    std::cout << "Game fps: " << fps << std::endl << "Game shutdown!~" << std::endl;
    return 0;
}

