/*
 * file handling logic of the Game of Life
 */

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "logic.h"

Cell *cells;
int cells_num;

// initilizing initial state grid
int initCellsArray(int cols, int rows)
{
    cells_num = numberOfCells(cols, rows);
    int id_cell = 0;
    // allocating memory for the cells in the grid
    cells = malloc(cells_num * sizeof(Cell));
    // represents grid's Xs in the loop
    int i;
    // represents grid's Ys in the loop
    int j;
    for (i = 0; i < MAX_Y; i++)
    {
        j = 0;
        for (j; j < MAX_X; j++)
        {
            (cells + id_cell)->id = id_cell + 1;
            (cells + id_cell)->x = j;
            (cells + id_cell)->y = i;
            (cells + id_cell)->alive = 0;
            id_cell++;
        }
    }
    return 0;
}

// test funnction to check if the cells structure
// is filled correctly
static int drawGrid()
{
    int col = 0;
    printf("    ");
    for (int j = 0; j < MAX_X; j++)
    {
        printf("%d ", j);
    }

    printf("\n");

    for (int i = 0; i < cells_num; i++)
    {
        if (i % MAX_X == 0)
        {
            printf("%.2d  ", col);
        }

        if ((cells + i)->alive == 0)
        {
            printf("0 ");
        }
        else
        {
            printf("I ");
        }

        if ((cells + i)->id % MAX_X == 0 && (cells + i)->id != 0)
        {
            col++;
            printf("\n");
        }
    }

    return 0;
}

// set up an initial(default) pattern(glider) approximately in the middle of the
// grid
int initialPattern(Cell *cellsArray, int numOfCells)
{
    // finding the middle width and middle height cell with binary search
    // algorithm
    int middle_width = MAX_X / 2;
    int middle_height = MAX_Y / 2;
    int array_size = numOfCells;
    int middle, middle_id;
    bool founded = false;
    middle = numOfCells / 2;
    // finding the cell with middle_width and middle_height
    // searching below id = middle
    for (int i = middle; i > 0; i--)
    {
        if (((cellsArray + i)->x == middle_width) &&
            ((cellsArray + i)->y == middle_height))
        {
            (cellsArray + i)->alive = 1;
            founded = true;
            middle_id = i;
            break;
        }
    }
    // if not found before searching above id=middle
    if (founded == false)
    {
        for (int j = middle; j < cells_num; j++)
        {
            if (((cellsArray + j)->x == middle_width) &&
                ((cellsArray + j)->y == middle_height))
            {
                (cellsArray + j)->alive = 1;
                founded = true;
                middle_id = j;
                break;
            }
        }
    }

    /*'drawing' pattern depending on found cell
     *first added number is up or down to the middle cell
     *second added number is left or right to the middle cell
     */
    // making alive rest of four cells
    (cellsArray + middle_id + 1 + MAX_X)->alive = 1;
    (cellsArray + middle_id + 1 + (MAX_X * 2))->alive = 1;
    (cellsArray + middle_id + 0 + (MAX_X * 2))->alive = 1;
    (cellsArray + middle_id - 1 + (MAX_X * 2))->alive = 1;

    return 0;
}

// count neihgbours of the cell
int checkNeighbours(Cell *cell)
{
    int aliveNeigh = 0;
    Cell dead_out_cell;
    Cell *upCell = NULL;
    Cell *downCell = NULL;
    Cell *leftCell = NULL;
    Cell *rightCell = NULL;
    Cell *upLeftCell = NULL;
    Cell *upRightCell = NULL;
    Cell *downLeftCell = NULL;
    Cell *downRightCell = NULL;
    dead_out_cell.id = -1;
    dead_out_cell.x = -1;
    dead_out_cell.y = -1;
    dead_out_cell.alive = 0;

    // p-1-max_x p-max_x P-1-max_x
    // p-1         p       P+1
    // p-1+max_x   p+max_x p+1+max_x

    /* if cell is on the edges, the cells that surround it
     and outside the grid are setting up to as dead cell*/
    // upCell check
    if (cell->y == 0)
    {
        upCell = &dead_out_cell;
        upLeftCell = &dead_out_cell;
        upRightCell = &dead_out_cell;
    }
    else
    {
        upCell = (cell - MAX_X);
        upLeftCell = (cell - 1 - MAX_X);
        upRightCell = (cell + 1 - MAX_X);
    }

    // downCell check
    if (cell->y == MAX_Y - 1)
    {
        downCell = &dead_out_cell;
        downLeftCell = &dead_out_cell;
        downRightCell = &dead_out_cell;
    }
    else
    {
        downCell = (cell + MAX_X);
        downLeftCell = (cell - 1 + MAX_X);
        downRightCell = (cell + 1 + MAX_X);
    }

    // leftCell
    if (cell->x == 0)
    {
        leftCell = &dead_out_cell;
        upLeftCell = &dead_out_cell;
        downLeftCell = &dead_out_cell;
    }
    else
    {
        leftCell = (cell - 1);
    }

    // rightCell
    if (cell->x == MAX_X - 1)
    {
        rightCell = &dead_out_cell;
        upRightCell = &dead_out_cell;
        downRightCell = &dead_out_cell;
    }
    else
    {
        rightCell = (cell + 1);
    }

    if (upCell->alive == 1)
        aliveNeigh++;
    if (downCell->alive == 1)
        aliveNeigh++;
    if (leftCell->alive == 1)
        aliveNeigh++;
    if (rightCell->alive == 1)
        aliveNeigh++;
    if (upLeftCell->alive == 1)
        aliveNeigh++;
    if (upRightCell->alive == 1)
        aliveNeigh++;
    if (downLeftCell->alive == 1)
        aliveNeigh++;
    if (downRightCell->alive == 1)
        aliveNeigh++;

    return aliveNeigh;
}

// make next generations based on current state of cells
int nextGen()
{
    // rules
    /*
     * 1. Any live cell with fewer than two live neighbours dies
     * 2. Any live cell with two or three live neighbours lives on to the next
     * generation.
     * 3. Any live cell with more than three live neighbours dies
     * 4. Any dead cell with exactly three live neighbours becomes a live cell
     */

    Cell *temp_cells; // stores cells of next generation
    Cell *current_cell = NULL;
    Cell *current_temp_cell = NULL;

    temp_cells = malloc(cells_num * sizeof(Cell));

    for (int i = 0; i < cells_num; i++)
    {
        current_cell = (cells + i);
        current_temp_cell = (temp_cells + i);

        current_temp_cell->id = current_cell->id;
        current_temp_cell->x = current_cell->x;
        current_temp_cell->y = current_cell->y;
        current_temp_cell->alive = current_cell->alive;

        if (current_cell->alive == 1)
        {
            if ((checkNeighbours(current_cell) < 2) || (checkNeighbours(current_cell) > 3))
            {
                current_temp_cell->alive = 0;
            }
        }
        else
        {
            if (checkNeighbours(current_cell) == 3)
            {
                current_temp_cell->alive = 1;
            }
            else
            {
                current_temp_cell->alive = 0;
            }
        }
    }

    for (int j = 0; j < cells_num; j++)
    {
        (cells + j)->alive = (temp_cells + j)->alive;
    }

    free(temp_cells);
    temp_cells = NULL;

    return 0;
}

