#include <cstdio>
#include <cstring>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "constants.h"
#include "renderer.h"
#include "shader.h"
#include "window.h"
#include "mesh.h"
#include "utils.h"
using namespace std;

wlVertex* create_terrain() {
    wlVertex* data = (wlVertex*)malloc(sizeof(wlVertex)*3);
    data[0] = { 0.0f, 1.0f, 0.0f};
    data[1] = {-1.15f,-1.0f, 0.0f};
    data[2] = { 1.15f,-1.0f, 0.0f};
    return data;
}

int main() {
    wlWindow window;
    window.init();

    wlShader shader("terrain.vert", "terrain.frag");

    wlVertex* data = create_terrain();
    wlMesh mesh = wlMesh(data, 3, &shader);
    wlRenderer renderer = wlRenderer(&shader);

    GLfloat* proj = perspective_matrix(
        0.7853981633974483,
        (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT,
        0.5, 5.0
    );
    GLfloat view[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 2.0f, 1.0f,
    };
    renderer.add_mesh(&mesh);
    renderer.set_projection(proj);
    renderer.set_view(view);
    free(proj);

    SDL_Event e;
    for(bool quit=false; quit == false; ) {
        renderer.render();
        SDL_GL_SwapWindow(window.window);

        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    window.deinit();
    return 0;
}
