/*
 * Meteor Runner - Main
 * Arquivo principal que gerencia o loop do jogo
 */

#include <GL/glut.h>
#include "../include/player.h"
#include "../include/scene.h"
#include "../include/camera.h"
#include "../include/meteoro.h"

// ============================================
// VARIÁVEIS GLOBAIS (agora organizadas em structs)
// ============================================
Player gPlayer;
Scene gScene;
Camera gCamera;
int gChaves[256];
Meteoro* gVetorMeteoros;
int gNumMeteoros = 10;


// ============================================
// CALLBACKS DO GLUT
// ============================================

void display() {
    // Atualiza a lógica do jogador
    player_update(&gPlayer, gChaves, &gScene);

    // Limpa os buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Aplica a câmera
    camera_aplicar(&gCamera, &gPlayer);

    // Atualiza meteoros primeiro
    meteoros_update(gVetorMeteoros, gNumMeteoros);
    
    // Desenha os alvos no chão ANTES do terreno
    for (int i = 0; i < gNumMeteoros; i++) {
        alvo_draw(&gVetorMeteoros[i]);
    }

    // Desenha a cena (terreno)
    scene_draw(&gScene);

    // Desenha o jogador
    player_draw(&gPlayer);

    // Desenha os meteoros (esferas no ar)
    for (int i = 0; i < gNumMeteoros; i++) {
        meteoro_draw(&gVetorMeteoros[i]);
    }

    // Troca os buffers
    glutSwapBuffers();
}


void reshape(int w, int h) {
    if (h == 0) h = 1;
    
    float aspect = (float)w / h;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}


void tecladoDown(unsigned char key, int x, int y) {
    // Converte maiúsculas para minúsculas
    if (key >= 'A' && key <= 'Z') {
        key = key + 32;
    }
    
    gChaves[key] = 1;

    // ESC para sair
    if (key == 27) exit(0);
}


void tecladoUp(unsigned char key, int x, int y) {
    // Converte maiúsculas para minúsculas
    if (key >= 'A' && key <= 'Z') {
        key = key + 32;
    }
    
    gChaves[key] = 0;
    
    // Tecla 'C' para alternar câmera
    if (key == 'c') {
        camera_alternar_modo(&gCamera);
    }
}


// ============================================
// INICIALIZAÇÃO
// ============================================

void init() {
    // Cor de fundo azul celeste
    glClearColor(0.5f, 0.8f, 0.9f, 1.0f);

    // Habilita teste de profundidade
    glEnable(GL_DEPTH_TEST);
    
    // Habilita blending para transparência dos meteoros
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Desabilita iluminação para mostrar cores naturais das texturas
    glDisable(GL_LIGHTING);

    // Inicializa os módulos
    player_init(&gPlayer, "../personagem.jpg", "../personagem.obj");
    scene_init(&gScene, "../grama.jpg");
    camera_init(&gCamera);
    gVetorMeteoros = meteoros_init(gNumMeteoros);
    
    // Zera o vetor de teclas
    for (int i = 0; i < 256; i++) {
        gChaves[i] = 0;
    }
}


// ============================================
// MAIN
// ============================================

int main(int argc, char** argv) {
    // Inicializa o GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Meteor Runner");

    // Inicializa o jogo
    init();

    // Registra callbacks
    glutKeyboardFunc(tecladoDown);
    glutKeyboardUpFunc(tecladoUp);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);

    // Inicia o loop principal
    glutMainLoop();
    
    return 0;
}
