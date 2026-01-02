# Meteor Runner

## Descrição
Projeto de Computação Gráfica: aplicação OpenGL/GLUT para demonstração de transformações 2D (translação, rotação, escala com ponto fixo).

---

## Build & Exec — Linux (Linux Mint)
Recomendado usar as bibliotecas do sistema (mais simples) ou usar o `freeglut/` fornecido no repositório.

Dependências recomendadas:
- build-essential, cmake
- pkg-config
- libgl1-mesa-dev (OpenGL)
- libglu1-mesa-dev (GLU)
- freeglut3-dev (GLUT)

Comandos:
```bash
# opcional: instalar dependências
sudo apt update
sudo apt install build-essential cmake pkg-config libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev

# construir
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .

# executar
./Meteor_Runner
```

Testes/interação:
- Tecla `r`: rotaciona o polígono
- Teclas `+` / `-`: aumenta / diminui escala
- Arrow keys: move o polígono

---

## Build & Exec — Windows 10 (MinGW + CLion)
1. Instale MinGW-w64 (32/64-bit conforme sua preferência) e configure toolchain no CLion (Settings → Build, Execution, Deployment → Toolchains).
2. Garanta que o `CMakeLists.txt` do projeto esteja apontando para a pasta `freeglut/` (o projeto já copia `freeglut.dll` para a pasta do executável após o build quando em Windows).
3. Abra o projeto no CLion, escolha o toolchain MinGW e rode o build.

Observações importantes:
- A DLL `freeglut.dll` precisa estar presente em `freeglut/bin/x64/freeglut.dll`. O `CMakeLists.txt` copia a DLL para o diretório do executável automaticamente.
- Se preferir MSVC/Visual Studio, ajuste o toolchain do CLion para o Visual Studio e instale a versão apropriada da freeglut para MSVC.

---

## Notas técnicas
- O código atual usa OpenGL fixed-function (glBegin/glVertex/glRotate/glScale...) com GLUT — é a forma mais simples para aprendizagem.
- O `CMakeLists.txt` define a política CMP0072 e prefere GLVND no Linux (recomendado). Se houver problemas com bibliotecas OpenGL, verifique instalação de `libGL`/`libOpenGL` e `freeglut`.

---

## Troubleshooting rápido
- Aviso CMP0072: já tratado no `CMakeLists.txt` (policy set to NEW e `OpenGL_GL_PREFERENCE` configurado).
- Erro: "No package 'glut' found" — instale `freeglut3-dev` ou use a pasta `freeglut/` do projeto.

---

Se quiser, eu posso adicionar scripts de build (`build.sh`, `build_windows.bat`) e instruções passo-a-passo detalhadas para configurar o MinGW no CLion. Diga se quer que eu adicione esses arquivos automaticamente.