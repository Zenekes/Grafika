#include "particle.h"

#define FIREWORK_LIFETIME 2.0


//draw majd a scene.c-ben

void update_stars(double elapsed_time)
{
    struct Star* star;
    struct Star* removable_star;

    star = stars.next;
    while (star->x != -1) {
        star->lifetime -= elapsed_time;
        if (star->lifetime < 0.0) {
            removable_star = star;
            star = star->prev;
            remove_star(removable_star);
            free(removable_star);
        }
        star = star->next;
    }
}

float calc_alpha_from_lifetime(double lifetime)
{
    return lifetime / STAR_LIFETIME;
}

void draw_stars()
{
    struct Star* star;
    float alpha;

    star = stars.next;
    while (star->x != -1) {
        glPushMatrix();
        glTranslatef(star->x, star->y, 0);
        alpha = calc_alpha_from_lifetime(star->lifetime);
        draw_star(50, alpha);
        glPopMatrix();
        star = star->next;
    }
}
