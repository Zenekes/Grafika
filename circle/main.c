#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "circle.h"
#include "color.h"

const int MAX_CIRCLE_COUNT = 1000;

/**
 * SDL2 example
 */
int main(int argc, char* argv[])
{
  int error_code;
  SDL_Window *window;
  bool need_run;
  SDL_Event event;
  SDL_Renderer *renderer;
  int i;

  Circle circles[MAX_CIRCLE_COUNT];
  int circle_count = 0;

  srand(time(NULL));

  error_code = SDL_Init(SDL_INIT_EVERYTHING);
  if (error_code != 0) {
    printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
    return error_code;
  }

  window = SDL_CreateWindow(
    "Hello SDL!",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    800, 600, 0);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  int mouseX, mouseY;
  bool new_circle_created = false;

  Color background_color = { 0, 0, 0 };

  SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  need_run = true;
  while (need_run) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_KEYDOWN:
        case SDL_SCANCODE_Q:
        need_run = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        SDL_GetMouseState(&mouseX, &mouseY);
        if (circle_count < MAX_CIRCLE_COUNT && !new_circle_created) {
          Color color = { rand() % 255, rand() % 255, rand() % 255 };
          Circle new_circle = { mouseX, mouseY, 0, color };
          circles[circle_count++] = new_circle;
          
          new_circle_created = true;
        }
        break;
      case SDL_MOUSEMOTION:
        SDL_GetMouseState(&mouseX, &mouseY);
        if (new_circle_created) {
          Circle *circle = &circles[circle_count - 1];
          circle->radius = sqrt((mouseX - circle->x) * (mouseX - circle->x) + (mouseY - circle->y) * (mouseY - circle->y));
        }
        break;
      case SDL_MOUSEBUTTONUP:
        new_circle_created = false;
        break;
      case SDL_QUIT:
        need_run = false;
        break;
      }

      SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

      for (int i = 0; i < circle_count; i++)
      {
		    approximate_circle_with_lines(renderer, &circles[i]);
      }

      SDL_RenderPresent(renderer);
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}