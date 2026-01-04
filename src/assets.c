#include "../include/assets.h"
#include <stdio.h>

// Define as implementações das bibliotecas header-only
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#define FAST_OBJ_IMPLEMENTATION
#include "../fast_obj.h"


GLuint carregar_Obj(const char* nomeArquivoObj) {
    // Utiliza a biblioteca para ler o arquivo
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
        unsigned int faceVerts = mesh->face_vertices[f];
        
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


GLuint carregaTextura(const char* nomeArquivoTextura) {
    GLuint idTextura;
    int largura, altura, canais;

    // Inverte a imagem verticalmente (OpenGL espera origem no canto inferior esquerdo)
    stbi_set_flip_vertically_on_load(1);

    // Carrega os dados da textura usando a biblioteca stb_image
    unsigned char* dados = stbi_load(nomeArquivoTextura, &largura, &altura, &canais, 0);

    if (dados == NULL) {
        printf("ERRO: Nao foi possivel carregar a textura: %s\n", nomeArquivoTextura);
        return 0;
    }
    
    printf("Textura carregada com sucesso: %s (%d x %d, canais: %d)\n", 
           nomeArquivoTextura, largura, altura, canais);

    glGenTextures(1, &idTextura);
    glBindTexture(GL_TEXTURE_2D, idTextura);

    // Corrige alinhamento de pixels (importante para imagens RGB de 3 canais)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Faz a textura se repetir
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Aplica filtro na textura ao aproximar e afastar
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Define o formato baseado no número de canais
    int formato = (canais == 4) ? GL_RGBA : GL_RGB;
    
    // Usa gluBuild2DMipmaps para gerar mipmaps automaticamente
    gluBuild2DMipmaps(GL_TEXTURE_2D, formato, largura, altura, formato, GL_UNSIGNED_BYTE, dados);

    // Libera a memória RAM
    stbi_image_free(dados);

    return idTextura;
}
