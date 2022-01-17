//
// Created by moojek on 11/01/2022.
//

#include "actions.h"

int backFunction()
{
    return BACK_CODE;
}

WINDOW *actionsWin;
PANEL *actionsPanel;
int actionsWinHeight, actionsWinWidth;

#define ACTIONS_CNT 4
const char *actionsStrArr[ACTIONS_CNT] = {"<Add>", "<Edit...>", "<Delete>", "<Back>"};
//char *exitActionsStr = "<Exit>";
//bool shouldOmitMenuOption[ACTIONS_CNT] = {false, false};

int (*actionsFunArr[ACTIONS_CNT])() = {&createBoard, NULL, NULL, &backFunction};

int action = 0;

int actionY(int id)
{
    if (id == ACTIONS_CNT - 1)
        return actionsWinHeight - 1;
    return 2 * id + 1;
}

int actionX(int id)
{
    return 0;
}

void
createActions(int parentMenuHeight, int parentMenuWidth, int selectorWidth, int parentMenuStartY, int parentMenuStartX)
{
    actionsWinHeight = parentMenuHeight - 4;
    actionsWinWidth = parentMenuWidth - (selectorWidth + 5);
    actionsWin = newwin(actionsWinHeight, actionsWinWidth, parentMenuStartY + 2,
                        parentMenuStartX + 2 + selectorWidth + 1);
    wbkgd(actionsWin, COLOR_PAIR(COL_PAIR_MENU));
    for (int i = 0; i < ACTIONS_CNT; ++i)
        mvwprintw(actionsWin, actionY(i), actionX(i), "%s", actionsStrArr[i]);
    actionsPanel = new_panel(actionsWin);
    hide_panel(actionsPanel);
}

void showActions()
{
//    wrefresh(actionsWin);

    show_panel(actionsPanel);

//    update_panels();
//    doupdate();
}

void hideActions()
{
    hide_panel(actionsPanel);

//    update_panels();
//    doupdate();
}

void highlightActions()
{
    MVWPRINTW_HL(actionsWin, actionY(action), actionX(action), "%s", actionsStrArr[action]);
//    wrefresh(actionsWin);
    update_panels();
    doupdate();
}

int operateActions(int keyPress)
{
    int returnCode = NO_CODE;

    mvwprintw(actionsWin, actionY(action), actionX(action), "%s", actionsStrArr[action]);
    switch (keyPress) {
        case KEY_UP:
            if (action != 0)
                action--;
//                if (shouldOmitMenuOption[action])
//                    action--;
            break;
        case KEY_DOWN:
            if (action != ACTIONS_CNT - 1)
                action++;
//                if (shouldOmitMenuOption[action])
//                    action++;
            break;
        case 10:
            returnCode = (*actionsFunArr[action])();
            break;
        default:
            break;
    }
    MVWPRINTW_HL(actionsWin, actionY(action), actionX(action), "%s", actionsStrArr[action]);

    update_panels();
    doupdate();
    return returnCode;
}

void unhighlightActions()
{
    mvwprintw(actionsWin, actionY(action), actionX(action), "%s", actionsStrArr[action]);
//    wrefresh(actionsWin);
    update_panels();
    doupdate();
}