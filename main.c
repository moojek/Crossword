#include <ncurses.h>
#include <stdlib.h>
#include <assert.h>
#include <locale.h>
#include "menus/mainmenu.h"
#include "misc.h"

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "");
    initscr();
    config();

    keypad(stdscr, true);

    createMainMenu();
    operateMainMenu();

//    getch();
    endwin();
    return 0;
}