# Makefile para Meteor Runner
# Alternativa ao CMake para compilação manual

CC = gcc
CFLAGS = -Wall -g -I./include -I./freeglut/include
LDFLAGS = -L./freeglut/lib/x64 -lfreeglut -lopengl32 -lglu32 -lgdi32 -lwinmm -lm

# Diretórios
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/Meteor_Runner

# Arquivos fonte
SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/assets.c \
          $(SRC_DIR)/player.c \
          $(SRC_DIR)/scene.c \
          $(SRC_DIR)/camera.c\
		  $(SRC_DIR)/meteoro.c \
		  $(SRC_DIR)/pontuacao.c

# Arquivos objeto
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Regra padrão
all: $(BUILD_DIR) $(TARGET)

# Cria diretório build se não existir
$(BUILD_DIR):
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# Linka o executável
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compila arquivos .c em .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Executa o jogo
run: all
	cd $(BUILD_DIR) && set PATH=..\freeglut\bin\x64;%PATH% && Meteor_Runner.exe

# Limpa arquivos compilados
clean:
	if exist $(BUILD_DIR)\*.o del /Q $(BUILD_DIR)\*.o
	if exist $(TARGET).exe del /Q $(TARGET).exe

# Rebuild completo
rebuild: clean all

.PHONY: all clean run rebuild
