#include "../include/player.h"
#include "../include/assets.h"

#include <math.h>

#define PI 3.14159265f


void player_init(Player* p, const char* texturaPath, const char* modeloPath) {
    p->x = 0.0f;
    p->z = 0.0f;
    p->rotY = 0.0f;
    p->velocidade = 6.0f;
    p->rotVel = 180.0f;
    p->hitboxRaio = PLAYER_RAIO_HITBOX;
    
    // Carrega assets
    p->idTextura = carregaTextura(texturaPath);
    p->idModelo = carregar_Obj(modeloPath);
}


void player_update(Player* p, int* chaves, Scene* cena, float deltaTime) {
    float radianos = p->rotY * (PI / 180.0f);




    // Movimento para frente (W)
    if (chaves['w']) {
        p->x += sinf(radianos) * p->velocidade * deltaTime;
        p->z += cosf(radianos) * p->velocidade * deltaTime;
    }
    
    // Movimento para trás (S)
    if (chaves['s']) {
        p->x -= sinf(radianos) * p->velocidade * deltaTime;
        p->z -= cosf(radianos) * p->velocidade * deltaTime;
    }

    // Rotação esquerda (A)
    if (chaves['a']) {
        p->rotY += p->rotVel * deltaTime;
    }

    // Rotação direita (D)
    if (chaves['d']) {
        p->rotY -= p->rotVel * deltaTime;
    }

    if(p->x > cena->tamanho) p->x = cena->tamanho;
    if(p->x < -cena->tamanho) p->x = -cena->tamanho;
    if(p->z > cena->tamanho) p->z = cena->tamanho;
    if(p->z < -cena->tamanho) p->z = -cena->tamanho;
}


void player_draw(Player* p) {
    glPushMatrix();

        // Ajustes de alinhamento do OBJ (comum quando o arquivo vem em Z-up)
        const float yOffset = 0.5f;
        const float alinhamentoEixoX = -90.0f;
        const float escalaModelo = 0.35f;

        // Move para a posição no terreno
        glTranslatef(p->x, yOffset, p->z);

        // Gira o personagem (Rotação no eixo Y)
        glRotatef(p->rotY, 0.0f, 1.0f, 0.0f);

        // Alinhamento Z-up
        glRotatef(alinhamentoEixoX, 1.0f, 0.0f, 0.0f);

        // Diminui o tamanho do modelo
        glScalef(escalaModelo, escalaModelo, escalaModelo);

        // Desenha com textura
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, p->idTextura);
        glColor3f(1.0f, 1.0f, 1.0f);

        glCallList(p->idModelo);

        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
