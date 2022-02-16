//
// Created by moojek on 15/01/2022.
//

#include "board_creator.h"

int cancelFun()
{
    return CANCEL_CODE;
}

int okFun()
{
    return CONTINUE_CODE;
}

WINDOW *boardSizePromptWin, *boardSizePromptShadowWin, *boardCreatorWin, *boardCreatorShadowWin;
PANEL *boardSizePromptPanel, *boardSizePromptShadowPanel, *boardCreatorPanel, *boardCreatorShadowPanel;
FIELD *boardSizePromptFieldArr[3];
FORM *boardSizePromptForm;
ITEM **boardSizePromptMenuItems, **boardCreatorMenuItems;
MENU *boardSizePromptMenu, *boardCreatorMenu;

#define BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT 2
char *boardSizePromptMenuOptionsStrArr[BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT + 1] = {"<Cancel>", "<OK>", (char *) NULL,};
#define BOARD_CREATOR_MENU_OPTIONS_CNT 2
char *boardCreatorMenuOptionsStrArr[BOARD_CREATOR_MENU_OPTIONS_CNT + 1] = {"<OK>", "<Cancel>", (char *) NULL};
char *boardSizePromptWinTitleStr = "Add board";

int boardSizePromptStartY, boardSizePromptStartX;
int boardCreatorStartY, boardCreatorStartX;

int boardSizePromptHeight, boardSizePromptWidth;
int boardCreatorHeight, boardCreatorWidth;

int activeRow;

bool boardSizePromptOkButtonAvailable()
{
    return form_driver(boardSizePromptForm, REQ_VALIDATION) == E_OK &&
           strcmp(field_buffer(boardSizePromptFieldArr[0], 0), "  ") != 0 &&
           strcmp(field_buffer(boardSizePromptFieldArr[1], 0), "  ") != 0;
}

void controlBoardSizePromptOkButtonHighlight()
{
    if (boardSizePromptOkButtonAvailable()) {
//        fprintf(stderr, "Height bufffer: <%s>", field_buffer(boardSizePromptFieldArr[1], 0));
        item_opts_on(boardSizePromptMenuItems[1], O_SELECTABLE);
        set_current_field(boardSizePromptForm, current_field(boardSizePromptForm));
        form_driver(boardSizePromptForm, REQ_END_LINE);
    } else {
        item_opts_off(boardSizePromptMenuItems[1], O_SELECTABLE);
        set_current_field(boardSizePromptForm, current_field(boardSizePromptForm));
        form_driver(boardSizePromptForm, REQ_END_LINE);
    }
}

void activateAndSelectBoardSizePromptMenu()
{
    curs_set(0);
    set_menu_fore(boardSizePromptMenu, COLOR_PAIR(COL_PAIR_HL));
    menu_driver(boardSizePromptMenu, REQ_FIRST_ITEM);
}

void deactivateBoardSizePromptMenu()
{
    curs_set(1);
    set_menu_fore(boardSizePromptMenu, COLOR_PAIR(COL_PAIR_MENU));
}

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
    boardSizePromptMenuItems = (ITEM **) calloc(BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT + 1, sizeof(ITEM *));
    for (int i = 0; i < BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT + 1; ++i)
        boardSizePromptMenuItems[i] = new_item(boardSizePromptMenuOptionsStrArr[i], "");
    set_item_userptr(boardSizePromptMenuItems[0], &cancelFun);
    set_item_userptr(boardSizePromptMenuItems[1], &okFun);
    item_opts_off(boardSizePromptMenuItems[1], O_SELECTABLE);
    boardSizePromptMenu = new_menu((ITEM **) boardSizePromptMenuItems);
//    set_menu_fore(boardSizePromptMenu, COLOR_PAIR(COL_PAIR_HL));
    set_menu_fore(boardSizePromptMenu, COLOR_PAIR(COL_PAIR_MENU));
    set_menu_back(boardSizePromptMenu, COLOR_PAIR(COL_PAIR_MENU));
    set_menu_grey(boardSizePromptMenu, COLOR_PAIR(COL_PAIR_LL));
    set_menu_win(boardSizePromptMenu, boardSizePromptWin);
    set_menu_sub(boardSizePromptMenu, derwin(boardSizePromptWin, 1, 13, 5, 10));
    set_menu_format(boardSizePromptMenu, 1, 2);
    set_menu_mark(boardSizePromptMenu, NULL);
    post_menu(boardSizePromptMenu);
    boardSizePromptFieldArr[0] = new_field(1, 2, 0, 0, 0, 0);
    set_field_type(boardSizePromptFieldArr[0], TYPE_INTEGER, 0, 1, MAX_BOARD_WIDTH);
    set_field_back(boardSizePromptFieldArr[0], COLOR_PAIR(COL_PAIR_PROMPT));
    set_field_fore(boardSizePromptFieldArr[0], COLOR_PAIR(COL_PAIR_PROMPT));
    set_field_pad(boardSizePromptFieldArr[0], '_');
    field_opts_off(boardSizePromptFieldArr[0], O_AUTOSKIP);
    field_opts_off(boardSizePromptFieldArr[0], O_NULLOK);
    boardSizePromptFieldArr[1] = new_field(1, 2, 1, 0, 0, 0);
    set_field_type(boardSizePromptFieldArr[1], TYPE_INTEGER, 0, 1, MAX_BOARD_HEIGHT);
    set_field_back(boardSizePromptFieldArr[1], COLOR_PAIR(COL_PAIR_PROMPT));
    set_field_fore(boardSizePromptFieldArr[1], COLOR_PAIR(COL_PAIR_PROMPT));
    set_field_pad(boardSizePromptFieldArr[1], '_');
    field_opts_off(boardSizePromptFieldArr[1], O_AUTOSKIP);
    field_opts_off(boardSizePromptFieldArr[1], O_NULLOK);
    boardSizePromptFieldArr[2] = NULL;
    boardSizePromptForm = new_form(boardSizePromptFieldArr);
    set_form_win(boardSizePromptForm, boardSizePromptWin);
    set_form_sub(boardSizePromptForm, derwin(boardSizePromptWin, 2, 2, 2, 9));
    post_form(boardSizePromptForm);
    boardSizePromptPanel = new_panel(boardSizePromptWin);
//    hide_panel(boardSizePromptPanel);

    update_panels();
    doupdate();

    int keyPress = KEY_UP;
    activeRow = 0;
    int returnCode;
    keypad(boardSizePromptWin, true);
    curs_set(1);
    do {
        returnCode = 0;
        switch (keyPress) {
            case KEY_DOWN:
                if (activeRow == BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT - 1) {
//                    fprintf(stderr, "From last form to menu\n");
                    activateAndSelectBoardSizePromptMenu();
                    activeRow++;
                } else if (activeRow < BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT - 1) {
                    if (form_driver(boardSizePromptForm, REQ_DOWN_FIELD) == E_OK) {
//                        fprintf(stderr, "From normal row to next row\n");
                        form_driver(boardSizePromptForm, REQ_END_LINE);
                        activeRow++;
                    } else {
//                        fprintf(stderr, "From normal row to menu\n");
                        activateAndSelectBoardSizePromptMenu();
                        activeRow = BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT;
                    }
                }
                break;
            case KEY_UP:
                if (activeRow == BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT) {
                    deactivateBoardSizePromptMenu();
                    if (form_driver(boardSizePromptForm, REQ_VALIDATION) != E_OK &&
                        strcmp(field_buffer(boardSizePromptFieldArr[1], 0), "  ") == 0) {
                        form_driver(boardSizePromptForm, REQ_FIRST_FIELD);
                        activeRow = 0;
                    } else {
                        form_driver(boardSizePromptForm, REQ_LAST_FIELD);
                        activeRow--;
                    }
                    form_driver(boardSizePromptForm, REQ_END_LINE);
                } else if (activeRow > 0) {
                    if (form_driver(boardSizePromptForm, REQ_UP_FIELD) == E_OK) {
                        form_driver(boardSizePromptForm, REQ_END_LINE);
                        activeRow--;
                    }
                }
                break;
            case KEY_LEFT:
                if (activeRow < BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT)
                    form_driver(boardSizePromptForm, REQ_LEFT_CHAR);
                else
                    menu_driver(boardSizePromptMenu, REQ_LEFT_ITEM);
                break;
            case KEY_RIGHT:
//                fprintf(stderr, "went right\n");
                if (activeRow < BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT)
//                    if() TODO: make KEY_RIGHT not go above all input letters
                    form_driver(boardSizePromptForm, REQ_RIGHT_CHAR);
                else if (boardSizePromptOkButtonAvailable())
                    menu_driver(boardSizePromptMenu, REQ_RIGHT_ITEM);
                break;
            case KEY_BACKSPACE:
                if (activeRow < BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT) {
//                    fprintf(stderr, "Action backspace in if!\n");
                    form_driver(boardSizePromptForm, REQ_DEL_PREV);
                    controlBoardSizePromptOkButtonHighlight();
                }
                break;
//            case KEY_DC: // TODO: implement delete key
//                if(activeRow < BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT) {
//                    form_driver(boardSizePromptForm, REQ_DEL_)
//                }
            case 10:
                if (activeRow == BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT) {
                    returnCode = (*(int (*)()) item_userptr(current_item(boardSizePromptMenu)))();
                } else if (activeRow < BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT && boardSizePromptOkButtonAvailable()) {
                    returnCode = CONTINUE_CODE;
                }
                break;
            default:
                if (activeRow < BOARD_SIZE_PROMPT_MENU_OPTIONS_CNT) {
                    form_driver(boardSizePromptForm, keyPress);
                    controlBoardSizePromptOkButtonHighlight();
                }
//                fprintf(stderr, "Board creator switch default: keyPress = %d/%d\n", keyPress, KEY_BACKSPACE);
                break;
        }
    } while (returnCode == NO_CODE && (keyPress = wgetch(boardSizePromptWin)) != KEY_ESC);
    keypad(boardSizePromptWin, false);
    curs_set(0);

    int newBoardWidth, newBoardHeight;
    newBoardWidth = atoi(field_buffer(boardSizePromptFieldArr[0], 0));
    newBoardHeight = atoi(field_buffer(boardSizePromptFieldArr[1], 0));

    unpost_form(boardSizePromptForm);
    free_form(boardSizePromptForm);
    free_field(boardSizePromptFieldArr[0]);
    free_field(boardSizePromptFieldArr[1]);
    unpost_menu(boardSizePromptMenu);
    free_item(boardSizePromptMenuItems[0]);
    free_item(boardSizePromptMenuItems[1]);
    free_menu(boardSizePromptMenu);
    del_panel(boardSizePromptPanel);
    delwin(boardSizePromptWin);
    del_panel(boardSizePromptShadowPanel);
    delwin(boardSizePromptShadowWin);

    update_panels();
    doupdate();

    if (keyPress == KEY_ESC || returnCode == CANCEL_CODE)
        return CANCEL_CODE;

    if (returnCode != CONTINUE_CODE)
        return ERR_CODE;

//    boardCreatorWidth = COLS - 2;
//    boardCreatorHeight = LINES - 2;
    boardCreatorWidth = newBoardWidth + 17;
    boardCreatorHeight = newBoardHeight + 6;

    boardCreatorStartY = (LINES - boardCreatorHeight) / 2;
    boardCreatorStartX = (COLS - boardCreatorWidth) / 2;

//    boardCreatorShadowWin = newwin(boardCreatorHeight, boardCreatorWidth, boardCreatorStartY + 1,
//                                   boardCreatorStartX + 1);
//    wbkgd(boardCreatorShadowWin, COLOR_PAIR(COL_PAIR_SHADOW));
//    boardCreatorShadowPanel = new_panel(boardCreatorShadowWin);
//    hide_panel(boardCreatorShadowPanel);

    boardCreatorWin = newwin(boardCreatorHeight, boardCreatorWidth, boardCreatorStartY, boardCreatorStartX);
    wbkgd(boardCreatorWin, COLOR_PAIR(COL_PAIR_MENU));
    box(boardCreatorWin, 0, 0);
    boardCreatorMenuItems = (ITEM **) calloc(BOARD_CREATOR_MENU_OPTIONS_CNT + 1, sizeof(ITEM *));
    for (int i = 0; i < BOARD_CREATOR_MENU_OPTIONS_CNT + 1; ++i)
        boardCreatorMenuItems[i] = new_item(boardCreatorMenuOptionsStrArr[i], "");
    set_item_userptr(boardCreatorMenuItems[0], &cancelFun);
    set_item_userptr(boardCreatorMenuItems[1], &okFun);
    boardCreatorMenu = new_menu((ITEM **) boardCreatorMenuItems);
//    set_menu_fore(boardCreatorMenu, COLOR_PAIR(COL_PAIR_HL));
    set_menu_fore(boardCreatorMenu, COLOR_PAIR(COL_PAIR_MENU));
    set_menu_back(boardCreatorMenu, COLOR_PAIR(COL_PAIR_MENU));
    set_menu_win(boardCreatorMenu, boardCreatorWin);
    set_menu_sub(boardCreatorMenu, derwin(boardCreatorWin, 3, 8, 3, 2 + newBoardWidth + 3));
    set_menu_format(boardCreatorMenu, 3, 1);
    set_menu_spacing(boardCreatorMenu, 0, 2, 1);
    set_menu_mark(boardCreatorMenu, NULL);
//    post_menu(boardCreatorMenu);
    boardCreatorPanel = new_panel(boardCreatorWin);
//    hide_panel(boardCreatorPanel);

//    WINDOW *boardEditorDerWin = derwin(boardCreatorWin, newBoardHeight + 2, newBoardWidth + 2, 2, 2);
//    box(boardEditorDerWin, 0, 0);
//    PANEL *boardEditorDerPanel = new_panel(boardEditorDerWin);

//    update_panels();
//    doupdate();

    int y, x;
    getyx(boardCreatorWin, y, x);
//    fprintf(stderr, "cursor position %d %d\n", y, x);
//    fprintf(stderr, "wmove return code: %d/%d/%d\n", wmove(boardCreatorWin, 1, 2), OK, ERR);
    getyx(boardCreatorWin, y, x);
//    fprintf(stderr, "cursor position %d %d\n", y, x);
//    fprintf(stderr, "curs_set return code: %d/%d", curs_set(1), ERR);
    wprintw(boardCreatorWin, "abc");
//    wmove(boardEditorDerWin, 1, 1);
//    wprintw(boardEditorDerWin, "abc");
    update_panels();
    doupdate();

//    int boardCreatorXPos = 0, boardCreatorYPos = 0;
//    keyPress = -1;
//    returnCode = NO_CODE;
//    do {
//        switch (keyPress) {
//            case KEY_UP:
//                wmove(boardEditorDerWin, max(boardCreatorYPos - 1, 1), boardCreatorXPos);
//                break;
//            case KEY_DOWN:
//                wmove(boardEditorDerWin, min(boardCreatorYPos + 1, newBoardHeight - 2), boardCreatorXPos);
//                break;
//            case KEY_LEFT:
//                wmove(boardEditorDerWin, boardCreatorYPos, max(boardCreatorXPos - 1, 1));
//                break;
//            case KEY_RIGHT:
//                if (boardCreatorXPos + 1 <= newBoardHeight - 2)
//                    wmove(boardEditorDerWin, boardCreatorYPos, boardCreatorXPos + 1);
//                break;
//        }
//
//        update_panels();
//        doupdate();
//        keyPress = wgetch(boardCreatorWin);
//    } while (returnCode == NO_CODE);

    getch();

    curs_set(0);

//    del_panel(boardEditorDerPanel);
//    delwin(boardEditorDerWin);
    del_panel(boardCreatorPanel);
    delwin(boardCreatorWin);
    del_panel(boardCreatorShadowPanel);
    delwin(boardCreatorShadowWin);
    update_panels();
    doupdate();
//
//    getch();
}