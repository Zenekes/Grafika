#include "scene.h"

#include <math.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <obj/load.h>
#include <obj/draw.h>

#include <GL/gl.h>

void init_scene(Scene* scene)
{
    scene->wheel_rotation = 0.0;
    scene->forgo_rotation = 0.0;
    scene->cube_rotation = 0.0;
    scene->seats_rotation = 0.0;

    scene->sky_texture = load_texture("assets/textures/sky.jpg");
    scene->grass_texture = load_texture("assets/textures/grass.png");
    scene->help_image = load_texture("assets/textures/help.png");
    load_model(&(scene->wheel), "assets/models/wheel.obj");
    scene->texture_wheel = load_texture("assets/textures/wheel.png");
    load_model(&(scene->stage), "assets/models/stage.obj");
    load_model(&(scene->forgo), "assets/models/forgo.obj");
    scene->texture_forgo = load_texture("assets/textures/forgo.png");
    load_model(&(scene->seat), "assets/models/seat.obj");
    scene->texture_seat = load_texture("assets/textures/seat.png");
    load_model(&(scene->stand), "assets/models/stand.obj");
    load_model(&(scene->rainbow), "assets/models/rainbow.obj");
    scene->texture_rainbow = load_texture("assets/textures/rainbow.png");

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 1.0;
    scene->light_intensity = 1.0f;

    scene->wheel_position.x = 4.0;
    scene->wheel_position.y = 6.0;
    scene->wheel_position.z = 1.0;

    scene->display_help = false;
}

void set_lighting(const Scene* scene)
{
    float intensity = scene->light_intensity;
    float ambient_light[] = { 0.4f * intensity, 0.4f * intensity, 0.4f * intensity, 1.0f };
    float diffuse_light[] = { 1.0f * intensity, 1.0f * intensity, 1.0f * intensity, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 0.0f };

    GLfloat laser_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat laser_direction[] = { 0.0f, -1.0f, 0.0f }; 

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT1, GL_POSITION, laser_position);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, laser_direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f); 
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0f); 
}


void set_material(const Material* material, float alpha)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue,
        alpha
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue,
        alpha
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue,
        alpha
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void help(GLuint Help_menu)
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, Help_menu);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}


void update_scene(Scene* scene, double time)
{
    scene->wheel_rotation = fmod(scene->wheel_rotation + 15.0 * time, 360.0);
    scene->forgo_rotation = fmod(scene->forgo_rotation + 20.0 * time, 360.0);
    scene->cube_rotation = fmod(scene->cube_rotation + 10.0 * time, 360.0);

}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material), 1.0f);
    set_lighting(scene);

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    render_floor(scene->grass_texture);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    render_skybox(scene->sky_texture);
    glPopMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    set_material(&(scene->material), 0.5f); 
    glPushMatrix();
    glTranslatef(15, 0, 3);
    glRotatef(90, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_rainbow);
    draw_model(&(scene->rainbow));
    glPopMatrix();
    set_material(&(scene->material), 1.0f);
    glDisable(GL_BLEND); 

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
    glTranslatef(3, 0, 0);
    glRotatef(90, 1, 0, 0);
    draw_model(&(scene->stage));
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);
    glTranslatef(17, -10, 0);
    glRotatef(scene->forgo_rotation, 0, 0, 1);
    glRotatef(90, 90, 0, 1);
    glBindTexture(GL_TEXTURE_2D, scene->texture_forgo);
    draw_model(&(scene->forgo));
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(4, 6, 3);
    glRotatef(90, 1, 0, 0);
    glScalef(2.0f, 2.0f, 2.0f);
    glRotatef(scene->wheel_rotation, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_seat);
    draw_model(&(scene->wheel));
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(4, 6, 3);
    glScalef(2.0f, 2.0f, 2.0f);
    glRotatef(90, 1, 0, 0);
    glRotatef(scene->wheel_rotation, 1, 0, 0); 
    glPushMatrix();
    glTranslatef(0, 1, 0); 
    glRotatef(-scene->wheel_rotation, 1, 0, 0); 
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_wheel);
    draw_model(&(scene->seat));
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(4, 6, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(2.0f, 2.0f, 2.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_wheel);
    draw_model(&(scene->stand));
    glPopMatrix();

    if (scene->display_help)
    {
        help(scene->help_image);
    }

    glDisable(GL_LIGHTING);
    glLineWidth(3.0f); 

    glPushMatrix();
    glTranslatef(scene->laser_position.x, scene->laser_position.y, scene->laser_position.z);
    draw_laser_beam();
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void render_floor(GLuint texture_name)
{
    float size = 50.0f;
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_name);
    glRotatef(-90, 1, 0, 0);

    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);

    glVertex3f(-size, 0, -size);
    glVertex3f(size, 0, -size);
    glVertex3f(size, 0, size);
    glVertex3f(-size, 0, size);

    glEnd();
    
    glPopMatrix();
}

void draw_laser_beam()
{
    glPushMatrix();
    glLineWidth(20.0f); 
    glColor3f(1.0f, 0.0f, 0.0f); 

    glBegin(GL_LINES);
    glVertex3f(1.0f, 1.0f, 0.0f); 
    glVertex3f(0.0f, 10.0f, 15.0f); 
    glEnd();
    glPopMatrix();
}

void render_skybox(GLuint texture_name) {
    glPushMatrix();
    glDepthMask(GL_FALSE);

    glBindTexture(GL_TEXTURE_2D, texture_name);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-50.0f, 50.0f, -50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(50.0f, 50.0f, -50.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(50.0f, -50.0f, 50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, 50.0f, -50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(50.0f, 50.0f, 50.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, -50.0f, 50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, -50.0f, 50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, 50.0f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, 50.0f, 50.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-50.0f, -50.0f, 50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-50.0f, 50.0f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, 50.0f, -50.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, 50.0f, -50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, 50.0f, -50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, 50.0f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, 50.0f, 50.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, -50.0f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, -50.0f, 50.0f);

    glEnd();

    glDepthMask(GL_TRUE);
    glPopMatrix();
}