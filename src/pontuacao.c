#include "../include/pontuacao.h"
#include <stdio.h>
#include <string.h>

// Função auxiliar para desenhar texto
static void desenhaTexto(float x, float y, const char* texto) {
    glRasterPos2f(x, y);
    for (const char* c = texto; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void pontuacao_init(Pontuacao* p) {
    p->pontos = 0;
    p->meteorosDesviados = 0;
    p->colisoes = 0;
    p->recorde = 0;
}

void pontuacao_adicionar(Pontuacao* p, int valor) {
    p->pontos += valor;
    if (p->pontos < 0) {
        p->pontos = 0;  // Não deixa ficar negativo
    }
}

void pontuacao_remover(Pontuacao* p, int valor) {
    p->pontos -= valor;
    if (p->pontos < 0) {
        p->pontos = 0;  // Não deixa ficar negativo
    }
}

void pontuacao_meteoro_desviado(Pontuacao* p) {
    p->meteorosDesviados++;
    pontuacao_adicionar(p, 5);  // +5 pontos por meteoro desviado
}

void pontuacao_colisao(Pontuacao* p) {
    p->colisoes++;
    pontuacao_remover(p, 10);  // -10 pontos por colisão
}

void pontuacao_reset(Pontuacao* p) {
    pontuacao_atualizar_recorde(p);
    p->pontos = 0;
    p->meteorosDesviados = 0;
    p->colisoes = 0;
}

void pontuacao_atualizar_recorde(Pontuacao* p) {
    if (p->pontos > p->recorde) {
        p->recorde = p->pontos;
    }
}

void pontuacao_desenhar_hud(Pontuacao* p) {
    // Salva as matrizes atuais
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    // Configura projeção ortográfica 2D
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluOrtho2D(0, w, 0, h);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // Desabilita iluminação e profundidade para o HUD
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    // Desenha o fundo semi-transparente
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(5, h - 5);
        glVertex2f(250, h - 5);
        glVertex2f(250, h - 120);
        glVertex2f(5, h - 120);
    glEnd();
    glDisable(GL_BLEND);
    
    // Desenha os textos
    glColor3f(1.0f, 1.0f, 1.0f);  // Cor branca
    
    char texto[100];
    
    // Pontuação atual
    sprintf(texto, "Pontos: %d", p->pontos);
    desenhaTexto(15, h - 25, texto);
    
    // Meteoros desviados
    sprintf(texto, "Desviados: %d", p->meteorosDesviados);
    desenhaTexto(15, h - 50, texto);
    
    // Colisões
    sprintf(texto, "Colisoes: %d", p->colisoes);
    desenhaTexto(15, h - 75, texto);
    
    // Recorde
    glColor3f(1.0f, 0.84f, 0.0f);  // Cor dourada para o recorde
    sprintf(texto, "Recorde: %d", p->recorde);
    desenhaTexto(15, h - 100, texto);
    
    // Restaura estados do OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    // Restaura as matrizes
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}