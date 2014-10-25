#include <cstdio>
#include <GL/glew.h>
#include "constants.h"
#include "window.h"


void wlWindow::init() {
    if(SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        SDL_Quit();
    }

    window = SDL_CreateWindow(
        WINDOW_TITLE,
        0, 0,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL
    );
    if(window == nullptr) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
    }

    context = SDL_GL_CreateContext(window);
    if(context == nullptr) {
        printf("SDL_GL_CreateContext Error: %s\n", SDL_GetError());
        SDL_Quit();
    }

    glewInit();

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GL_SetSwapInterval(1);
}


void wlWindow::deinit() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
}
