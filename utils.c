//
// Created by moojek on 12/01/2022.
//
#include "utils.h"

int exitProgram()
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
    init_pair(COL_PAIR_TITLE, COLOR_RED, COLOR_WHITE);
}

void config()
{
    noecho();
    cbreak();

    curs_set(0);

    initColours();
    bkgd(COLOR_PAIR(COL_PAIR_BG));
}

void throw(char *msg)
{
    fprintf(stderr, msg);
    exit(-1);
}

void addTitle(WINDOW *win, char *titleStr)
{
    int winWidth = getmaxx(win);
    fprintf(stderr, "addTitle for \"%s\": getmaxx(win) = %d, getbegx(win) = %d, winWidth = %d\n", titleStr,
            getmaxx(win), getbegx(win), winWidth);
    int titleStartX = (winWidth - (strlen(titleStr) + 4)) / 2;
    mvwprintw(win, 0, titleStartX, "┤ ");
    wattron(win, COLOR_PAIR(COL_PAIR_TITLE));
    mvwprintw(win, 0, titleStartX + 2, "%s", titleStr);
    wattroff(win, COLOR_PAIR(COL_PAIR_TITLE));
    mvwprintw(win, 0, titleStartX + 2 + strlen(titleStr), " ├");
}