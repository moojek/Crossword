//
// Created by moojek on 06/01/2022.
//

#include "editmenu.h"

WINDOW *editMenuWin, *editMenuShadowWin;
PANEL *editMenuPanel, *editMenuShadowPanel;

int editmenuStartX, editmenuStartY;
int editmenuWinWidth, editmenuWinHeight;

int selectorWidth;

void createEditMenu()
{
    editmenuWinWidth = 41, editmenuWinHeight = 15;
    selectorWidth = 27;

    if (LINES < editmenuWinHeight)
        throw("Too small terminal height");
    if (COLS < editmenuWinWidth)
        throw("Too small terminal width");

    editmenuStartY = (LINES - editmenuWinHeight) / 2;
    editmenuStartX = (COLS - editmenuWinWidth) / 2;

    editMenuShadowWin = newwin(editmenuWinHeight, editmenuWinWidth, editmenuStartY + 1, editmenuStartX + 1);
    wbkgd(editMenuShadowWin, COLOR_PAIR(COL_PAIR_SHADOW));
    editMenuShadowPanel = new_panel(editMenuShadowWin);
    hide_panel(editMenuShadowPanel);

    editMenuWin = newwin(editmenuWinHeight, editmenuWinWidth, editmenuStartY, editmenuStartX);
    wbkgd(editMenuWin, COLOR_PAIR(COL_PAIR_MENU));
    box(editMenuWin, 0, 0);
    editMenuPanel = new_panel(editMenuWin);
    hide_panel(editMenuPanel);

    createActions(editmenuWinHeight, editmenuWinWidth, selectorWidth, editmenuStartY, editmenuStartX);

    createSelector(editmenuWinHeight, editmenuWinWidth, selectorWidth, editmenuStartY, editmenuStartX);
}

void showEditMenu()
{
    show_panel(editMenuShadowPanel);
    show_panel(editMenuPanel);
    showSelector();
    showActions();

    update_panels();
    doupdate();
}

void hideEditMenu()
{
    hideActions();
    hideSelector();
    hide_panel(editMenuPanel);
    hide_panel(editMenuShadowPanel);

    update_panels();
    doupdate();
}

int operateEditMenu()
{
    showEditMenu();

    int keyPress = -1;
    int (*operateFun)(int);

    // TODO
    if (true) { // boards empty
        highlightActions();
        operateFun = &operateActions;
    } else {
        highlightSelector();
        operateFun = &operateSelector;
    }

    int returnCode;
    keypad(editMenuWin, true);
    do {
        returnCode = 0;

        fprintf(stderr, "Before switch, keyPress = %d\n", keyPress);
        switch (keyPress) {
            case KEY_LEFT:
                fprintf(stderr, "case KEY_LEFT:\n");
                if (false) { // !boards empty
                    unhighlightActions();
                    highlightSelector();
                    operateFun = &operateSelector;
                }
                break;
            case KEY_RIGHT:
                unhighlightSelector();
                highlightActions();
                operateFun = &operateActions;
                break;
            default:
                returnCode = (*operateFun)(keyPress);
                break;
        }
//        keyPress = wgetch(editMenuWin);
    } while (returnCode != BACK_CODE && (keyPress = wgetch(editMenuWin)) != KEY_ESC);
    keypad(editMenuWin, false);
    fprintf(stderr, "Esc key assumed. keyPress == %d\n", (int) keyPress);
    hideEditMenu();
}