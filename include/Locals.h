#pragma once
#include <SFML/Graphics.hpp>

//窗口的设置
#ifdef INITIAL_WINDIW
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 618
#endif

//围棋棋盘的参数
#ifdef INITIAL_BOARD
#define BOARD_WIDTH  600
#define BOARD_HEIGHT 600
#define BOARD_COLOR     sf::Color(230, 145, 56)
#define BLACK           sf::Color(0, 0, 0)
#define BLACK_ALPHA     sf::Color(0, 0, 0, 30)
#define WHITE           sf::Color(255, 255, 255)
#define WHITE_ALPHA     sf::Color(255, 255, 255, 80)
#define RED             sf::Color(255, 0, 0)
#define BOARD_OFFSET 9
#define LINE_OFFSET  30
#define LEVEL_LINE_THICKNESS    sf::Vector2f(2.f, 540.9f)
#define VERTICAL_LINE_THICKNESS sf::Vector2f(540.9f, 2.f)
#define CIRCLE_OFFSET -4.1
#define CIRCLE_RADIUS 5
#define CIRCLE_POINTS_19 {3, 9, 15}
#define CIRCLE_POINTS_13 {3, 6,  9}
#define CIRCLE_POINTS_9  {2, 4,  6}
#endif
