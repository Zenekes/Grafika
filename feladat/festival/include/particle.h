#ifndef H_PARTICLE
#define H_PARTICLE

struct Firework
{
    int x;
    int y;
    double lifetime;
    struct Firework* next;
    struct Firework* prev;
};

/**
 * Insert star after the given element.
 */
void insert_star(struct Firework* valami, struct Firework* firework);

/**
 * Remove the star from the list.
 */
void remove_star(struct Firework* firework);

#endif // H_STAR
