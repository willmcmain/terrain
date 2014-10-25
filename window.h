#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <SDL2/SDL.h>
class wlWindow {
    public:
        void init();
        void deinit();
        SDL_Window *  window;
    private:
        SDL_GLContext context;
};
#endif
