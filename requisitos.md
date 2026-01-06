# Especificação do Trabalho: Jogo 3D com OpenGL

Este documento descreve os requisitos funcionais, técnicos e critérios de avaliação para o trabalho prático de Computação Gráfica.

## 1. Visão Geral do Projeto
* [cite_start]**Objetivo:** Implementar uma aplicação gráfica interativa 3D[cite: 7].
* [cite_start]**Descrição:** O projeto consiste em um jogo onde um personagem (real ou fictício) controlado pelo usuário se movimenta em um terreno, fugindo de objetos que caem em posições aleatórias[cite: 8].
* **Tecnologias:**
    * [cite_start]Linguagem: C ou C++[cite: 7].
    * [cite_start]Biblioteca Gráfica: OpenGL[cite: 7].
    * [cite_start]Gerenciamento de Janelas: GLUT ou FreeGLUT[cite: 7].

---

## 2. Requisitos de Implementação (Passo a Passo)

### 2.1. Cenário e Modelagem
- [x] [cite_start]**Terreno:** Construir um plano para representar o terreno do jogo[cite: 9].
- [x] **Modelo do Personagem:**
    - [x] [cite_start]Escolher um modelo `.obj` de um repositório 3D (ex: tf3dm.com) ou modelar no Blender[cite: 10, 11].
    - [x] [cite_start]Carregar o modelo na aplicação (vértices, faces, texturas e normais)[cite: 12].
    - [x] [cite_start]**Obrigatório:** Utilizar o arquivo base `carregar Arquivo2.cpp` para o carregamento do OBJ[cite: 12]. *(Usando fast_obj em assets.c)*

### 2.2. Jogabilidade e Controle
- [x] [cite_start]**Entrada do Usuário:** Controlar a movimentação (rotação e translação) via teclado[cite: 13]. *(W/A/S/D implementado)*
- [x] [cite_start]**Física de Movimento:** O personagem deve se deslocar para frente na direção para a qual está rotacionado (orientado)[cite: 14]. *(Implementado em player.c)*
- [x] [cite_start]**Mecânica do Jogo:** Implementar objetos caindo aleatoriamente dos quais o personagem deve fugir[cite: 8]. *(Meteoros implementados)*

### 2.3. Câmera
[cite_start]O sistema deve permitir alternar entre duas câmeras[cite: 15]:
- [x] **Câmera 1 (Visão Geral):** Posição fixa que permite ver todo o terreno. *(Modo top-down implementado)*
- [x] **Câmera 2 (3ª Pessoa):** Câmera atrás e ligeiramente acima do personagem, deslocando-se na mesma direção que ele. *(Implementado, alterna com tecla C)*

### 2.4. Visualização
- [x] [cite_start]**Texturas:** Aplicar texturas no personagem e no terreno[cite: 16]. *(Implementado)*
- [ ] [cite_start]**Iluminação:** Definir e configurar a iluminação da cena[cite: 17]. ⚠️ **FALTANDO** - Atualmente desabilitada no código

---

## 3. Pontuação Extra (Bônus: 5%)
[cite_start]A implementação dos seguintes itens é opcional e garante pontuação extra[cite: 18]:
* [ ] Movimentação de partes do personagem (animação hierárquica). ⚠️ **NÃO IMPLEMENTADO**
* [ ] Surgimento de obstáculos aleatórios no terreno. ⚠️ **NÃO IMPLEMENTADO**
* [ ] Detecção de colisão. ⚠️ **NÃO IMPLEMENTADO**
* [ ] Skybox. ⚠️ **NÃO IMPLEMENTADO**

---

## 4. Logística e Avaliação

### 4.1. Formato da Equipe
* [cite_start]O trabalho pode ser **individual ou em dupla**[cite: 2].
* [cite_start]Se for em dupla: Apenas um aluno posta no Moodle, mas o `readme` deve conter o nome de ambos[cite: 2].

### 4.2. Apresentação e Defesa
* [cite_start]**Local:** Sala A202[cite: 3].
* [cite_start]**Formato:** Apresentação **individual** para o professor (mesmo para duplas)[cite: 3].
* [cite_start]**Agendamento:** Enviar e-mail para `gildaaa@ufop.edu.br`[cite: 6].

### 4.3. Critérios de Nota (Risco de Zero)
Durante a apresentação:
1.  [cite_start]Serão feitos questionamentos sobre o código[cite: 4].
2.  [cite_start]Será solicitada uma **alteração no código em tempo real**[cite: 4].
3.  [cite_start]**Nota 0.0:** Será atribuída se o aluno não responder corretamente aos questionamentos e/ou não conseguir realizar a alteração solicitada na hora[cite: 5].

---

## Status Geral de Implementação

### ✅ Requisitos Obrigatórios Implementados (90%)
- [x] Cenário e Modelagem
- [x] Jogabilidade e Controle
- [x] Sistema de Câmera
- [x] Texturas

### ❌ Requisitos Obrigatórios Faltando (10%)
- [ ] **Iluminação da cena** - CRÍTICO para completar o trabalho

### ❌ Bônus Não Implementados (0% dos 5% extras)
- [ ] Animação hierárquica
- [ ] Obstáculos no terreno
- [ ] Detecção de colisão
- [ ] Skybox