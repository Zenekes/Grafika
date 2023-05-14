#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

typedef struct Color {
  char r, g, b;
} Color;

const int MAX_RECT_COUNT = 1000;

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

  SDL_Rect rects[MAX_RECT_COUNT];
  Color colors[MAX_RECT_COUNT];
  int rect_count = 0;

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
  bool new_rect_created = false;

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
        printf("(%d,%d)\n", mouseX, mouseY);
        if (rect_count < MAX_RECT_COUNT && !new_rect_created) {
          SDL_Rect new_rect = { mouseX, mouseY, 0, 0 };
          rects[rect_count] = new_rect;
          
          Color color = { rand() % 255, rand() % 255, rand() % 255 };
          colors[rect_count] = color;

          rect_count++;

          new_rect_created = true;
        }
        break;
      case SDL_MOUSEMOTION:
        SDL_GetMouseState(&mouseX, &mouseY);
        if (new_rect_created) {
          //SDL_Rect *rect = rects + rect_count - 1; // kiszedem a címét pointerbe
          SDL_Rect *rect = &rects[rect_count - 1];
          rect->w = mouseX - rect->x;
          rect->h = mouseY - rect->y;
        }
        break;
      case SDL_MOUSEBUTTONUP:
        new_rect_created = false;
        break;
      case SDL_QUIT:
        need_run = false;
        break;
      }

      SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

      for (int i = 0; i < rect_count; i++)
      {
        const Color *color = &colors[i];       
        SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rects[i]);
      }

      SDL_RenderPresent(renderer);
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}