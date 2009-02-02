#include <GL/gl.h>
#include <GL/glut.h>

int
main (int argc, char *argv[])
{
    int window;

    glutInit(&argc, argv);
    window = glutCreateWindow("LOL");
    glutMainLoop();

    return 1;
}

