#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(){
    srand(time(NULL));
    if ( SDL_Init ( SDL_INIT_VIDEO ) != 0 ) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n",
                SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if(0 != SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &window,
                                        &renderer))
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    int x = 2500;
    int y = 400;
    SDL_SetWindowPosition(window, x, y);
    SDL_SetWindowTitle(window, "helloSDL");
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderPresent(renderer);
    int continuer = 1;
    SDL_Event event;
    int i = 1;
    while(continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                i = rand() % 8 +1;
                char chaine[10];
                sprintf(chaine, "fleur%da.bmp", i);
                SDL_Surface *surface = SDL_LoadBMP(chaine);
                if (surface == NULL) {
                    fprintf(stderr, "Erreur de chargement du fichier : %s ", SDL_GetError());
                    return 1;
                }
                SDL_SetColorKey ( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0, 0));
                SDL_Texture *fleur = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_Rect rect_fleur;
                rect_fleur.x = event.button.x - 25;
                rect_fleur.y = event.button.y - 25;
                rect_fleur.w = 50;
                rect_fleur.h = 50;
                SDL_SetRenderTarget(renderer, fleur);
                SDL_RenderCopy(renderer, fleur, NULL, &rect_fleur);
                SDL_RenderPresent(renderer);
                SDL_DestroyTexture ( fleur );
                break;

            default:
                break;
        }
    }
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit ();
    printf("Quit\n");
    return EXIT_SUCCESS;
}