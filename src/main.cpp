#include <iostream>
#include <cstdlib>
#include "Game.h"

int main(int argc, char** argv)
{   
    int fps = 60;
    if (argc > 1)
        fps = atoi(argv[1]);
    std::cout << "Game start!~" << std::endl;
    Game game;
    game.run(fps);
    std::cout << "Game fps: " << fps << std::endl << "Game shutdown!~" << std::endl;
    return 0;
}

