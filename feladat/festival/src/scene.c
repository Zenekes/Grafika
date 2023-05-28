#include "scene.h"
#include <math.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    scene->wheel_rotation = 0.0;
    scene->forgo_rotation = 0.0;
    scene->cube_rotation = 0.0;
    scene->seats_rotation = 0.0;

    load_model(&(scene->cube), "assets/models/cube.obj");
    scene->texture_id = load_texture("assets/textures/cube.png");
    scene->texture_id_2 = load_texture("assets/textures/cube2.png");
    load_model(&(scene->wheel), "assets/models/wheel.obj");
    load_model(&(scene->stage), "assets/models/stage.obj");
    load_model(&(scene->forgo), "assets/models/forgo.obj");
    load_model(&(scene->seat), "assets/models/seat.obj");
    load_model(&(scene->ferris), "assets/models/ferris.obj");

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
    scene->light_intensity = 1.0f;

    scene->wheel_position.x = 4.0;
    scene->wheel_position.y = 6.0;
    scene->wheel_position.z = 2.0;
}


void set_lighting(const Scene* scene)
{
    float intensity = scene->light_intensity;
    float ambient_light[] = { 0.4f * intensity, 0.4f * intensity, 0.4f * intensity, 1.0f };
    float diffuse_light[] = { 1.0f * intensity, 1.0f * intensity, 1.0f * intensity, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 0.0f, 1.0f };


    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}


void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene, double time)
{
    scene->wheel_rotation = fmod(scene->wheel_rotation + 10.0 * time, 360.0);
    scene->forgo_rotation = fmod(scene->forgo_rotation + 20.0 * time, 360.0);
    scene->cube_rotation = fmod(scene->cube_rotation + 10.0 * time, 360.0);
    scene->ferris_rotation = fmod(scene->ferris_rotation + 10.0 * time, 360.0);
}

void render_scene(const Scene* scene)
{
    
    set_material(&(scene->material));
    set_lighting(scene);
    draw_origin();
    render_floor();

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(1, 3, 0);
    glRotatef(90, 90, 0, 1);
    draw_model(&(scene->stage));
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glScalef(0.3f, 0.3f, 0.3f);
    glTranslatef(-5, -4, 0);
    glRotatef(scene->forgo_rotation, 0, 0, 1);
    glRotatef(90, 90, 0, 1);
    draw_model(&(scene->forgo));
    glPopMatrix();

glPushMatrix();
glTranslatef(4, 6, 3);
glRotatef(90, 1, 0, 0);
glScalef(2.0f, 2.0f, 2.0f);
glRotatef(scene->wheel_rotation, 1, 0, 0);
draw_model(&(scene->wheel));
glPopMatrix();

glPushMatrix();
glTranslatef(4, 6, 3);
glScalef(2.0f, 2.0f, 2.0f);
glRotatef(90, 1, 0, 0);
glRotatef(scene->wheel_rotation, 1, 0, 0); // Rotate around the wheel's center on the x-axis
glPushMatrix();
glTranslatef(0, 1, 0); // Translate the seats down by 2 units
glRotatef(-scene->wheel_rotation, 1, 0, 0); // Counter-rotate the seats to maintain their original orientation
glPushMatrix();
glTranslatef(0, 0, 0);
draw_model(&(scene->seat)); // Call the function to draw the seats
glPopMatrix();
glPopMatrix();
glPopMatrix();


    glPushMatrix();
    glRotatef(scene->cube_rotation, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    draw_model(&(scene->cube));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id_2);
    draw_model(&(scene->cube));
    glPopMatrix();

}

void render_floor()
{
    
    float size = 50.0f;
    glPushMatrix(); 
    glDisable(GL_LIGHTING); // disable lighting
    glRotatef(-90, 1, 0, 0);
 
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);

    glVertex3f(-size, 0, -size);
    glVertex3f(size, 0, -size);
    glVertex3f(size, 0, size);
    glVertex3f(-size, 0, size);

    glEnd();
    glEnable(GL_LIGHTING); // re-enable lighting
    glPopMatrix();

}


void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();

}
