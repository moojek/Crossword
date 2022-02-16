//
// Created by moojek on 06/01/2022.
//

#ifndef CROSSWORD_EDITMENU_H
#define CROSSWORD_EDITMENU_H

#include <ncurses.h>
#include <panel.h>
#include <stdlib.h>
#include "editmenu/actions.h"
#include "editmenu/selector.h"
#include "../utils.h"

void createEditMenu();
void showEditMenu();
int operateEditMenu();
void hideEditMenu();

#endif //CROSSWORD_EDITMENU_H
