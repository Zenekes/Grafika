#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model cube;
    Model wheel;
    Model stage;
    Model forgo;
    Model ferris;
    Model seat;
    float wheel_rotation;
    float forgo_rotation;
    float cube_rotation;
    float seats_rotation;
    float ferris_rotation;
    Material material;
    GLuint texture_id;
    GLuint texture_id_2;
    float light_intensity;
    vec3 wheel_position; 

} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(const Scene* scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);

void update_scene(Scene* scene, double time);
/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void render_floor();


#endif /* SCENE_H */
