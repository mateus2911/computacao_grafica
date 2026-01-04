#ifndef SCENE_H
#define SCENE_H

#include <GL/glut.h>

typedef struct {
    GLuint idTexturaChao;
    float tamanho;      // Tamanho do terreno (lado do quadrado)
    float repeticoes;   // Quantas vezes a textura repete
} Scene;

// Inicializa a cena e carrega a textura do chão
void scene_init(Scene* s, const char* texturaChaoPath);

// Desenha o terreno
void scene_draw(Scene* s);

#endif
