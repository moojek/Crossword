//
// Created by moojek on 11/01/2022.
//

#ifndef CROSSWORD_ACTIONS_H
#define CROSSWORD_ACTIONS_H

#include <ncurses.h>
#include <panel.h>
#include "../../misc.h"

void createActions(int, int, int, int, int);
void showActions();
void highlightActions();
int operateActions(int);
void unhighlightActions();
void hideActions();

#endif //CROSSWORD_ACTIONS_H
