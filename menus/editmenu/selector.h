//
// Created by moojek on 12/01/2022.
//

#ifndef CROSSWORD_SELECTOR_H
#define CROSSWORD_SELECTOR_H

#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include "../../utils.h"

void createSelector(int, int, int, int, int);
void showSelector();
void highlightSelector();
int operateSelector(int);
void unhighlightSelector();
void hideSelector();

#endif //CROSSWORD_SELECTOR_H
