#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Meteor Runner");

    init();

    

    glutMainLoop();
    return 0;
}