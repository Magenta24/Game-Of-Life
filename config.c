/*
* configurable file of the Game of Life
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#include "config.h"
#include "logic.h"

//default screen width and height
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int MAX_X;
int MAX_Y;

// loaded world from a file
// size of the world + number of '\n' signs at the ends of lines
int sizeOfLoadedWord = 0;
// size of the world laoded from a file
int LOADED_COLS = 0;
int LOADED_ROWS = 0;

// return number of cells(cols = number of cells horizontally, rows = vertically)
// and also set up MAX_X and MAX_Y values
int numberOfCells(int cols, int rows)
{
    int cell_num;

    SCREEN_WIDTH = cols * CELL_SIZE;
    SCREEN_HEIGHT = rows * CELL_SIZE;

    cell_num = cols * rows;
    MAX_X = cols;
    MAX_Y = rows;

    return cell_num;
}

// store the data in the file
int dataToFile(char *filename)
{
    FILE *openedWrite;
    openedWrite = fopen(filename, "w");
    char *width_and_height = malloc(20 * sizeof(char));
    char *width = malloc(5 * sizeof(char));
    char *height = malloc(5 * sizeof(char));

    int col_counter = 0;

    if (!openedWrite)
    {
        printf("Sorry cannot open the file :(");
        return 1;
    }
    else
    {
        // converting MAX_X and MAX_Y to strings
        snprintf(width,sizeof(width),"%d",MAX_X);
        snprintf(height,sizeof(height),"%d",MAX_Y);

        strcpy(width_and_height, width);
        strcat(width_and_height, " ");
        strcat(width_and_height, height);
        strcat(width_and_height, "\n");

        fprintf(openedWrite, width_and_height);
        for(int i=0;i<cells_num;i++){
            if((cells + i)->alive == 1){
                fprintf(openedWrite, "1");
            }else{
                fprintf(openedWrite, "0");
            }

            if(col_counter == (MAX_X - 1)){
                fprintf(openedWrite,"\n");
                col_counter = 0;
                continue;
            }

            col_counter++;
        }

    }

    fclose(openedWrite);
    return 0;
}

/* read world configuration from the given file
*  the file should contain:
*  - in the first line(seperated by space):
*       number of columns of cells
*       number of rows of cells
*  - from the second line the map starts (0s represent dead cells
*    and 1s alive cells)
*    example of a map of size 10x5:
     10 5
*    0000000000
*    0000010000
*    0001110000
*    0000000000
*    0000000000
*/
int *readData(FILE *file)
{
    int lineCounter = 0;
    int wordCounter = 0;
    int columnCounter = 0;
    int wordNumChar = 0;

    int cellsPointerId = 0;

    char word[5];
    char save[200];

    int *loadedWorld;

    if (file == NULL)
    {
        printf("\nFile cannot be opened :(\n");
        return NULL;
    }
    else
    {
        while (fgets(save, sizeof(save), file) != NULL)
        {
            //reading rows and columns number
            if (lineCounter == 0)
            {
                for (int i = 0; i < strlen(save); i++)
                {
                    if (save[i] == ' ' || save[i] == '\n')
                    {
                        word[i] = '\0';

                        if (wordCounter == 0)
                        {
                            LOADED_COLS = atoi(word);
                            wordCounter++;
                            memset(word, 0, sizeof(word));
                            wordNumChar = -1;
                        }
                        else
                        {
                            LOADED_ROWS = atoi(word);
                            sizeOfLoadedWord = (LOADED_ROWS * LOADED_COLS);
                        }
                    }
                    else
                    {
                        word[wordNumChar] = save[i];
                    }
                    wordNumChar++;
                }
                loadedWorld = malloc(sizeof(int) * sizeOfLoadedWord);
            }
            // reading the map and storing it in an array
            else
            {
                for (int i = 0; i < strlen(save); i++)
                {
                    if (save[i] == '0' || save[i] == '1')
                    {
                        //convertion of char to int
                        *(loadedWorld + cellsPointerId) = save[i] - '0';
                        cellsPointerId++;
                    }
                }
            }
            lineCounter++;
        }
    }

    fclose(file);

    return loadedWorld;
}

// load world from a file to Cells structure pointer array
int loadWorldFromFileToCells(int *world)
{
    if (world == NULL)
    {
        printf("\nSorry, could not load the world :(\n");
        return 1;
    }

    int cols = 0; // Xs
    int rows = 0; //Ys
    int pointerID = 0;

    // printf("sizeof the wolrd: %d\n", numberOfCells(LOADED_COLS, LOADED_ROWS));
    for (int i = 0; i < sizeOfLoadedWord; i++)
    {
        (cells + i)->alive = *(world + i);
    }
    return 0;
}
