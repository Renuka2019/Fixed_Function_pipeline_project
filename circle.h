#pragma once
#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h>

#define _USE_MATH_DEFINES
#include<cmath>



void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)//radius_x,radius_y,certre_position_x,centre_position_y
{

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(cx, cy, 0.0f);

    for (int i = 0; i <= 100; i++)

    {
        float angle = 2.0f * 3.1416f * i / 100;

        float x = rx * cosf(angle);
        float y = ry * sinf(angle);

        glVertex3f((x + cx), (y + cy), 0.0f);
    }
    glEnd();



}

void SolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks)
{
    double  alt = height / (double)(stacks + 1);
    double  angle = M_PI / (double)slices * 2.0f;
    double  slope = (height / base);
    double  sBase = base;
    double  sinNormal = (base / sqrt(height * height + base * base));
    double  cosNormal = (height / sqrt(height * height + base * base));

    double* vertices = NULL;
    int    i, j;

    /*
     * We need 'slices' points on a circle
     */
    vertices = (double*)calloc(sizeof(double), 2 * (slices + 1));

    for (j = 0; j < slices + 1; j++)
    {
        vertices[j * 2 + 0] = cos(angle * j);
        vertices[j * 2 + 1] = sin(angle * j);
    }

    /*
     * First the cone's bottom...
     */
    for (j = 0; j < slices; j++)
    {
        double scl = height / slope;

        glBegin(GL_TRIANGLES);
        glNormal3d(0.0, 0.0, -1.0);
        glVertex3d(vertices[(j + 0) * 2 + 0] * sBase, vertices[(j + 0) * 2 + 1] * sBase, 0);
        glVertex3d(vertices[(j + 1) * 2 + 0] * sBase, vertices[(j + 1) * 2 + 1] * sBase, 0);
        glVertex3d(0.0, 0.0, 0.0);
        glEnd();
    }

    /*
     * Then all the stacks between the bottom and the top
     */
    for (i = 0; i < stacks; i++)
    {
        double alt_a = i * alt, alt_b = (i + 1) * alt;
        double scl_a = (height - alt_a) / slope;
        double scl_b = (height - alt_b) / slope;

        for (j = 0; j < slices; j++)
        {
            glBegin(GL_TRIANGLES);
            glNormal3d(sinNormal * vertices[(j + 0) * 2 + 0], sinNormal * vertices[(j + 0) * 2 + 1], cosNormal);
            glVertex3d(vertices[(j + 0) * 2 + 0] * scl_a, vertices[(j + 0) * 2 + 1] * scl_a, alt_a);
            glNormal3d(sinNormal * vertices[(j + 1) * 2 + 0], sinNormal * vertices[(j + 1) * 2 + 1], cosNormal);
            glVertex3d(vertices[(j + 1) * 2 + 0] * scl_a, vertices[(j + 1) * 2 + 1] * scl_a, alt_a);
            glNormal3d(sinNormal * vertices[(j + 0) * 2 + 0], sinNormal * vertices[(j + 0) * 2 + 1], cosNormal);
            glVertex3d(vertices[(j + 0) * 2 + 0] * scl_b, vertices[(j + 0) * 2 + 1] * scl_b, alt_b);
            glEnd();

            glBegin(GL_TRIANGLES);
            glNormal3d(sinNormal * vertices[(j + 0) * 2 + 0], sinNormal * vertices[(j + 0) * 2 + 1], cosNormal);
            glVertex3d(vertices[(j + 0) * 2 + 0] * scl_b, vertices[(j + 0) * 2 + 1] * scl_b, alt_b);
            glNormal3d(sinNormal * vertices[(j + 1) * 2 + 0], sinNormal * vertices[(j + 1) * 2 + 1], cosNormal);
            glVertex3d(vertices[(j + 1) * 2 + 0] * scl_b, vertices[(j + 1) * 2 + 1] * scl_b, alt_b);
            glVertex3d(vertices[(j + 1) * 2 + 0] * scl_a, vertices[(j + 1) * 2 + 1] * scl_a, alt_a);
            glEnd();
        }
    }

    /*
     * Finally have the top part drawn...
     */
    for (j = 0; j < slices; j++)
    {
        double scl = alt / slope;

        glBegin(GL_TRIANGLES);
        glNormal3d(sinNormal * vertices[(j + 0) * 2 + 0], sinNormal * vertices[(j + 0) * 2 + 1], cosNormal);
        glVertex3d(vertices[(j + 0) * 2 + 0] * scl, vertices[(j + 0) * 2 + 1] * scl, height - alt);
        glNormal3d(sinNormal * vertices[(j + 1) * 2 + 0], sinNormal * vertices[(j + 1) * 2 + 1], cosNormal);
        glVertex3d(vertices[(j + 1) * 2 + 0] * scl, vertices[(j + 1) * 2 + 1] * scl, height - alt);
        glVertex3d(0, 0, height);
        glEnd();
    }
}







