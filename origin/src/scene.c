#include "scene.h"

#include <GL/gl.h>

void init_scene(Scene* scene)
{
}

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene)
{
    int i, k;
    draw_origin();
    
    glPushMatrix();
        for (k=0; k<8; ++k) {
            glPushMatrix();
        for (i=0; i<6; ++i) {
        glBegin(GL_TRIANGLES);

        glColor3f(1, 0, 0);
        glVertex3f(1, 0, 0);

        glColor3f(0, 1, 0);
        glVertex3f(0, 1, 0);

        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 1);

        glEnd();

        glTranslatef(0, 0, 0.2);
    }
    glPopMatrix();
    glTranslatef(1, 1, 0);
    }
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
