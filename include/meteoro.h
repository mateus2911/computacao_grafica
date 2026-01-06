#ifndef METEORO_H
#define METEORO_H

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/player.h"

// Constantes de configuração
#define METEORO_RAIO_HITBOX 2.0f
#define METEORO_RAIO_VISUAL 0.1f  // Raio adicional para visualização

typedef struct 
{
    float x, y, z;
    float velocidade;
    int estado;
    float hitboxRaio;
} Meteoro;

// Inicializa um array de meteoros
Meteoro* meteoros_init(int numMeteoros);

// Atualiza a posição de todos os meteoros
void meteoros_update(Meteoro* vetor_meteoros, int numMeteoros, Player* p);

// Desenha um meteoro individual
void meteoro_draw(Meteoro* m);

void alvo_draw(Meteoro* m);

// Reinicia um meteoro para uma nova posição
void reinicia_meteoro(Meteoro* m);

#endif



