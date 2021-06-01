/*
 *   functions related to graphical representation of Game Of Life
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "logic.h"

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

// initilizing game window and renderer
int initWindowAndRenderer(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    else
    {
        atexit(SDL_Quit);

        // setting up window
        gWindow = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

        if (gWindow == NULL)
        {
            fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
            atexit(SDL_Quit);
            return 1;
        }

        // setting up a renderer
        gRenderer = SDL_CreateRenderer(
            gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (gRenderer == NULL)
        {
            fprintf(stderr, "SDL_CreateRenderer: %s\n", SDL_GetError());
            SDL_DestroyWindow(gWindow);
            atexit(SDL_Quit);
            return 1;
        }
        return 0;
    }
}

int drawGrid()
{
    int rect_x_loc = 0; // rectangle x location
    int rect_y_loc = 0; // rectangle y location

    SDL_Rect cell_square = {
        rect_x_loc, rect_y_loc,
        CELL_SIZE, // width
        CELL_SIZE  // height
    };

    // background (blue)
    SDL_SetRenderDrawColor(gRenderer, 26, 31, 125, 255);
    SDL_RenderClear(gRenderer);

    // draw rectangle for each cell
    int cell_id = 0;
    for (int y = 0; y < SCREEN_HEIGHT;)
    {
        for (int x = 0; x < SCREEN_WIDTH;)
        {
            if ((cells + cell_id)->alive == 1)
            {
                // yellow
                SDL_SetRenderDrawColor(gRenderer, 255, 213, 0, 255);
            }
            else
            {
                // blue
                SDL_SetRenderDrawColor(gRenderer, 26, 31, 125, 255);
            }
            SDL_RenderFillRect(gRenderer, &cell_square);
            cell_square.x = x;
            cell_square.y = y;
            x += CELL_SIZE;
            cell_id++;
        }
        y += CELL_SIZE;
    }

    // draw lines to separates rectangles and show grid
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    for (int i = 0; i < SCREEN_HEIGHT;)
    {
        SDL_RenderDrawLine(gRenderer, 0, i, SCREEN_WIDTH, i);
        i += CELL_SIZE;
    }

    for (int i = 0; i < SCREEN_WIDTH;)
    {
        SDL_RenderDrawLine(gRenderer, i, 0, i, SCREEN_HEIGHT);
        i += CELL_SIZE;
    }
    SDL_RenderPresent(gRenderer);
    return 0;
}

void close_SDL(){
    //destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    //quit subsystems
    IMG_Quit();
    SDL_Quit();
}
