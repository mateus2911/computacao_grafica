#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glut.h>
#include "scene.h"

// Constantes de configuração
#define PLAYER_RAIO_HITBOX 2.0f


typedef struct {
    float x, z;
    float rotY;
    float velocidade;
    float rotVel;
    float hitboxRaio;
    GLuint idTextura;
    GLuint idModelo;
} Player;

// Inicializa o jogador com valores padrão e carrega assets
void player_init(Player* p, const char* texturaPath, const char* modeloPath);

// Atualiza a posição/rotação do jogador baseado nas teclas pressionadas
void player_update(Player* p, int* chaves, Scene* cena, float deltaTime);

// Desenha o jogador na tela
void player_draw(Player* p);

#endif
