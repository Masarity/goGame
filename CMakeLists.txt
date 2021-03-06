cmake_minimum_required(VERSION 3.2)

set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INCROOT})

project(goGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

set(FILES_HEADER
    ${INCROOT}/GoGame.h
    ${INCROOT}/ChessBoard.hpp
    ${INCROOT}/ChessPiece.hpp
    ${INCROOT}/GoRule.hpp
    ${INCROOT}/StatusPanel.hpp
    ${INCROOT}/Constants.h
    ${INCROOT}/PieceQi.hpp
    )

set(FILES_SRC 
    ${SRCROOT}/main.cpp
    ${SRCROOT}/GoGame.cpp
    ${SRCROOT}/ChessBoard.cpp
    ${SRCROOT}/ChessPiece.cpp
    ${SRCROOT}/GoRule.cpp
    ${SRCROOT}/StatusPanel.cpp
    ${SRCROOT}/PieceQi.cpp
    )

add_executable(startGame ${FILES_HEADER} ${FILES_SRC})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(startGame ${SFML_LIBRARIES})
endif()

find_package(Eigen3 3.3.9 REQUIRED)
if (Eigen3_FOUND)
    include_directories(${Eigen3_DIRS})
endif()
