#include "../include/camera.h"
#include <GL/glu.h>
#include <math.h>

#define PI 3.14159265f


void camera_init(Camera* c) {
    c->modo = 0;
    c->distancia = 8.0f;
    c->altura = 4.0f;
}


void camera_alternar_modo(Camera* c) {
    c->modo = !c->modo;
}


void camera_aplicar(Camera* c, Player* p) {
    if (c->modo == 0) {
        // Modo 0: Visão de cima (Top-down)
        gluLookAt(
            0.0f, 80.0f, 0.0f,          // Posição da câmera (bem alto)
            p->x, 0.0f, p->z,           // Olha para o jogador
            0.0f, 1.0f, 0.0f           // Vetor UP ajustado para visão de cima
        );
    } else {
        // Modo 1: Terceira pessoa (segue o jogador)
        float radianos = p->rotY * (PI / 180.0f);
        
        // Calcula posição da câmera atrás do jogador
        float camX = p->x - sinf(radianos) * c->distancia;
        float camZ = p->z - cosf(radianos) * c->distancia;
        float camY = c->altura;

        gluLookAt(
            camX, camY, camZ,           // Posição da câmera
            p->x, 2.0f, p->z,           // Olha para o jogador (um pouco acima do chão)
            0.0f, 1.0f, 0.0f            // Vetor UP
        );
    }
}
