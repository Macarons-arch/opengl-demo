//
//  main.cpp
//  Demo
//
//  Created by 何志勇 on 2022/12/23.
//

#include <iostream>
#include "MyList/HYList.h"
#include "MYTree/HYTree.h"
#include "OpenGL/myOpenGLDemo.h"

using namespace std;

int main(int argc, char * argv[]) {
    
    
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("opengl demo");

    
    glutReshapeFunc(Atom::ChangeSize);
    
    
//    spiralDemoTest();
    Atom::test();
    
    
    glutMainLoop();
    
    return 0;
}
