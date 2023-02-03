#include "../libGLTools/include/GLTools.h"
#include <GLUT/GLUT.h>

const GLfloat GL_PI = 3.1415f;

GLboolean increaseZ = true;
GLfloat bottomZ = -100.f;
GLfloat bottomAngle = 0;
GLuint pointsSize = 300;

GLfloat radius = 50.0f;

void setup_spiralColor() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 1.0, 0.0);
}


void spiralLineDemo(int idx) {
    
    GLfloat x, y, z, angle;
    GLuint pid = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    glRotated(45, 1.0, 0.0, 0.0);
    glRotated(45, 0.0, 1.0, 0.0);
    
    glBegin(GL_LINES);
    
    glColor3f(0.6, 0.3, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(200, 0, 0);
    
    glColor3f(0.3, 0.6, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 400, 0);
    
    glColor3f(0.0, 0.3, 0.6);
    glVertex3f(0, 0, -200);
    glVertex3f(0, 0, 200);
    
    glEnd();
    
    z = bottomZ;
    for (angle = bottomAngle; pid < pointsSize; angle += 0.1f, pid++) {
        GLfloat greenoffset = 1.0 * (pointsSize - pid) / pointsSize;
        GLfloat redoffset = 1.0 - greenoffset;
        x = log2(pid * radius) * sin(angle);
        y = log2(pid * radius) * cos(angle);
        z += 0.5f;
        
        
        
        glColor3f(greenoffset, redoffset, 0.0);
        
        if (pid < pointsSize / 2) {
            glPointSize((GLfloat)(pid + 1) * 0.1);
        } else {
            glPointSize((GLfloat)(pointsSize - pid + 1) * 0.1);
        }
        
        
        
        glBegin(GL_POINTS);
        glVertex3f(x, y, z);
        glEnd();
    }
    
    
    
    glPopMatrix();
    glutSwapBuffers();
    
    
    if (increaseZ && bottomZ + pointsSize * .5f > 100.0) {
        increaseZ = false;
    } else if (!increaseZ && bottomZ - .5f < -100.f) {
        increaseZ = true;
    }
    
    if (increaseZ) {
        bottomZ += .5f;
        bottomAngle += 0.1f;
    } else {
        bottomZ -= .5f;
        bottomAngle -= 0.1f;
    }
    glutTimerFunc(10, spiralLineDemo, 0);
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
}

void spiralDemoTest() {
    glutDisplayFunc(renderScene);
    glutTimerFunc(10, spiralLineDemo, 0);
    setup_spiralColor();
}
