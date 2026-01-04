#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glut.h>

typedef struct {
    float x, z;
    float rotY;
    float velocidade;
    float rotVel;
    GLuint idTextura;
    GLuint idModelo;
} Player;

// Inicializa o jogador com valores padrão e carrega assets
void player_init(Player* p, const char* texturaPath, const char* modeloPath);

// Atualiza a posição/rotação do jogador baseado nas teclas pressionadas
void player_update(Player* p, int* chaves);

// Desenha o jogador na tela
void player_draw(Player* p);

#endif
