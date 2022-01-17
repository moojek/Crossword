//
// Created by moojek on 15/01/2022.
//

#include "boards_db.h"

const char *boardsDBFilePathStr = "db_files/boards.db";
FILE *boardsDBFileStream;

int recordCnt;
int (*boardsSizesArr)[2];
long long **boardsContentsArr;

void loadBoardsDB()
{
    boardsDBFileStream = fopen(boardsDBFilePathStr, "r");
    if (boardsDBFileStream) {
        fscanf(boardsDBFileStream, "%d", &recordCnt);
        boardsContentsArr = calloc(recordCnt, sizeof(long long*));
        boardsSizesArr = calloc(recordCnt, sizeof(int[2]));
        for (int i = 0; i < recordCnt; ++i) {
            int w, h;
            fscanf(boardsDBFileStream, "%d %d", &w, &h);
            boardsSizesArr[i][0] = w;
            boardsSizesArr[i][1] = h;
            boardsContentsArr[i] = calloc(h, sizeof(long long));
            for (int j = 0; j < h; ++j)
                fscanf(boardsDBFileStream, "%lld", &(boardsContentsArr[i][j]));
        }
    } else {
        recordCnt = 0;
    }
    fclose(boardsDBFileStream);
}

void updateBoardsDB()
{
    boardsDBFileStream = fopen(boardsDBFilePathStr, "w");
    fprintf(boardsDBFileStream, "%d", recordCnt);
    for (int i = 0; i < recordCnt; ++i) {
        fprintf(boardsDBFileStream, "%d %d ", boardsSizesArr[i][0], boardsSizesArr[i][1]);
        for (int j = 0; j < boardsSizesArr[i][1]; ++j) {
            fprintf(boardsDBFileStream, "%lld", boardsContentsArr[i][j]);
        }
        fprintf(boardsDBFileStream, "\n");
    }
    fclose(boardsDBFileStream);
}

void addBoard(long long* board, int w, int h)
{
    long long** newContentsArr = calloc(recordCnt + 1, sizeof(long long*));
    int (*newSizesArr)[2] = calloc(recordCnt + 1, sizeof(int[2]));

    for (int i = 0; i < recordCnt; ++i) {
        memcpy(newSizesArr[i], boardsSizesArr[i], 2 * sizeof(int));
        memcpy(newContentsArr[i], boardsContentsArr[i], boardsSizesArr[i][1] * sizeof(long long));
    }
    newSizesArr[recordCnt][0] = w;
    newSizesArr[recordCnt][1] = h;
    newContentsArr[recordCnt] = board;

    free(boardsContentsArr);
    free(boardsSizesArr);
    boardsContentsArr = newContentsArr;
    boardsSizesArr = newSizesArr;
    recordCnt++;

    updateBoardsDB();
}

void editBoard(int id, long long* board, int w, int h)
{
    boardsSizesArr[id][0] = w;
    boardsSizesArr[id][1] = h;
    free(boardsContentsArr[id]);
    boardsContentsArr[id] = board;

    updateBoardsDB();
}

void removeBoard(int id)
{
    long long * * newContentsArr = calloc(recordCnt - 1, sizeof(long long*));
    int (* newSizesArr)[2] = calloc(recordCnt - 1, sizeof(int[2]));

    int newId = 0;
    for(int i=0;i<recordCnt;++i) {
        if(i != id) {
            memcpy(newSizesArr[newId], boardsSizesArr[i], 2 * sizeof(int));
            memcpy(newContentsArr[newId], boardsContentsArr[i], boardsSizesArr[i][1] * sizeof(long long));
        }
    }

    free(boardsContentsArr);
    free(boardsSizesArr);
    boardsContentsArr = newContentsArr;
    boardsSizesArr = newSizesArr;
    recordCnt--;

    updateBoardsDB();
}

void getBoard(int id, long long ** boardPtr, int* wPtr, int* hPtr)
{

}

bool isBoardsDBEmpty()
{
    return recordCnt == 0;
}