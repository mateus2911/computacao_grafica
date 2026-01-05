#ifndef METEORO_H
#define METEORO_H

#include <GL/glut.h>
#include <stdlib.h>

typedef struct 
{
    float x, y, z;
    float velocidade;
    int estado;
} Meteoro;

// Inicializa um array de meteoros
Meteoro* meteoros_init(int numMeteoros);

// Atualiza a posição de todos os meteoros
void meteoros_update(Meteoro* vetor_meteoros, int numMeteoros);

// Desenha um meteoro individual
void meteoro_draw(Meteoro* m);

// Reinicia um meteoro para uma nova posição
void reinicia_meteoro(Meteoro* m);

#endif



