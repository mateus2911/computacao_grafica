/*
 * Meteor Runner - Main
 * Arquivo principal que gerencia o loop do jogo
 */

#include <GL/glut.h>
#include "../include/player.h"
#include "../include/scene.h"
#include "../include/camera.h"
#include "../include/meteoro.h"
#include "../include/pontuacao.h"

// ============================================
// VARIÁVEIS GLOBAIS (agora organizadas em structs)
// ============================================
Player gPlayer;
Scene gScene;
Camera gCamera;
int gChaves[256];
Meteoro* gVetorMeteoros;
int gNumMeteoros = 10;
Pontuacao gPontuacao;
int gUltimoTempoMs = 0;


// ============================================
// CALLBACKS DO GLUT
// ============================================




void display() {
    int tempoAtualMs = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (tempoAtualMs - gUltimoTempoMs) / 1000.0f;
    if (deltaTime > 0.1f) deltaTime = 0.1f;
    gUltimoTempoMs = tempoAtualMs;

    // Atualiza a lógica do jogador
    player_update(&gPlayer, gChaves, &gScene, deltaTime);

    // Limpa os buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    


    // Aplica a câmera
    camera_aplicar(&gCamera, &gPlayer);

    // Luz acompanha o jogador (dinâmica)
    float lightPos[] = {0.0f, 1.0f, 0.0f, 0.0f};  // Luz vindo de cima (Y positivo)
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


    // Atualiza meteoros primeiro
    meteoros_update(gVetorMeteoros, gNumMeteoros, &gPlayer, deltaTime);
    
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

    // Desenha o HUD (placar)
    pontuacao_desenhar_hud(&gPontuacao);

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
    
    // Configuração de iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);// Normaliza normais após transformações
    glEnable(GL_COLOR_MATERIAL);  // Permite usar glColor3f com iluminação
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    // Luz ambiente global (clareia toda a cena)
    float globalAmbient[] = {0.6f, 0.6f, 0.6f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
    
    // Propriedades da luz principal
    //float lightPos[] = {0.0f, 100.0f, 0.0f, 1.0f};  // Posição (luz pontual)
    float lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};  // Luz ambiente
    float lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};  // Luz difusa (principal)
    float lightSpecular[] = {0.2f, 0.2f, 0.2f, 1.0f}; // Luz especular (brilho)
    
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Inicializa os módulos
    player_init(&gPlayer, "../personagem.jpg", "../pato_borracha.obj");
    scene_init(&gScene, "../grama.jpg");
    camera_init(&gCamera);
    gVetorMeteoros = meteoros_init(gNumMeteoros);
    pontuacao_init(&gPontuacao);
    
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
    gUltimoTempoMs = glutGet(GLUT_ELAPSED_TIME);

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
