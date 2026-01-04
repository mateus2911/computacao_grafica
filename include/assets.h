#ifndef ASSETS_H
#define ASSETS_H

#include <GL/glut.h>

// Carrega um modelo 3D no formato OBJ e retorna o ID da Display List
GLuint carregar_Obj(const char* nomeArquivo);

// Carrega uma textura de imagem e retorna o ID da textura OpenGL
GLuint carregaTextura(const char* nomeArquivo);

#endif
