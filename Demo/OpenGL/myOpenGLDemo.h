
#include "../libGLTools/include/GLTools.h"
#include <GLUT/GLUT.h>
#include <vector>
#include <utility>
#include "spiralLine.h"
#include "dotFire.h"
#include "Atom.h"


GLuint blockSize = 4;
GLfloat xstep[] = {1.0f, -1.0f, 1.0f, -1.0f};
GLfloat ystep[] = {1.0f, -1.0f, -1.0f, 1.0f};
GLfloat rsize[] = {25.f, 50.f, 30.f, 70.f};
unsigned int speed[] = {50, 10, 80, 100};
std::vector<std::pair<GLfloat, GLfloat>> points = {{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}};
std::vector<std::vector<GLfloat>> colors = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.4, 0.5, 0.1}, {0.0, 0.0, 0.0}};

GLfloat windowWidth;
GLfloat windowHeight;

GLfloat x_1 = 0.0f;
GLfloat y_1 = 0.0f;

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (int i = 0; i < blockSize; i++) {
        glColor3f(colors[i][0], colors[i][1], colors[i][2]);
        GLfloat x = points[i].first;
        GLfloat y = points[i].second;
        GLfloat size = rsize[i];
        glRectf(x, y, x + size, y - size);
    }
    
//    glFlush();
    glutSwapBuffers();
}

void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}


void ChangeSize(GLsizei w, GLsizei h) {
    if (h == 0) h = 1;
    
    windowWidth = w;
    windowHeight = h;
    
    printf("glViewport is %d * %d", w, h);
    
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat halfw = (GLfloat)w / 2.0;
    GLfloat halfh = (GLfloat)h / 2.0;

    glOrtho(-halfw, halfw, -halfh, halfh, 100, -100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void TimerFunction(int idx) {
    GLfloat size = rsize[idx];
    GLfloat left = -windowWidth / 2.0;
    GLfloat right = windowWidth / 2.0 - size;
    GLfloat top = windowHeight / 2.0;
    GLfloat bottom = -windowHeight / 2.0 + size;
    GLfloat x = points[idx].first;
    GLfloat y = points[idx].second;
    
    
    if (x > right || x < left) xstep[idx] = -xstep[idx];
    if (y > top || y < bottom) ystep[idx] = -ystep[idx];
    
    x += xstep[idx];
    y += ystep[idx];
    
    
    if (x > windowWidth - size + xstep[idx])
        x = windowWidth - size - 1;
    else if (x < -windowWidth - xstep[idx])
        x = -windowWidth - xstep[idx];
    
    if (y > windowHeight + ystep[idx])
        y = windowHeight - 1;
    else if (y < -windowHeight + size - ystep[idx])
        y = -windowHeight + size - 1;
    
    points[idx] = std::make_pair(x, y);
    
    glutPostRedisplay();
    glutTimerFunc(speed[idx], TimerFunction, idx);
}



void translate() {
    
    /***\
        y = z sin(0) + y cos(0)
        z = z cos(0) - y sin(0)
     ***/
    
}
