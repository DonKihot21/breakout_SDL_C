#include <SDL.h>
#include <SDL2/SDL_image.h>

static SDL_Texture* LoadTexture(char *filename,SDL_Renderer *renderer)
{
    SDL_Surface *temp_surface = IMG_Load(filename);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,temp_surface);
    SDL_FreeSurface(temp_surface);
    return texture;
}