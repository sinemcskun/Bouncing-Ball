#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0x00000000
#define COLOR_BACKGROUND 0x382876
#define COLOR_FOREGROUND 0x667628
#define GRAVITY 0.2

struct Circle {
    double x;
    double y;
    double radius;
    double v_x, v_y;
};

void FillCircle(struct Circle circle, SDL_Surface *surface) {

    double low_x = circle.x - circle.radius;
    double low_y = circle.y - circle.radius;
    double high_x = circle.x + circle.radius;
    double high_y = circle.y + circle.radius;

    if (circle.radius > 0 && circle.radius < WIDTH) {
        if (circle.radius < HEIGHT) {
             for (double i = low_x; i < high_x; i++) {
                 for (double j = low_y; j < high_y; j++) {
                     if (((circle.x - i) * (circle.x - i)) + ((circle.y - j) * (circle.y - j)) < circle.radius * circle.radius) {
                         SDL_Rect pixel = (SDL_Rect){i, j, 1,1};
                         SDL_FillRect(surface, &pixel, COLOR_WHITE);
                     }
                 }
             }
        }
    }
}

void moveCircle(struct Circle *circle) {
    circle->x += circle->v_x;
    circle->y += circle->v_y;
    circle->v_y += GRAVITY;

    //ball exiting screen control
    if (circle->y + circle->radius > HEIGHT) {
        circle->v_y = -circle->v_y;
    }
    if (circle->x + circle->radius > WIDTH) {
        circle->v_x = -circle->v_x;
    }
    if (circle->y - circle->radius < 0) {
        circle->v_y = -circle->v_y;
    }
    if (circle->x - circle->radius < 0) {
        circle->v_x = -circle->v_x;
    }

}

int main(){

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Bouncing Ball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_BORDERLESS);
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    struct Circle circle = {200, 200, 100, 5, 0};
    SDL_Rect eraser = (SDL_Rect){0, 0, WIDTH, HEIGHT};
    SDL_Event e;
    int simulation_running = 1;
    while (simulation_running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                simulation_running = 0;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    simulation_running = 0;
                }
            }
        }
        SDL_FillRect(surface, &eraser, COLOR_BACKGROUND);
        FillCircle(circle, surface);
        moveCircle(&circle);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(20);
    }


}
