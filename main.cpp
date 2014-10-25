#include <cstdio>
#include <cstring>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "renderer.h"
#include "shader.h"
#include "window.h"
#include "mesh.h"
using namespace std;

wlVertex* create_terrain() {
    wlVertex* data = (wlVertex*)malloc(sizeof(wlVertex)*3);
    data[0] = { 0.0f, 1.0f, 0.0f};
    data[1] = {-1.0f,-1.0f, 0.0f};
    data[2] = { 1.0f,-1.0f, 0.0f};
    return data;
}

int main() {
    wlWindow window;
    window.init();

    wlShader shader("terrain.vert", "terrain.frag");

    wlVertex* data = create_terrain();
    wlMesh mesh = wlMesh(data, 3, &shader);
    wlRenderer renderer = wlRenderer(&shader);
    renderer.add_mesh(&mesh);

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
