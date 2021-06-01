/*
 * main file for Game Of Life
 */

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "graph.h"
#include "logic.h"


int main(int argc, char **argv)
{
    int delay = 300;
    bool quit = false;
    SDL_Event event;
    int num_of_gens = 0;

    //string with name of the world to read data from
    char *worldFile;
    //string with name of file that will store final state of the world
    char *saveFilename;


    if(argc >= 2){
        worldFile = argv[1];
    }else{
        worldFile = DEFAULT_WORLD;
    }
    
    if(argc >= 3 ){
        saveFilename = argv[2];
    }else{
        saveFilename = "saved_worlds/default_saved.txt";
    }

    FILE *openedRead = fopen(worldFile, "r");
    int *world;
    // dataToFile("saved_worlds/test.txt");

    if (openedRead == NULL)
    {
        initCellsArray(DEFAULT_COLS, DEFAULT_ROWS);
        initialPattern(cells, cells_num);
    }
    else
    {
        world = readData(openedRead);
        initCellsArray(LOADED_COLS, LOADED_ROWS);
        loadWorldFromFileToCells(world);
    }
    initWindowAndRenderer();

    // game loop - if click top right X the game terminates
    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        drawGrid();
        nextGen();
        num_of_gens++;

        SDL_Delay(delay);
    }

    dataToFile(saveFilename);
    printf("Number of generations computed: %d", num_of_gens);
    close_SDL();
    free(cells);
    cells = NULL;

    return 0;
}