#include <cstdio>
#include <cstring>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "shader.h"
#include "window.h"
#include "mesh.h"
using namespace std;

int main() {
    wlWindow window;
    window.init();

    wlShader shader("terrain.vert", "terrain.frag");
    wlVertex* data = (wlVertex*)malloc(sizeof(wlVertex)*3);
    data[0] = { 0.0f, 1.0f, 0.0f};
    data[1] = {-1.0f,-1.0f, 0.0f};
    data[2] = { 1.0f,-1.0f, 0.0f};
    wlMesh mesh = wlMesh(data, 3, &shader);

    SDL_Event e;
    for(bool quit=false; quit == false; ) {
        mesh.render();
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
