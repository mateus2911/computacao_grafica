#include "../include/player.h"
#include "../include/assets.h"

#include <math.h>

#define PI 3.14159265f


void player_init(Player* p, const char* texturaPath, const char* modeloPath) {
    p->x = 0.0f;
    p->z = 0.0f;
    p->rotY = 0.0f;
    p->velocidade = 0.8f;
    p->rotVel = 5.0f;
    p->hitboxRaio = PLAYER_RAIO_HITBOX;
    
    // Carrega assets
    p->idTextura = carregaTextura(texturaPath);
    p->idModelo = carregar_Obj(modeloPath);
}


void player_update(Player* p, int* chaves, Scene* cena) {
    float radianos = p->rotY * (PI / 180.0f);




    // Movimento para frente (W)
    if (chaves['w']) {
        p->x += sinf(radianos) * p->velocidade;
        p->z += cosf(radianos) * p->velocidade;
    }
    
    // Movimento para trás (S)
    if (chaves['s']) {
        p->x -= sinf(radianos) * p->velocidade;
        p->z -= cosf(radianos) * p->velocidade;
    }

    // Rotação esquerda (A)
    if (chaves['a']) {
        p->rotY += p->rotVel;
    }

    // Rotação direita (D)
    if (chaves['d']) {
        p->rotY -= p->rotVel;
    }

    if(p->x > cena->tamanho) p->x = cena->tamanho;
    if(p->x < -cena->tamanho) p->x = -cena->tamanho;
    if(p->z > cena->tamanho) p->z = cena->tamanho;
    if(p->z < -cena->tamanho) p->z = -cena->tamanho;
}


void player_draw(Player* p) {
    glPushMatrix();

        // Move para a posição X, Z atual
        glTranslatef(p->x, 0.0f, p->z);

        // Gira o personagem (Rotação no eixo Y)
        glRotatef(p->rotY, 0.0f, 1.0f, 0.0f);

        // Desenha com textura
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, p->idTextura);
        glColor3f(1.0f, 1.0f, 1.0f);

        glCallList(p->idModelo);

        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
