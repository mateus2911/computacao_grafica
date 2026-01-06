#ifndef PONTUACAO_H
#define PONTUACAO_H

#include <GL/glut.h>

// Estrutura para gerenciar a pontuação
typedef struct {
    int pontos;
    int meteorosDesviados;
    int colisoes;
    int recorde;
} Pontuacao;

// Inicializa a pontuação
void pontuacao_init(Pontuacao* p);

// Adiciona pontos (meteoro desviado)
void pontuacao_adicionar(Pontuacao* p, int valor);

// Remove pontos (colisão)
void pontuacao_remover(Pontuacao* p, int valor);

// Incrementa contador de meteoros desviados
void pontuacao_meteoro_desviado(Pontuacao* p);

// Incrementa contador de colisões
void pontuacao_colisao(Pontuacao* p);

// Reseta a pontuação atual
void pontuacao_reset(Pontuacao* p);

// Atualiza o recorde se necessário
void pontuacao_atualizar_recorde(Pontuacao* p);

// Desenha o HUD da pontuação na tela
void pontuacao_desenhar_hud(Pontuacao* p);

#endif