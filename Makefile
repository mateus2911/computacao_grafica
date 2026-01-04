# Makefile para Meteor Runner
# Alternativa ao CMake para compilação manual

CC = gcc
CFLAGS = -Wall -g -I./include
LDFLAGS = -lGL -lGLU -lglut -lm

# Diretórios
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/Meteor_Runner

# Arquivos fonte
SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/assets.c \
          $(SRC_DIR)/player.c \
          $(SRC_DIR)/scene.c \
          $(SRC_DIR)/camera.c

# Arquivos objeto
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Regra padrão
all: $(BUILD_DIR) $(TARGET)

# Cria diretório build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Linka o executável
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compila arquivos .c em .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Executa o jogo
run: all
	cd $(BUILD_DIR) && ./Meteor_Runner

# Limpa arquivos compilados
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

# Rebuild completo
rebuild: clean all

.PHONY: all clean run rebuild
