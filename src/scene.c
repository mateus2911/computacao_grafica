#include "../include/scene.h"
#include "../include/assets.h"


void scene_init(Scene* s, const char* texturaChaoPath) {
    s->idTexturaChao = carregaTextura(texturaChaoPath);
    s->tamanho = 50.0f;
    s->repeticoes = 10.0f;
}


void scene_draw(Scene* s) {
    // Define a cor do terreno - BRANCO para não filtrar cores da textura
    glColor3f(1.0f, 1.0f, 1.0f);

    glEnable(GL_TEXTURE_2D);
    
    // Usa MODULATE para combinar cor com textura
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, s->idTexturaChao);

    glBegin(GL_QUADS);

        // Define a normal apontando para cima
        glNormal3f(0.0f, 1.0f, 0.0f);

        // Define os vértices do terreno
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-s->tamanho, 0.0f, -s->tamanho);

        glTexCoord2f(0.0f, s->repeticoes);
        glVertex3f(s->tamanho, 0.0f, -s->tamanho);

        glTexCoord2f(s->repeticoes, s->repeticoes);
        glVertex3f(s->tamanho, 0.0f, s->tamanho);

        glTexCoord2f(s->repeticoes, 0.0f);
        glVertex3f(-s->tamanho, 0.0f, s->tamanho);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}
