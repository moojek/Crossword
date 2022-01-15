cmake_minimum_required(VERSION 3.21)
project(Crossword C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra -lm")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lpanel -lncurses")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")

add_executable(Crossword main.c menus/editmenu.c menus/editmenu.h menus/editmenu/actions.c menus/editmenu/actions.h misc.c misc.h menus/editmenu/selector.c menus/editmenu/selector.h menus/mainmenu.c menus/mainmenu.h boards/board_creator.c boards/board_creator.h boards/boards_db.c boards/boards_db.h)
