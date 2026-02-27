#include "../include/camera.h"
#include <GL/glu.h>
#include <math.h>

#define PI 3.14159265f


void camera_init(Camera* c) {
    c->modo = 1;
    c->distancia = 16.0f;
    c->altura = 8.0f;
    c->suavizacao = 10.0f;
    c->camX = 0.0f;
    c->camY = c->altura;
    c->camZ = 0.0f;
    c->inicializada = 0;
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
        const float lookAhead = 2.0f;

        static int ultimoTempoMs = 0;
        int tempoAtualMs = glutGet(GLUT_ELAPSED_TIME);
        float deltaTime = (tempoAtualMs - ultimoTempoMs) / 1000.0f;
        if (deltaTime < 0.0f) deltaTime = 0.0f;
        if (deltaTime > 0.1f) deltaTime = 0.1f;
        ultimoTempoMs = tempoAtualMs;
        
        // Calcula posição da câmera atrás do jogador
        float alvoCamX = p->x - sinf(radianos) * c->distancia;
        float alvoCamZ = p->z - cosf(radianos) * c->distancia;
        float alvoCamY = c->altura;

        if (!c->inicializada) {
            c->camX = alvoCamX;
            c->camY = alvoCamY;
            c->camZ = alvoCamZ;
            c->inicializada = 1;
        }

        float fator = 1.0f - expf(-c->suavizacao * deltaTime);
        c->camX += (alvoCamX - c->camX) * fator;
        c->camY += (alvoCamY - c->camY) * fator;
        c->camZ += (alvoCamZ - c->camZ) * fator;

        float alvoX = p->x + sinf(radianos) * lookAhead;
        float alvoY = 2.0f;
        float alvoZ = p->z + cosf(radianos) * lookAhead;

        gluLookAt(
            c->camX, c->camY, c->camZ,  // Posição da câmera suavizada
            alvoX, alvoY, alvoZ,        // Olha para frente do jogador
            0.0f, 1.0f, 0.0f            // Vetor UP
        );
    }
}
