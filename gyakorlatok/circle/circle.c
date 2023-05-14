#include "circle.h"
#include <SDL2/SDL.h>

#include <math.h>

void set_circle_data(Circle* circle, double x, double y, double radius, Color color)
{
	circle->x = x;
	circle->y = y;
	if (radius > 0.0) {
		circle->radius = radius;
	} else {
		circle->radius = NAN;
	}
	circle->color = color;
}

double calc_circle_area(const Circle* circle)
{
	double area = circle->radius * circle->radius * M_PI;
	return area;
}

void approximate_circle_with_lines(SDL_Renderer* renderer, const Circle* circle)
{
	const int N = 1000;

	float x0 = 0;
	float y0 = circle->radius;

	SDL_SetRenderDrawColor(renderer, circle->color.r, circle->color.g, circle->color.b, SDL_ALPHA_OPAQUE);

	int x = circle->radius - 1;
	int y = 0;
	int tx = 1;
	int ty = 1;
	int error = tx - (2 * circle->radius);

	while (x >= y)
	{
		SDL_RenderDrawPoint(renderer, circle->x + x, circle->y - y);
		SDL_RenderDrawPoint(renderer, circle->x + x, circle->y + y);
		SDL_RenderDrawPoint(renderer, circle->x - x, circle->y - y);
		SDL_RenderDrawPoint(renderer, circle->x - x, circle->y + y);
		SDL_RenderDrawPoint(renderer, circle->x + y, circle->y - x);
		SDL_RenderDrawPoint(renderer, circle->x + y, circle->y + x);
		SDL_RenderDrawPoint(renderer, circle->x - y, circle->y - x);
		SDL_RenderDrawPoint(renderer, circle->x - y, circle->y + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - (2 * circle->radius));
		}
	}

	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	const int plus_sign_size = 3;
	if (is_inside(circle, mouseX, mouseY)) 
	{
		SDL_RenderDrawLine(renderer, 
			circle->x - plus_sign_size,
			circle->y - plus_sign_size,
			circle->x + plus_sign_size,
			circle->y + plus_sign_size);
		SDL_RenderDrawLine(renderer, 
			circle->x - plus_sign_size,
			circle->y + plus_sign_size,
			circle->x + plus_sign_size,
			circle->y - plus_sign_size);	
	}
}

bool is_inside(const Circle* circle, int x, int y)
{
	int dx = circle->x - x;
	int dy = circle->y - y;
	return (dx * dx + dy * dy) <= (circle->radius * circle->radius);
}