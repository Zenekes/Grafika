#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{   

    Model wheel;
    Model stage;
    Model forgo;
    Model rainbow;
    Model seat;
    Model stand;
    float wheel_rotation;
    float forgo_rotation;
    float cube_rotation;
    float seats_rotation;
    Material material;
    GLuint texture_rainbow;
    GLuint grass_texture;
    GLuint sky_texture;
    GLuint texture_id;
    GLuint texture_forgo;
    GLuint texture_wheel;
    GLuint texture_seat;
    GLuint help_image;
	bool display_help;
    float light_intensity;
    vec3 wheel_position; 
    vec3 laser_position;
    vec3 laser_direction;
    Color laser_color;

    
} Scene;


/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material, float alpha);

void update_scene(Scene* scene, double time);
/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

void help(GLuint Help_menu);

void render_floor(GLuint texture_name);

void draw_laser_beam();

void render_skybox(GLuint texture_name);

#endif /* SCENE_H */