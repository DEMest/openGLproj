#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <math.h>
#include "display.h"
#include "controls.h"


void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Настройка ортографической проекции
    float aspect = (float)w / (float)h;
    glOrtho(-10.0 * aspect, 10.0 * aspect, -10.0, 10.0, -130.0, 130.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
    moveCamera();
    updateRotation();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    parseConfig("config.txt");
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("OpenGL Cube and Sphere");

    init();

    glutTimerFunc(0, timer, 0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();

    return 0;
}
