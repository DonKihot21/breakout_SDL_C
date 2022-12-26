#include <SDL.h>
#include "texture_manager.c"

int move_board(SDL_Renderer *renderer,int WIDTH, int HEIGHT,SDL_Rect control_rect);
void draw_board(SDL_Renderer *renderer,SDL_Rect ball_rect);
SDL_Rect draw_control(SDL_Renderer *renderer,int xpos,int ypos);
SDL_Rect draw_ball(SDL_Renderer *renderer,int x_pos, int y_pos);
void populate_board(int width, int height);

int cx = 230;
int cy = 250;
int cvx = 10;
int cvy = 10;

int xpos = 300;
int ypos = 300;

typedef struct
{
    int xPos;
    int yPos;
    int width;
    int height;
    int hit;
}Piece;

Piece board[6][6] = {0};
int move_board(SDL_Renderer *renderer,int WIDTH, int HEIGHT,SDL_Rect control_rect)
{
            SDL_Rect ball_rect = draw_ball(renderer,cx,cy);
            draw_board(renderer,ball_rect);
            if(cx + cvx == WIDTH)
            {
                cvx = -10;
            }
            else if(cx + cvx == 0)
            {
                cvx = 10;
            }
            if(cy + cvy == HEIGHT)
            {
                return 1;
            }
            else if(SDL_HasIntersection(&control_rect,&ball_rect))
            {
                cvy = -10;
            }
            else if(cy + cvy == 0)
            {
                cvy = 10;
            }
            cx += cvx;
            cy += cvy;
        
        return 0;
}
void draw_board(SDL_Renderer *renderer,SDL_Rect ball_rect)
{
    SDL_Texture *piece_texture = LoadTexture("C:\\Users\\Retard\\Desktop\\breakout\\assets\\piece.png",renderer);
    SDL_RenderClear(renderer);
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j< 6;j++)
        {
            if(!board[i][j].hit)
            {
                SDL_Rect dest;
                dest.w = board[i][j].width;
                dest.h = board[i][j].height;
                dest.x = board[i][j].xPos;
                dest.y = board[i][j].yPos;
                if(SDL_HasIntersection(&dest,&ball_rect))
                {
                    cvy = 10;
                    board[i][j].hit = 1;
                    return;
                }
                SDL_RenderCopy(renderer,piece_texture,NULL,&dest);
            }
            else
            {

            }  
        }
    }
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(piece_texture);
}

SDL_Rect draw_control(SDL_Renderer *renderer,int xpos,int ypos)
{
    SDL_Texture *texture = LoadTexture("C:\\Users\\Retard\\Desktop\\breakout\\assets\\piece.png",renderer);
    SDL_Rect dest;
    dest.x = xpos;
    dest.y = ypos;
    dest.w = 150;
    dest.h = 50;
    SDL_RenderCopy(renderer,texture,NULL,&dest);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
    return dest;
}

SDL_Rect draw_ball(SDL_Renderer *renderer,int x_pos, int y_pos)
{
    SDL_Rect dest;
    dest.w = 30;
    dest.h = 30;
    dest.x = x_pos;
    dest.y = y_pos;

    SDL_Texture *circle = LoadTexture("C:\\Users\\Retard\\Desktop\\breakout\\assets\\circle.png",renderer);
    
    SDL_RenderCopy(renderer,circle,NULL,&dest);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(circle);
    return dest;
}

void populate_board(int width, int height)
{
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            board[i][j].xPos = i*(width / 6);
            board[i][j].yPos = j*(height / 12);
            board[i][j].width = width / 6;
            board[i][j].height = height / 12;
            board[i][j].hit = 0;
        }
    }
}