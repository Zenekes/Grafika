#ifndef CIRCLE_H
#define CIRCLE_H

#include "color.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

/**
 * Data of a circle object in Descartes coordinate system
 */
typedef struct Circle
{
	double x;
	double y;
	double radius;
	Color color;
} Circle;

/**
 * Set the data of the circle
 */
void set_circle_data(Circle* circle, double x, double y, double radius, Color color);

/**
 * Calculate the area of the circle.
 */
double calc_circle_area(const Circle* circle);


/**
 * Approximate the circle using SDL's line drawing function.
 */
void approximate_circle_with_lines(SDL_Renderer* renderer, const Circle* circle);

/**
 * Determine if a point is inside a circle
 */
bool is_inside(const Circle* circle, int x, int y);

#endif // CIRCLE_H