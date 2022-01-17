//
// Created by moojek on 12/01/2022.
//

#include "selector.h"

#define COL_PAIR_MENU 2

WINDOW *selectorWin, *emptySelectorWin;
PANEL *selectorPanel, *emptySelectorPanel;

bool isSelectorEmpty;
char *emptySelectorStr = "No crosswords";

int selection = 0;

int selectionY(int id)
{
    return id + 1;
}

int selectionX(int id)
{
    return 1;
}

void createSelector(int menuHeight, int menuWidth, int selectorWidth, int menuStartY, int menuStartX)
{
    selectorWin = newwin(menuHeight - 4, selectorWidth, menuStartY + 2, menuStartX + 2);
    wbkgd(selectorWin, COLOR_PAIR(COL_PAIR_MENU));
    box(selectorWin, 0, 0);
    // TODO: populate the window with saved crossword boards
    selectorPanel = new_panel(selectorWin);
    hide_panel(selectorPanel);

//    emptySelectorTextWin = newwin(1, strlen(emptySelectorStr), (menuStartY + 2 + menuStartY + 2 + menuHeight - 4) / 2,
//                                  (menuStartX + 2 + menuStartX + 2 + selectorWidth - strlen(emptySelectorStr)) / 2);
//    mvwprintw(emptySelectorTextWin, 0, 0, "%s", emptySelectorStr);
//    emptySelectorTextPanel = new_panel(emptySelectorTextWin);
//    hide_panel(emptySelectorTextPanel);
    emptySelectorWin = newwin(menuHeight - 4, selectorWidth, menuStartY + 2, menuStartX + 2);
    wbkgd(emptySelectorWin, COLOR_PAIR(COL_PAIR_MENU));
    box(emptySelectorWin, 0, 0);
    MVWPRINTW_ATTR(COLOR_PAIR(COL_PAIR_LL), emptySelectorWin, (menuHeight - 4) / 2, (selectorWidth - strlen(emptySelectorStr)) / 2, "%s", emptySelectorStr);
    emptySelectorPanel = new_panel(emptySelectorWin);
    hide_panel(emptySelectorPanel);
}

void showSelector()
{
//    wrefresh(selectorWin);
//    wrefresh(emptySelectorTextWin);

    if (!isBoardsDBEmpty()) // TODO: check correctness
        show_panel(selectorPanel);
    else
        show_panel(emptySelectorPanel);

//    update_panels();
//    doupdate();
}

void hideSelector()
{
    hide_panel(selectorPanel);
    hide_panel(emptySelectorPanel);

//    update_panels();
//    doupdate();
}

void highlightSelector()
{
    wattron(selectorWin, COLOR_PAIR(COL_PAIR_FRAME));
    wattron(emptySelectorWin, COLOR_PAIR(COL_PAIR_FRAME));
    box(selectorWin, 0, 0);
    box(emptySelectorWin, 0, 0);
    wattroff(selectorWin, COLOR_PAIR(COL_PAIR_FRAME));
    wattroff(emptySelectorWin, COLOR_PAIR(COL_PAIR_FRAME));
//    MVWPRINTW_HL(selectorWin, selectionY(selection), selectionX(selection), "%s", selectionsStrArr[selection]);

    update_panels();
    doupdate();
}

int operateSelector(int keyPress)
{
//    mvwprintw(selectorWin, selectionY(selection), selectionX(selection), "%s", selectionsStrArr[selection]);
//    switch (keyPress) {
//        case KEY_UP:
//            if (selection != 0)
//                selection--;
////                if (shouldOmitMenuOption[selection])
////                    selection--;
//            break;
//        case KEY_DOWN:
//            if (selection != ACTIONS_CNT - 1)
//                selection++;
////                if (shouldOmitMenuOption[selection])
////                    selection++;
//            break;
//        case 10:
//            (*selectionsFunArr[selection])();
//            break;
//        default:
//            break;
//    }
////    MVWPRINTW_HL(selectorWin, selectionY(selection), selectionX(selection), "%s", selectionsStrArr[selection]);
//    wrefresh(selectorWin);
}

void unhighlightSelector()
{
    box(selectorWin, 0, 0);
    box(emptySelectorWin, 0, 0);
//    mvwprintw(selectorWin, selectionY(selection), selectionX(selection), "%s", selectionsStrArr[selection]);
//    wrefresh(selectorWin);

    update_panels();
    doupdate();
}