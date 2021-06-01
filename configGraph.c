/*
* module contains code for config window that allow user entering
* their own pattern and size of the world
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

// initilizing window
int initConfigWindow(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
            fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
            return 1;
    }else{
        atexit(SDL_Quit);

        gWindow = SDL_CreateWindow("Game Of Life - Configuration",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    WINDOW_WIDTH,
                                    WINDOW_HEIGHT,
                                    SDL_WINDOW_OPENGL);

        if(gWindow == NULL){
            fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
            atexit(SDL_Quit);
            return 1;
        }
    }
    
    return 0;
}


//initilizing renderer for config Window
int initConfigRenderer(){
    gRenderer = SDL_CreateRenderer(
        gWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if(gRenderer == NULL){
        fprintf(stderr, "SDL_CreateRenderer: %s", SDL_GetError());
        SDL_DestroyWindow(gWindow);
        atexit(SDL_Quit);
        return 1;
    }
    
    return 0;
}

// enable entering users patterns for the cells
int textInputForGrid(){
    bool quit = false;
    SDL_Event event;    //event handler
    SDL_Color textColor = {0,0,0,255};

    //the current input text
    char inputtext = "something lol";
    return 0;
}

int textInputForGens(){
    return 0;
}

// accept the user made configuration and start the game
// in seperate window
int startButton(){
    return 0;
}