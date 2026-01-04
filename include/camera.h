#ifndef CAMERA_H
#define CAMERA_H

#include "player.h"

typedef struct {
    int modo;           // 0 = visão de cima, 1 = terceira pessoa
    float distancia;    // Distância da câmera ao jogador (modo 1)
    float altura;       // Altura da câmera
} Camera;

// Inicializa a câmera com valores padrão
void camera_init(Camera* c);

// Alterna entre os modos de câmera
void camera_alternar_modo(Camera* c);

// Aplica a câmera (chama gluLookAt)
void camera_aplicar(Camera* c, Player* p);

#endif
