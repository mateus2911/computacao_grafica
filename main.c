#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>


// --- BIBLIOTECA DE IMAGEM ---
#define STB_IMAGE_IMPLEMENTATION // Necessário definir isso antes do include
#include "stb_image.h"

#define FAST_OBJ_IMPLEMENTATION
#include "fast_obj.h"

#define PI 3.14159265

int modoCamera = 0;

float camX = 0.0f;
float camY = 10.0f;
float camZ = 20.0f;



// Personagem
float playerX = 0.0f;
float playerZ = 0.0f;
float playerRotY = 0.0f; // Ângulo de rotação em graus
float playerVelocidade = 0.8f;
float playerRotVel = 5.0f;

// IDs OpenGL
GLuint idTexturaChao;
GLuint idTexturaPersonagem;
GLuint idModeloPersonagem; // Display List do boneco

// Array para guardar o estado de cada tecla (0 = solta, 1 = pressionada)
// 256 é o número de caracteres na tabela ASCII
int chaves[256];


GLuint carregar_Obj(const char* nomeArquivoObj){

    //Utiliza a biblioteca para ler o arquivo
    fastObjMesh* mesh = fast_obj_read(nomeArquivoObj);
    if (!mesh) {
        printf("ERRO: Modelo 3D nao encontrado: %s\n", nomeArquivoObj);
        return 0;
    }

    GLuint idLista = glGenLists(1);
    glNewList(idLista, GL_COMPILE);

    // Loop por todas as faces (suporta triângulos e quads)
    unsigned int indexOffset = 0;
    for (unsigned int f = 0; f < mesh->face_count; f++) {
        unsigned int faceVerts = mesh->face_vertices[f]; // Número de vértices nesta face
        
        if (faceVerts == 3) {
            glBegin(GL_TRIANGLES);
        } else if (faceVerts == 4) {
            glBegin(GL_QUADS);
        } else {
            glBegin(GL_POLYGON);
        }
        
        for (unsigned int v = 0; v < faceVerts; v++) {
            fastObjIndex idx = mesh->indices[indexOffset + v];
            
            if (idx.n) glNormal3fv(&mesh->normals[idx.n * 3]);
            if (idx.t) glTexCoord2fv(&mesh->texcoords[idx.t * 2]);
            glVertex3fv(&mesh->positions[idx.p * 3]);
        }
        
        glEnd();
        indexOffset += faceVerts;
    }

    glEndList();

    fast_obj_destroy(mesh);
    printf("Modelo %s carregado com sucesso via fast_obj!\n", nomeArquivoObj);
    return idLista;
}


GLuint carregaTextura(const char* nomeArquivoTextura){

    GLuint idTextura;

    int largura, altura, canais;

    // Inverte a imagem verticalmente (OpenGL espera origem no canto inferior esquerdo)
    stbi_set_flip_vertically_on_load(1);

    //Carrega os dados da textura usando a biblioteca stb_image
    unsigned char* dados = stbi_load(nomeArquivoTextura, &largura, &altura, &canais, 0);

    // Verifica se a imagem foi carregada com sucesso
    if (dados == NULL) {
        printf("ERRO: Nao foi possivel carregar a textura: %s\n", nomeArquivoTextura);
        return 0;
    }
    
    printf("Textura carregada com sucesso: %s (%d x %d, canais: %d)\n", nomeArquivoTextura, largura, altura, canais);

    //Salav a textura carregada e retorna o id dela
    glGenTextures(1, &idTextura);

    glBindTexture(GL_TEXTURE_2D, idTextura);

    // Corrige alinhamento de pixels (importante para imagens RGB de 3 canais)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //Faz as textura se repetir
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Eixo X da textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Eixo Y da textura

    //Aplica filtro na textura ao aproximar e afastar a tela
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Ao afastar (Minifying) com mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Ao aproximar (Magnifying)

    // Envia os pixels da RAM para a VRAM (Placa de Vídeo)
    // Se a imagem tiver 3 canais (RGB) ou 4 (RGBA/Transparência)
    int formato = (canais == 4) ? GL_RGBA : GL_RGB;
    
    // Usa gluBuild2DMipmaps para gerar mipmaps automaticamente (corrige efeito moiré)
    gluBuild2DMipmaps(GL_TEXTURE_2D, formato, largura, altura, formato, GL_UNSIGNED_BYTE, dados);

    // Libera a memória RAM (já está na placa de vídeo agora)
    stbi_image_free(dados);

    return idTextura;

}


void desenhaTerreno(){

    //Define a cor do terreno - BRANCO para não filtrar cores da textura
    glColor3f(1.0f, 1.0f, 1.0f);

    glEnable(GL_TEXTURE_2D);
    
    // Usa MODULATE para combinar cor com textura
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, idTexturaChao);

    glBegin(GL_QUADS);

        //Define a normal apontando para o topo
        glNormal3f(0.0f, 1.0f, 0.0f);

        //Define os vertice do terreno, o glVertex3f() define os pontos extremo do quadrilatero
        // e o glTexCoord2f() define onde o extremos de onde ira ser desenhado os quadrados verdes
        // o 10.0f define quantos quadrados de textura serao desenhados dentro desse quadrilatero
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-50.0f, 0.0f, -50.0f);

        glTexCoord2f(0.0f, 10.0f);
        glVertex3f(50.0f, 0.0f, -50.0f);

        glTexCoord2f(10.0f, 10.0f);
        glVertex3f(50.0f, 0.0f, 50.0f);

        glTexCoord2f(10.0f, 0.0f);
        glVertex3f(-50.0f, 0.0f, 50.0f);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void desenhaPersonagem() {
    glPushMatrix(); // Isola a matriz para mexer só no boneco

        // 1. Move para a posição X, Z atual
        glTranslatef(playerX, 0.0f, playerZ);

        // 2. Gira o personagem (Rotação no eixo Y)
        glRotatef(playerRotY, 0.0f, 1.0f, 0.0f);

        // 3. Escala (AJUSTE AQUI se seu boneco for gigante ou minúsculo)
        glScalef(1.0f, 1.0f, 1.0f); 

        // 4. Desenha com textura
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, idTexturaPersonagem);
        glColor3f(1.0f, 1.0f, 1.0f); // Garante que não fique escuro sem luz

        glCallList(idModeloPersonagem); // Chama a lista criada pelo fast_obj

        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void display(){
    atualizarMovimento();
    // Limpa a tela, o GL_COLOR_BUFFER_BIT reseta a cor de fundo original e o 
    // GL_DEPTH_BUFFER_BIT limpa o buffer da profundidade dos elementos
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reseta a matriz de transformações, se nao resetada as transformações podem ser acumuladas
    // em cada quadro
    glLoadIdentity();

    
    //Camera fiza no topo
    if(modoCamera == 0){
        //(camX,camY,camZ): Define onde a camera esta no terreno
        //0.0f, 0.0f, 0.0f : Define para onde a camera esta olhando
        //0.0f, 1.0f, 0.0f): Define o topo da camera, no caso o topo, o y.
        gluLookAt(0.0f,80.0f,0.0f,
                playerX, 0.0f, playerZ,
                0.0f, 1.0f, 0.0f);
    }else {
        // --- MODO 2: TERCEIRA PESSOA (SEGUE O BONECO) ---
        
        // 1. Converter angulo para radianos
        float radianos = playerRotY * (PI / 180.0f);
        
        // 2. Definir a distancia da câmera
        float distanciaH = 8.0f; // Distância horizontal (atrás)
        float alturaCam = 4.0f;  // Altura da câmera
        
        // 3. Calcular posição da Câmera (Matemática crucial)
        // Se o boneco anda somando Sin/Cos, a câmera fica subtraindo Sin/Cos
        float camX_TP = playerX - sin(radianos) * distanciaH;
        float camZ_TP = playerZ - cos(radianos) * distanciaH;
        float camY_TP = alturaCam; // Altura fixa em relação ao chão

        // 4. Configurar o gluLookAt
        gluLookAt(camX_TP, camY_TP, camZ_TP, // Onde a câmera está
                  playerX, 2.0f, playerZ,    // Para onde ela olha (para o boneco, um pouco acima do pé)
                  0.0f, 1.0f, 0.0f);         // Vetor UP
    } 
    
    //Chama a função desenhar o terreno
    desenhaTerreno();

    //Desenha o personagem
    desenhaPersonagem();

    //Troca os buffers onde os dados foram salvos, o codigo usa um buffer propio para armazenar os calculos
    //o computador usa outro, essa função faz isso, troca os dados dos buffers
    glutSwapBuffers();


}

//Função que define os parametros inicias
void init(){
    //Define a cor de fundo da aplicação para azul celeste
    glClearColor(0.5f, 0.8f, 0.9f, 1.0f);

    //Testa a profundidade dos elementos que estão sendo desenhados, na tela, sem isso o opengl desenha
    // os elemntos na ordem que aparecem no codigo, podendo haver sobreposições
    glEnable(GL_DEPTH_TEST);
    
    // Desabilita lighting para que a textura mostre suas cores naturais
    glDisable(GL_LIGHTING);

    // Carrega Assets
    idTexturaChao = carregaTextura("../grama.jpg");
    idTexturaPersonagem = carregaTextura("../personagem.jpg");
    
    // Aqui usamos a função nova com fast_obj
    idModeloPersonagem = carregar_Obj("../personagem.obj");
}


//Desenha a camera
void reshape(int w, int h){


    if(h==0){
        h=1;
    }

    //Define o aspecto da largura/altura.
    float aspect = (float) w/h;


    //Recebe os novos valores do tamanho da janela
    glViewport(0, 0, w, h);

    //Sai do modo de edição dos objetos na cena e entra no modo editor da camera
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    //Configura a camera, 0 angulo de visao em 45 graus, o aspecto da cena
    //a profundidade aonde os elementos serão desenhados, o minimo 0.1 e o maximo 1000
    gluPerspective(45.0f, aspect, 0.1f, 1000.0f);

    //Volta para o modo de edição dos objetos da cena
    glMatrixMode(GL_MODELVIEW);

}

// Chamada quando uma tecla é PRESSIONADA
void tecladoDown(unsigned char key, int x, int y) {
    // Para aceitar maiúsculas e minúsculas, convertemos tudo para minúsculo
    if (key >= 'A' && key <= 'Z') {
        key = key + 32; // 'A' vira 'a'
    }
    
    chaves[key] = 1; // Marca a tecla como pressionada

    // O ESC continua funcionando direto
    if (key == 27) exit(0);
}



// Chamada quando uma tecla é SOLTA
void tecladoUp(unsigned char key, int x, int y) {
    if (key >= 'A' && key <= 'Z') {
        key = key + 32;
    }
    
    chaves[key] = 0; // Marca a tecla como solta
    
    // tecla 'c' para trocar câmera (funciona melhor no Up para não piscar rápido demais)
    if (key == 'c') {
         modoCamera = !modoCamera;
    }
}

void atualizarMovimento() {
    float radianos = playerRotY * (PI / 180.0f);
    
    // Se 'w' está pressionado
    if (chaves['w']) {
        playerX += sin(radianos) * playerVelocidade;
        playerZ += cos(radianos) * playerVelocidade;
    }
    
    // Se 's' está pressionado
    if (chaves['s']) {
        playerX -= sin(radianos) * playerVelocidade;
        playerZ -= cos(radianos) * playerVelocidade;
    }

    // Se 'a' está pressionado (Girar)
    if (chaves['a']) {
        playerRotY += playerRotVel;
    }

    // Se 'd' está pressionado (Girar)
    if (chaves['d']) {
        playerRotY -= playerRotVel;
    }
}

int main(int argc, char** argv) {

    //Incia a aplicação glut
    glutInit(&argc, argv);

    //Define os parametros da tela
    // GLUT_DOUBLE: Usa dois buffers de imagem para animação suave (sem piscar).
    // GLUT_RGB: Usa sistema de cores Red/Green/Blue.
    // GLUT_DEPTH: Cria memória para guardar a profundidade (Z-buffer).
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //Define o tamanho da tela incial
    glutInitWindowSize(800, 600);

    glutCreateWindow("Meteor Runner");



    init();

    // Zera o vetor de teclas para evitar lixo de memória
    for(int i=0; i<256; i++) chaves[i] = 0;

    glutKeyboardFunc(tecladoDown);  
    glutKeyboardUpFunc(tecladoUp);

    glutDisplayFunc(display);

    glutIdleFunc(display);

    glutReshapeFunc(reshape);


    glutMainLoop();
    return 0;
}