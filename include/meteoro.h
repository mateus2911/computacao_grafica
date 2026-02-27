#ifndef METEORO_H
#define METEORO_H

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/player.h"

#define METEORO_RAIO_HITBOX 4.0f
#define METEORO_RAIO_VISUAL 0.1f

typedef struct
{
    float x, y, z;
    float velocidade;
    int estado;
    float hitboxRaio;
    GLuint idTextura;
    GLuint idModelo;
} Meteoro;

Meteoro* meteoros_init(int numMeteoros, const char* texturaPath, const char* modeloPath);
void meteoros_update(Meteoro* vetor_meteoros, int numMeteoros, Player* p, float deltaTime);
void meteoro_draw(Meteoro* m);
void alvo_draw(Meteoro* m);
void reinicia_meteoro(Meteoro* m);

#endif
