//
// Created by moojek on 12/01/2022.
//

#include "mainmenu.h"

WINDOW *mainMenuWin, *mainMenuShadowWin, *mainMenuTitleWin;
PANEL *mainMenuPanel, *mainMenuShadowPanel, *mainMenuTitlePanel;

#define MAIN_MENU_OPTION_CNT 2
void (*createMainMenuSubMenuFunArr[MAIN_MENU_OPTION_CNT - 1])() = {&createEditMenu};

int mainMenuStartY, mainMenuStartX;
int mainMenuHeight, mainMenuWidth;

const char *mainMenuTitleStr = "┤ Crossword helper ├";
const int mainMenuTitleStrLen = 20;
const char *mainMenuSelectStr = "Please select an option";
const char *mainMenuOptionsStrArr[MAIN_MENU_OPTION_CNT] = {/*"Solve a crossword", */"Edit crossword boards", "Quit"};

void (*optionsFunArr[MAIN_MENU_OPTION_CNT])() = {/*NULL,*/ &operateEditMenu, &exitProgram};

int mainMenuOption = 0;

int optionY(int id)
{
    if (id == MAIN_MENU_OPTION_CNT - 1)
        return 4 + MAIN_MENU_OPTION_CNT;
    return 4 + id;
}

int optionX(int id)
{
    return 2;
}

void createMainMenu()
{
//    mainMenuWidth = 28, mainMenuHeight = 12;
    mainMenuWidth = 28, mainMenuHeight = 10;

    if (LINES < mainMenuHeight)
        throw("Too small terminal height");
    if (COLS < mainMenuWidth)
        throw("Too small terminal width");

    mainMenuStartY = (LINES - mainMenuHeight) / 2;
    mainMenuStartX = (COLS - mainMenuWidth) / 2;

    mainMenuShadowWin = newwin(mainMenuHeight, mainMenuWidth, mainMenuStartY, mainMenuStartX);
    wbkgd(mainMenuShadowWin, COLOR_PAIR(COL_PAIR_SHADOW));
    mainMenuShadowPanel = new_panel(mainMenuShadowWin);
    hide_panel(mainMenuShadowPanel);

    mainMenuWin = newwin(mainMenuHeight, mainMenuWidth, mainMenuStartY, mainMenuStartX);
    wbkgd(mainMenuWin, COLOR_PAIR(COL_PAIR_MENU));
    box(mainMenuWin, 0, 0);
    MVWPRINTW_ATTR(COLOR_PAIR(COL_PAIR_LL), mainMenuWin, 2, 2, "%s", mainMenuSelectStr);
    for (int i = 0; i < MAIN_MENU_OPTION_CNT; i++)
        mvwprintw(mainMenuWin, optionY(i), optionX(i), "%s", mainMenuOptionsStrArr[i]);
    mainMenuPanel = new_panel(mainMenuWin);
    hide_panel(mainMenuPanel);

    fprintf(stderr, "mainMenuTitleWin debug: %d %d %d %d\n", mainMenuStartX, mainMenuWidth, mainMenuTitleStrLen,
            mainMenuStartX + (mainMenuWidth - mainMenuTitleStrLen) / 2);
    fprintf(stderr, "basic additional info: %d %d\n", LINES, COLS);
    mainMenuTitleWin = newwin(1, mainMenuTitleStrLen, mainMenuStartY,
                              mainMenuStartX + (mainMenuWidth - mainMenuTitleStrLen) / 2);
    wbkgd(mainMenuTitleWin, COLOR_PAIR(COL_PAIR_MENU));
    wprintw(mainMenuTitleWin, "%s", mainMenuTitleStr);
    mainMenuTitlePanel = new_panel(mainMenuTitleWin);
    hide_panel(mainMenuTitlePanel);

    for (int i = 0; i < MAIN_MENU_OPTION_CNT - 1; ++i)
        (*createMainMenuSubMenuFunArr[i])();

//    refresh();
}

void showMainMenu()
{
//    wrefresh(mainMenuShadowWin);
//    wrefresh(mainMenuWin);
//    wrefresh(mainMenuTitleWin);

    show_panel(mainMenuShadowPanel);
    show_panel(mainMenuPanel);
    show_panel(mainMenuTitlePanel);

    update_panels();
    doupdate();
}

int operateMainMenu()
{
    showMainMenu();

    int keyPress = -1;

    keypad(mainMenuWin, true);
    do {
        mvwprintw(mainMenuWin, optionY(mainMenuOption), optionX(mainMenuOption), "%s",
                  mainMenuOptionsStrArr[mainMenuOption]);
        switch (keyPress) {
            case KEY_UP:
                if (mainMenuOption != 0)
                    mainMenuOption--;
                break;
            case KEY_DOWN:
                if (mainMenuOption != MAIN_MENU_OPTION_CNT - 1)
                    mainMenuOption++;
                break;
            case 10:
                (*optionsFunArr[mainMenuOption])();
                break;
            default:
                break;
        }
        MVWPRINTW_HL(mainMenuWin, optionY(mainMenuOption), optionX(mainMenuOption), "%s",
                     mainMenuOptionsStrArr[mainMenuOption]);
        keyPress = wgetch(mainMenuWin);
    } while (keyPress != KEY_ESC);
    keypad(mainMenuWin, false);
}
