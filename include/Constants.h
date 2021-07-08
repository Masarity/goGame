#pragma once
#include <SFML/Graphics.hpp>

//窗口的设置
#ifdef INITIAL_MYWINDOW
#define MYWINDOW_WIDTH      1000
#define MYWINDOW_HEIGHT     618
#endif

//围棋棋盘的参数
#ifdef INITIAL_BOARD
#define BOARD_WIDTH  600
#define BOARD_HEIGHT 600
#define BOARD_COLOR     sf::Color(230, 145, 56)
#define BLACK           sf::Color(0, 0, 0)
#define WHITE           sf::Color(255, 255, 255)
#define WHITE_ALPHA     sf::Color(255, 255, 255, 80)
#define BOARD_OFFSET 9
#define LINE_OFFSET  30
#define LEVEL_LINE_THICKNESS    sf::Vector2f(2.f, 540.9f)
#define VERTICAL_LINE_THICKNESS sf::Vector2f(540.9f, 2.f)
#define CIRCLE_OFFSET   -4.1
#define CIRCLE_RADIUS   5
#define CIRCLE_POINTS_19 {3, 9, 15}
#define CIRCLE_POINTS_13 {3, 6,  9}
#define CIRCLE_POINTS_9  {2, 4,  6}
#define MARK_POINTS_19   "ZABCDEFGHJKLMNOPQRST"
#define MARK_POINTS_13   "ZABCDEFGHJKLMN"
#define MARK_POINTS_9    "ZABCDEFGHJ"
//遍历宏
#define forEach(container)    for (auto iter=container.begin(); iter != container.end(); iter++)
#endif

//棋子参数
#ifdef PIECE_ARGS
#define PIECE_RADIUS 15
#define BASE_19      19
#endif

//规则参数
#ifdef INITIAL_RULE
#define BASE_DIVISION_30    30
#define NINETEEN            19
#define MIN_BOUND           25
#define MAX_BOUND           595
#define ONE                 1
#define ZERO                0
#define PLAYER_WHITE    sf::Color(255, 255, 255)
#define WHITE_ALPHA     sf::Color(255, 255, 255, 30)
#define PLAYER_BLACK    sf::Color(0, 0, 0)
#define BLACK_ALPHA     sf::Color(0, 0, 0, 30)
#define COLOR_ALPHA     sf::Color(0, 0, 0, 0)
#define RED             sf::Color(255, 0, 0)
#define X_SIZE          30
#define X_OFFSET_Y      4
#define PIECE_QI_OFFSET {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}
//遍历宏
#define forEach(container)    for (auto iter=container.begin(); iter != container.end(); iter++)
#endif

//状态面板参数
#ifdef INITIAL_PANEL
#define MYWINDOW_WIDTH      1000
#define PANEL_POSITION_X 618
#define PANEL_POSITION_Y 0
#define LINE_OFFSET 9
#define TEXT_COLOR sf::Color(159, 18, 139)
/* #define PANEL_COLOR sf::Color(74, 159, 140) */
#define PANEL_COLOR sf::Color(97, 176, 96)
/* #define PANEL_ALPHA     sf::Color(153, 51, 205, 80) */
#define PANEL_ALPHA            sf::Color(97, 176, 96, 80)
#define DIVISION_LINE_POSITION sf::Vector2f(627,   382)
#define DIVISION_LINE_SIZE     sf::Vector2f(364.f, 2.f)
#define DIVISION_LINE_COLOR    sf::Color(1, 2, 3, 80)
/* #define CHESS_MANUAL_POSITION  sf::Vector2f(700,   382) */
#define CHESS_MANUAL_POSITION  sf::Vector2f(640,   382)
#define CHESS_MANUAL_SIZE      sf::Vector2f(218,   218)
#define CHESS_MANUAL_FONT_SIZE 11
#endif

//气的参数
#ifdef INITIAL_QI
/* #define PIECE_QI_OFFSET {{0, -1}, {0, 1}, {-1, 0}, {1, 0}} */
#define WHITE_QI_COLOR sf::Color(255, 255, 255, 60)
#define BLACK_QI_COLOR sf::Color(0,   0,   0,   60)
#define QI_RADIUS      7
#define CIRCLE_OFFSET -6
#define BOARD_OFFSET   9
#define LINE_OFFSET    30
#define forEach(container)    for (auto iter=container.begin(); iter != container.end(); iter++)
#endif
