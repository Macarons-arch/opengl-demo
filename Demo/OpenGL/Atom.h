#include "../libGLTools/include/GLTools.h"
#include <GLUT/GLUT.h>


class Atom {
    
public:
    
    
    
    static void ChangeSize(GLsizei w, GLsizei h) {
        if (h == 0) h = 1;
        
        glViewport(0, 0, w, h);
        GLfloat fAspect = (GLfloat)w / (GLfloat)h;
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        gluPerspective(45.0f, fAspect, 1.0, 425.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    
    static void drawSun() {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, -300.0f);
        glColor3ub(255, 255, 0);
        glDisable(GL_LIGHTING);
        glutSolidSphere(15.0f, 15, 15);
//        glEnable(GL_LIGHTING);
        
        GLfloat lightPos[] = {0.0f, 0.0f, -300.0f};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        
        glPopMatrix();
    }
    
    static void drawEarth(GLfloat fEarthRot) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, -300.0f);
        // earth
        glColor3ub(0, 0, 255);
        glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);
        glTranslatef(105.f, 0.0f, 0.0f);
        glutSolidSphere(15.f, 15, 15);
        glPopMatrix();
    }
    
    static void drawMoon(GLfloat fEarthRot, GLfloat fMoonRot) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, -300.0f);
        
        glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);
        glTranslatef(105.f, 0.0f, 0.0f);
        
        glColor3ub(200, 200, 200);
        glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f);
        glTranslatef(30.f, 0.f, 0.f);
        
        glutSolidSphere(6.0, 15, 15);
        glPopMatrix();
    }
    
    static void RenderScene(int value) {
        
        static GLfloat fMoonRot = 0.0f;
        static GLfloat fEarthRot = 0.0f;
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glMatrixMode(GL_MODELVIEW);
        
        if (fEarthRot < 180) {
            if (fMoonRot < 180) {
                // sun --> earth --> moon
                drawMoon(fEarthRot, fMoonRot);
                drawEarth(fEarthRot);
                drawSun();
            } else {
                // sun --> moon --> earth
                drawEarth(fEarthRot);
                drawMoon(fEarthRot, fMoonRot);
                drawSun();
            }
        } else {
            if (fMoonRot < 180) {
                // earth --> moon --> sun
                drawSun();
                drawMoon(fEarthRot, fMoonRot);
                drawEarth(fEarthRot);
            } else {
                // moon --> earth --> sun
                drawSun();
                drawEarth(fEarthRot);
                drawMoon(fEarthRot, fMoonRot);
            }
        }
        
        fMoonRot += 1.5f;
        while(fMoonRot > 360.f) {
            fMoonRot -= 360.f;
        }
        fEarthRot += 0.5f;
        while (fEarthRot > 360.f) {
            fEarthRot -= 360.f;
        }
        glutSwapBuffers();
        
        glutTimerFunc(5, RenderScene, 0);
    }
    
    static void renderScene() {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0, 0, 0, 1.0);
    }
    
    static void test() {
        
        glutDisplayFunc(renderScene);
        glutTimerFunc(5, RenderScene, 0);
    }
    
    
};
