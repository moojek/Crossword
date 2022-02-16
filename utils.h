//
// Created by moojek on 12/01/2022.
//

#ifndef CROSSWORD_UTILS_H
#define CROSSWORD_UTILS_H

#include <ncurses.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define KEY_ESC 27

#define NO_CODE 0
#define BACK_CODE 1
#define ERR_CODE (-1)
#define CANCEL_CODE 2
#define CONTINUE_CODE 3

#define COL_PAIR_BG 1
#define COL_PAIR_FRAME 1
#define COL_PAIR_PROMPT 1
#define COL_PAIR_MENU 2
#define COL_PAIR_SHADOW 3
#define COL_PAIR_HL 4
#define COL_PAIR_LL 6
#define COL_PAIR_TITLE 7

#define MVWPRINTW_ATTR(attr, win, y, x, ...) wattron(win, attr); \
mvwprintw(win, y, x, __VA_ARGS__); \
wattroff(win, attr);
#define MVWPRINTW_HL(win, y, x, ...) MVWPRINTW_ATTR(COLOR_PAIR(COL_PAIR_HL), win, y, x, __VA_ARGS__)
#define MVWPRINTW_LL(win, y, x, ...) MVWPRINTW_ATTR(COLOR_PAIR(COL_PAIR_LL), win, y, x, __VA_ARGS__)
#define MVWPRINTW_SO(win, y, x, ...) MVWPRINTW_ATTR(A_STANDOUT, win, y, x, __VA_ARGS__)

#define MAX_BOARD_WIDTH 60
#define MAX_BOARD_HEIGHT 60

int exitProgram();

void initColours();

void config();

void throw(char *);

void addTitle(WINDOW *, char *);

int min(int, int);

int max(int ,int);

#endif //CROSSWORD_UTILS_H
