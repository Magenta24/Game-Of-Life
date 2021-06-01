#ifndef LOGIC_H
#define LOGIC_H

typedef struct{
    int id;
    int x;
    int y;
    int alive;
}Cell;

//pointer to array of cells
extern Cell *cells;
extern int cells_num;

//funtions prototypes
int initCellsArray(int cols, int rows);
int initialPattern(Cell *cellsArray, int numOfCells);
int checkNeighbours(Cell *cell);
int nextGen();

#endif /* LOGIC_H */