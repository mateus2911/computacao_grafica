#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
    GLfloat x, y;
} Ponto2D; //Cria um tipo de variavel para os vertices do poligono


//Inicializa os posições iniciais dos vertices dos poligonos
#define NUM_VERTICES 3
Ponto2D poligono[NUM_VERTICES] = {
    { 0.0, 2.0},
    {-2.0, -1.0},
    { 2.0, -1.0}
};

//Define a posição de ancora do poligono
GLfloat anchorX = 0.0;
GLfloat anchorY = 2.0;

//Define as variveis globais de angulos e posições
GLfloat gPosX = 0.0;
GLfloat gPosY = 0.0;
GLfloat gAngle = 0.0;
GLfloat gScale = 1.0;

void desenhaPoligono() {
    int i;
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0); //Define a cor do poligono
    for (i = 0; i < NUM_VERTICES; i++) {
        glVertex2f(poligono[i].x, poligono[i].y);
    } //Cria o poligono com as posições dos vertices
    glEnd();

    //Cria um ponto azul onde fica a ancora do poligono
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(anchorX, anchorY);
    glEnd();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
}

void funcaoDeDesenho() {
    glClear(GL_COLOR_BUFFER_BIT);// Limpa a tela
    glLoadIdentity();//Reinicia todas as transformações

    //chama as transformações do poligono na ordem inverssa
    glTranslatef(gPosX, gPosY, 0.0);
    glTranslatef(anchorX, anchorY, 0.0);
    glRotatef(gAngle, 0.0, 0.0, 1.0);
    glScalef(gScale, gScale, 1.0);
    glTranslatef(-anchorX, -anchorY, 0.0);

    desenhaPoligono(); // Redesenha o poligono
    glutSwapBuffers();
}

void gerenciaTeclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'r':
            gAngle += 5.0f;
            break;
        case '+':
            gScale += 0.1f;
            break;
        case '-':
            gScale -= 0.1f;
            break;
    }
    glutPostRedisplay();
}

void gerenciaTecladoEspecial(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            gPosY += 0.1f;
            break;
        case GLUT_KEY_DOWN:
            gPosY -= 0.1f;
            break;
        case GLUT_KEY_LEFT:
            gPosX -= 0.1f;
            break;
        case GLUT_KEY_RIGHT:
            gPosX += 0.1f;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Transformacoes 2D com Ponto Fixo");

    init();

    glutDisplayFunc(funcaoDeDesenho);
    glutKeyboardFunc(gerenciaTeclado);
    glutSpecialFunc(gerenciaTecladoEspecial);

    glutMainLoop();
    return 0;
}