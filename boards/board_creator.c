//
// Created by moojek on 15/01/2022.
//

#include "board_creator.h"

WINDOW *boardSizePromptWin, *boardSizePromptShadowWin, *boardCreatorWin, *boardCreatorShadowWin;
PANEL *boardSizePromptPanel, *boardSizePromptShadowPanel, *boardCreatorPanel, *boardCreatorShadowPanel;
FIELD *boardSizePromptFieldArr[3];
FORM *boardSizePromptForm;
ITEM **boardSizePromptMenuItems;
MENU *boardSizePromptMenu;

#define BOARD_SIZE_PROMPT_MENU_OPTIONS_STR_ARR_SIZE 3
char *boardSizePromptMenuOptionsStrArr[BOARD_SIZE_PROMPT_MENU_OPTIONS_STR_ARR_SIZE] = {
        "<Cancel>",
        "<OK>",
        (char *) NULL,
};
char *boardSizePromptWinTitleStr = "Add board";

int boardSizePromptStartY, boardSizePromptStartX;
int boardCreatorStartY, boardCreatorStartX;

int boardSizePromptHeight, boardSizePromptWidth;
int boardCreatorHeight, boardCreatorWidth;

int activeRow = 0;

int createBoard()
{
    boardSizePromptHeight = 8;
    boardSizePromptWidth = 25;

    boardSizePromptStartY = (LINES - boardSizePromptHeight) / 2;
    boardSizePromptStartX = (COLS - boardSizePromptWidth) / 2;

    boardSizePromptShadowWin = newwin(boardSizePromptHeight, boardSizePromptWidth, boardSizePromptStartY + 1,
                                      boardSizePromptStartX + 1);
    wbkgd(boardSizePromptShadowWin, COLOR_PAIR(COL_PAIR_SHADOW));
    boardSizePromptShadowPanel = new_panel(boardSizePromptShadowWin);
//    hide_panel(boardSizePromptShadowPanel);

    boardSizePromptWin = newwin(boardSizePromptHeight, boardSizePromptWidth, boardSizePromptStartY,
                                boardSizePromptStartX);
    wbkgd(boardSizePromptWin, COLOR_PAIR(COL_PAIR_MENU));
    box(boardSizePromptWin, 0, 0);
    addTitle(boardSizePromptWin, boardSizePromptWinTitleStr);
    MVWPRINTW_LL(boardSizePromptWin, 2, 2, "Width");
    MVWPRINTW_LL(boardSizePromptWin, 3, 2, "Height");
    boardSizePromptFieldArr[0] = new_field(1, 2, 0, 0, 0, 0);
    set_field_type(boardSizePromptFieldArr[0], TYPE_INTEGER);
    set_field_back(boardSizePromptFieldArr[0], COLOR_PAIR(COL_PAIR_PROMPT));
    set_field_fore(boardSizePromptFieldArr[0], COLOR_PAIR(COL_PAIR_PROMPT));
    set_field_pad(boardSizePromptFieldArr[0], '_');
    field_opts_off(boardSizePromptFieldArr[0], O_AUTOSKIP);
    boardSizePromptFieldArr[1] = new_field(1, 2, 1, 0, 0, 0);
    set_field_type(boardSizePromptFieldArr[1], TYPE_INTEGER);
    set_field_back(boardSizePromptFieldArr[1], COLOR_PAIR(COL_PAIR_PROMPT));
    set_field_fore(boardSizePromptFieldArr[1], COLOR_PAIR(COL_PAIR_PROMPT));
    set_field_pad(boardSizePromptFieldArr[1], '_');
    field_opts_off(boardSizePromptFieldArr[1], O_AUTOSKIP);
    boardSizePromptFieldArr[2] = NULL;
    boardSizePromptForm = new_form(boardSizePromptFieldArr);
    set_form_win(boardSizePromptForm, boardSizePromptWin);
    set_form_sub(boardSizePromptForm, derwin(boardSizePromptWin, 2, 2, 2, 9));
    post_form(boardSizePromptForm);
    boardSizePromptMenuItems = (ITEM **) calloc(BOARD_SIZE_PROMPT_MENU_OPTIONS_STR_ARR_SIZE, sizeof(ITEM *));
    for (int i = 0; i < BOARD_SIZE_PROMPT_MENU_OPTIONS_STR_ARR_SIZE; ++i)
        boardSizePromptMenuItems[i] = new_item(boardSizePromptMenuOptionsStrArr[i], "");
    item_opts_off(boardSizePromptMenuItems[1], O_SELECTABLE);
    boardSizePromptMenu = new_menu((ITEM **) boardSizePromptMenuItems);
    set_menu_fore(boardSizePromptMenu, COLOR_PAIR(COL_PAIR_HL));
    set_menu_back(boardSizePromptMenu, COLOR_PAIR(COL_PAIR_MENU));
    set_menu_win(boardSizePromptMenu, boardSizePromptWin);
    set_menu_sub(boardSizePromptMenu, derwin(boardSizePromptWin, 1, 13, 5, 4));
    set_menu_format(boardSizePromptMenu, 1, 2);
    set_menu_mark(boardSizePromptMenu, "");
    post_menu(boardSizePromptMenu);
    boardSizePromptPanel = new_panel(boardSizePromptWin);
//    hide_panel(boardSizePromptPanel);

    update_panels();
    doupdate();

    int keyPress = -1;
    keypad(boardSizePromptWin, true);
    curs_set(1);
    while ((keyPress = wgetch(boardSizePromptWin)) != 10) {
        switch (keyPress) {
            case KEY_DOWN:
                if (activeRow < BOARD_SIZE_PROMPT_MENU_OPTIONS_STR_ARR_SIZE - 2) {
                    form_driver(boardSizePromptForm, REQ_NEXT_FIELD);
                    form_driver(boardSizePromptForm, REQ_END_LINE);
                } else if(activeRow == BOARD_SIZE_PROMPT_MENU_OPTIONS_STR_ARR_SIZE - 2) {
                    
                }
                break;
            case KEY_UP:
                form_driver(boardSizePromptForm, REQ_PREV_FIELD);
                form_driver(boardSizePromptForm, REQ_END_LINE);
                break;
            case KEY_LEFT:
                menu_driver(boardSizePromptMenu, REQ_LEFT_ITEM);
                break;
            case KEY_RIGHT:
                menu_driver(boardSizePromptMenu, REQ_RIGHT_ITEM);
                break;
            default:
                form_driver(boardSizePromptForm, keyPress);
                fprintf(stderr, "Board creator switch default: keyPress = %d\n", keyPress);
                break;
        }
    }
    keypad(boardSizePromptWin, false);
    curs_set(0);
}