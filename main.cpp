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
#include "camera.h"
using namespace std;

wlVertex* create_terrain(int width, int height, size_t* count) {
    const int V = 6;
    int w = width - 1;
    int h = height - 1;
    int wmid = (w / 2),
        hmid = (h / 2);

    *count = V * (w) * (h);
    wlVertex* data = (wlVertex*)malloc(sizeof(wlVertex) * (*count));

    for (int z = 0; z < h; ++z) {
        for (int x = 0; x < w; ++x) {
            int i = V * (z * w + x);
            float fx = x - wmid,
                  fz = z - hmid;
            data[  i] = {fx,   0.0f, fz,   1.0f, 0.0f, 0.0f};
            data[i+1] = {fx,   0.0f, fz-1, 0.0f, 1.0f, 0.0f};
            data[i+2] = {fx+1, 0.0f, fz,   0.0f, 0.0f, 1.0f};
            data[i+3] = {fx+1, 0.0f, fz,   1.0f, 0.0f, 0.0f};
            data[i+4] = {fx,   0.0f, fz-1, 0.0f, 1.0f, 0.0f};
            data[i+5] = {fx+1, 0.0f, fz-1, 0.0f, 0.0f, 1.0f};
        }
    }
    return data;
}

int main() {
    bool keys[6] = {false, false, false, false, false, false};
    wlWindow window;
    window.init();

    wlShader shader("terrain.vert", "terrain.frag");

    size_t count;
    wlVertex* data = create_terrain(128, 128, &count);
    printf("Vertices: %zu\n", count);
    wlMesh mesh = wlMesh(data, count, &shader);

    wlRenderer renderer = wlRenderer(&shader);
    // set camera
    renderer.camera.move(0.0f, 1.0f, -2.0f);

    GLfloat* proj = perspective_matrix(
        0.7853981633974483,
        (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT,
        0.5, 1000.0
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
    float speed = 0.05f;
    for(bool quit=false; quit == false; ) {
        if(keys[0]) {
            renderer.camera.move(0.0, 0.0, speed);
        }
        if(keys[1]) {
            renderer.camera.move(0.0, 0.0, -speed);
        }
        if(keys[2]) {
            renderer.camera.move(-speed, 0.0, 0.0);
        }
        if(keys[3]) {
            renderer.camera.move(+speed, 0.0, 0.0);
        }
        if(keys[4]) {
            renderer.camera.move(0.0, +speed, 0.0);
        }
        if(keys[5]) {
            renderer.camera.move(0.0, -speed, 0.0);
        }
        renderer.render();
        SDL_GL_SwapWindow(window.window);

        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
            if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_w:
                        keys[0] = true;
                        break;
                    case SDLK_s:
                        keys[1] = true;
                        break;
                    case SDLK_a:
                        keys[2] = true;
                        break;
                    case SDLK_d:
                        keys[3] = true;
                        break;
                    case SDLK_LSHIFT:
                        keys[4] = true;
                        break;
                    case SDLK_LCTRL:
                        keys[5] = true;
                        break;
                }
            }
            if(e.type == SDL_KEYUP) {
                switch(e.key.keysym.sym) {
                    case SDLK_w:
                        keys[0] = false;
                        break;
                    case SDLK_s:
                        keys[1] = false;
                        break;
                    case SDLK_a:
                        keys[2] = false;
                        break;
                    case SDLK_d:
                        keys[3] = false;
                        break;
                    case SDLK_LSHIFT:
                        keys[4] = false;
                        break;
                    case SDLK_LCTRL:
                        keys[5] = false;
                        break;
                }
            }
        }
    }

    window.deinit();
    return 0;
}
