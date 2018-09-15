cmake_minimum_required(VERSION 3.12)
project(Board_Games)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2TTF)
find_package(SDL2GFX)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS})
link_libraries(${SDL2GFX_LIBRARY} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY})

add_executable(Board_Games
        Application.cpp
        Application.h
        Board.cpp
        Board.h
        Helper.h
        LanguageResourceManager.cpp
        LanguageResourceManager.h
        NineMensMorrisBoard.cpp
        LanguageResourceManager.h
        Piece.cpp
        Piece.h
        Player.cpp
        Player.h
        Point.cpp
        Point.h
        SnakesAndLaddersBoard.cpp
        snakesandladdersboard.h
        main.cpp)
