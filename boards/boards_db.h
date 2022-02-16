//
// Created by moojek on 15/01/2022.
//

#ifndef CROSSWORD_BOARDS_DB_H
#define CROSSWORD_BOARDS_DB_H

#include <stdio.h>
#include <string.h>
#include "../utils.h"

//void createBoardsDB();

void loadBoardsDB();

void updateBoardsDB();

//void closeBoardsDB();

void addBoard(long long *, int, int);

void editBoard(int, long long *, int, int);

// TODO: duplicateBoard

void removeBoard(int);

void getBoard(int, long long **, int *, int *);

bool isBoardsDBEmpty();

#endif //CROSSWORD_BOARDS_DB_H
