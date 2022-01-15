//
// Created by moojek on 12/01/2022.
//
#include "misc.h"

void exitProgram()
{
    endwin();
    exit(0);
}

void initColours()
{
    assert(has_colors());
    start_color();
    init_pair(COL_PAIR_BG, COLOR_WHITE, COLOR_BLUE);
    init_pair(COL_PAIR_SHADOW, COLOR_WHITE, COLOR_BLACK);
    init_pair(COL_PAIR_MENU, COLOR_BLACK, COLOR_WHITE);
    init_pair(COL_PAIR_HL, COLOR_WHITE, COLOR_RED);
    init_pair(COL_PAIR_LL, COLOR_BLUE, COLOR_WHITE);
}

void config()
{
    noecho();
    cbreak();

    curs_set(0);

    initColours();
    bkgd(COLOR_PAIR(COL_PAIR_BG));
}

void throw(char* msg)
{
    fprintf(stderr, msg);
    exit(-1);
}