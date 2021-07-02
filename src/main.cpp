#include <iostream>
#include <cstdlib>
#include "Game.h"

int main(int argc, char** argv)
{   
    //帧率默认是30，可以通过命令行传参改变（第二个参数）
    int fps = 30;
    if (argc > 1)
        fps = atoi(argv[1]);
    std::cout << "Game start!~" << std::endl;
    Game game;
    game.run(fps);
    std::cout << "Game fps: " << fps << std::endl << "Game shutdown!~" << std::endl;
    return 0;
}
