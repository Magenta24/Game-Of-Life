#ifndef CONFIG_H
#define CONFIG_H
#include <stdio.h>

#define DEFAULT_WORLD "world_maps/default_world.txt"
#define CELL_SIZE 20
#define DEFAULT_COLS 40
#define DEFAULT_ROWS 40

// SCREEN PARAMETERS
extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;
// WORLD PARAMETERS
extern int MAX_X;
extern int MAX_Y;

// size of the world laoded from a file
extern int LOADED_COLS;
extern int LOADED_ROWS;

//number of cells in the grid
// extern int cells_num;

//functions prototypes
int numberOfCells(int cols, int rows);
int dataToFile(char *filename);
int * readData(FILE *file);
int loadWorldFromFileToCells(int *world);

#endif /* CONFIG_H */