#include "../include/meteoro.h"
#include "../include/assets.h"
#include "../include/player.h" 
#include <math.h>
#include <stdlib.h>
#include "../include/pontuacao.h"

extern Pontuacao gPontuacao;


Meteoro * meteoros_init(int numMeteoros, const char* texturaPath, const char* modeloPath){

    Meteoro * vetor_meteoros = (Meteoro *)malloc(numMeteoros * sizeof(Meteoro));
    GLuint idTexturaMeteoro = carregaTextura(texturaPath);
    GLuint idModeloMeteoro = carregar_Obj(modeloPath);

    for(int i = 0; i<numMeteoros; i++){
        vetor_meteoros[i].x = rand() % 100 - 50; //Posição aleatória entre -50 e 50
        vetor_meteoros[i].y = rand() % 50 + 10; //Posição aleatória entre 10 e 60
        vetor_meteoros[i].z = rand() % 100 - 50; //Posição aleatória entre -50 e 50
        vetor_meteoros[i].velocidade = 10.8f;
        vetor_meteoros[i].estado = 1; //Ativo
        vetor_meteoros[i].hitboxRaio = METEORO_RAIO_HITBOX;
        vetor_meteoros[i].idTextura = idTexturaMeteoro;
        vetor_meteoros[i].idModelo = idModeloMeteoro;
    }

    return vetor_meteoros;
};


/*void meteoro_draw(Meteoro* m, GLuint idModeloMeteoro, GLuint idTexturaMeteoro){

    if(m->estado == 1){
        glPushMatrix();

            // Move para a posição X, Y, Z atual
            glTranslatef(m->x, m->y, m->z);

            // Desenha com textura
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, idTexturaMeteoro);
            glColor3f(1.0f, 1.0f, 1.0f); // Garante que não fique escuro sem luz

            glCallList(idModeloMeteoro); // Chama a lista criada pelo fast_obj

            glDisable(GL_TEXTURE_2D);

        glPopMatrix();
    }

};

*/


void meteoro_draw(Meteoro* m){
    if(m->estado == 1){
        // Calcula a transparência com base na altura (float)
        float alpha = 1.0f - (m->y / 60.0f);
        const float escalaModelo = 0.003f;
        const float centroModeloX = 2.7262f;
        const float centroModeloY = -1.51095f;
        const float centroModeloZ = 700.3422f;
        if(alpha < 0.3f) alpha = 0.3f; // Alpha mínimo para visibilidade
        
        glPushMatrix();

            // Move para a posição X, Y, Z atual
            glTranslatef(m->x, m->y, m->z);
            glScalef(escalaModelo, escalaModelo, escalaModelo);
            glTranslatef(-centroModeloX, -centroModeloY, -centroModeloZ);

            // Desenha com textura
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, m->idTextura);
            glColor4f(1.0f, 1.0f, 1.0f, alpha); // Cor branca com transparência

            glCallList(m->idModelo); // Chama a lista criada pelo fast_obj
            glDisable(GL_TEXTURE_2D);

            

            //glColor4f(1.0f, 0.5f, 0.0f, alpha);    // Cor laranja/vermelha com transparência
        
            // Raio 2.0, 20 fatias, 20 pilhas
            //glutSolidSphere(m->hitboxRaio + METEORO_RAIO_VISUAL, 20, 20);

            

        glPopMatrix();
    }
}

void alvo_draw(Meteoro* m){
    if(m->estado == 1){
        // Salva estados do OpenGL
        glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_POLYGON_BIT);
        
        // Desabilita textura para desenhar com cor sólida
        glDisable(GL_TEXTURE_2D);
        //glDisable(GL_LIGHTING);
        
        // Usa polygon offset para evitar z-fighting com o terreno
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(-1.0f, -1.0f);
        
        float y = 0.1f;  // Altura logo acima do chão
        int segments = 32;
        
        // Desenha círculos concêntricos no plano XZ (horizontal)
        // Círculo vermelho externo (raio 3.0 a 3.5)
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i <= segments; i++){
            float angle = 2.0f * 3.14159f * i / segments;
            float c = cosf(angle);
            float s = sinf(angle);
            glVertex3f(m->x + c * 3.5f, y, m->z + s * 3.5f);
            glVertex3f(m->x + c * 2.5f, y, m->z + s * 2.5f);
        }
        glEnd();
        
        // Círculo branco (raio 2.0 a 2.5)
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i <= segments; i++){
            float angle = 2.0f * 3.14159f * i / segments;
            float c = cosf(angle);
            float s = sinf(angle);
            glVertex3f(m->x + c * 2.5f, y, m->z + s * 2.5f);
            glVertex3f(m->x + c * 1.5f, y, m->z + s * 1.5f);
        }
        glEnd();
        
        // Círculo vermelho interno (raio 1.0 a 1.5)
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i <= segments; i++){
            float angle = 2.0f * 3.14159f * i / segments;
            float c = cosf(angle);
            float s = sinf(angle);
            glVertex3f(m->x + c * 1.5f, y, m->z + s * 1.5f);
            glVertex3f(m->x + c * 0.5f, y, m->z + s * 0.5f);
        }
        glEnd();
        
        // Centro amarelo (raio 0 a 0.5)
        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(m->x, y, m->z);  // Centro
        for(int i = 0; i <= segments; i++){
            float angle = 2.0f * 3.14159f * i / segments;
            glVertex3f(m->x + cosf(angle) * 0.5f, y, m->z + sinf(angle) * 0.5f);
        }
        glEnd();
        
        // Restaura estados do OpenGL
        glPopAttrib();
    }
}

void meteoros_update(Meteoro* vetor_meteoros, int numMeteoros, Player* p, float deltaTime){

    for(int i = 0; i<numMeteoros; i++){
        if(vetor_meteoros[i].estado == 1){
            vetor_meteoros[i].y -= vetor_meteoros[i].velocidade * deltaTime;

            //Verifica colisão com o jogador
            float raioSoma = vetor_meteoros[i].hitboxRaio + p->hitboxRaio;
            float limiteAoQuadrado = raioSoma * raioSoma;

            
            float dx = vetor_meteoros[i].x - p->x;
            float dy = vetor_meteoros[i].y - 0.0f; // Altura do jogador é 0 no eixo Y
            float dz = vetor_meteoros[i].z - p->z;
            

            float distanciaAoQuadrado = (dx * dx) + (dy * dy) + (dz * dz);

            if(distanciaAoQuadrado <= limiteAoQuadrado){
                //Colisão detectada
                printf("Colisão com meteoro!\n");
                pontuacao_colisao(&gPontuacao);
                reinicia_meteoro(&vetor_meteoros[i]);
            }
            //Se o meteoro atingir o chão, reinicia ele
            if(vetor_meteoros[i].y <= 0.0f){
                printf("Meteoro desviado!\n");
                pontuacao_meteoro_desviado(&gPontuacao);
                reinicia_meteoro(&vetor_meteoros[i]);
            }
        }
    }
};


void reinicia_meteoro(Meteoro* m){

    m->x = rand() % 100 - 50; //Posição aleatória entre -50 e 50
    m->y = rand() % 50 + 10; //Posição aleatória entre 10 e 60
    m->z = rand() % 100 - 50; //Posição aleatória entre -50 e 50
    m->velocidade = m->velocidade + 0.5f; // Mantém a mesma velocidade
    m->estado = 1; //Ativo

};