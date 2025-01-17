#include <jni.h>
#include <string>
#include <unistd.h>
#include "../util/alog.h"
#include "SDL.h"
#include "SDL_image.h"
/* XPM */
static char * icon_xpm[] = {
        "32 23 3 1",
        "     c #FFFFFF",
        ".    c #000000",
        "+    c #FF0000",
        "                                ",
        "            ........            ",
        "          ..++++++++..          ",
        "         .++++++++++++.         ",
        "        .++++++++++++++.        ",
        "       .++++++++++++++++.       ",
        "      .++++++++++++++++++.      ",
        "      .+++....++++....+++.      ",
        "     .++++.. .++++.. .++++.     ",
        "     .++++....++++....++++.     ",
        "     .++++++++++++++++++++.     ",
        "     .++++++++++++++++++++.     ",
        "     .+++++++++..+++++++++.     ",
        "     .+++++++++..+++++++++.     ",
        "     .++++++++++++++++++++.     ",
        "      .++++++++++++++++++.      ",
        "      .++...++++++++...++.      ",
        "       .++............++.       ",
        "        .++..........++.        ",
        "         .+++......+++.         ",
        "          ..++++++++..          ",
        "            ........            ",
        "                                "};

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    int done;
    SDL_Event event;

    if (SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) < 0) {
        LOGE("SDL_CreateWindowAndRenderer() failed: %s", SDL_GetError());
        return(2);
    }

    surface = IMG_ReadXPMFromArray(icon_xpm);
    if (!surface){
        LOGE("surface = null ");
        return 0;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        LOGE("Couldn't load texture: %s", SDL_GetError());
        return(2);
    }
    SDL_SetWindowSize(window, 800, 480);
    done = 0;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                done = 1;
        }
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    SDL_DestroyTexture(texture);
    SDL_Quit();
    return(0);
}