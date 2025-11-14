cmake_minimum_required(VERSION 3.10)
project(OpenGL_C LANGUAGES C)

set(CMAKE_C_STANDARD 99)

# === Encontrar OpenGL ===
find_package(OpenGL REQUIRED)

# === Caminhos do freeglut (RELATIVOS AO PROJETO) ===
set(FREEGLUT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/freeglut")
include_directories("${FREEGLUT_ROOT}/include")
link_directories("${FREEGLUT_ROOT}/lib/x64")

# === Executável ===
add_executable(${PROJECT_NAME} main.c
        freeglut/include/GL/freeglut_ext.h)

# === Linkar bibliotecas ===
target_link_libraries(${PROJECT_NAME}
        OpenGL::GL
        glu32
        freeglut
        opengl32
)

# === DLL está em bin/x64 ===
set(FREEGLUT_DLL "${FREEGLUT_ROOT}/bin/x64/freeglut.dll")
set(DEST_DIR "$<TARGET_FILE_DIR:${PROJECT_NAME}>")

# === Verifica se DLL existe ===
if(NOT EXISTS "${FREEGLUT_DLL}")
    message(FATAL_ERROR "freeglut.dll NAO ENCONTRADO! Verifique a pasta: ${FREEGLUT_DLL}")
endif()

# === Copia DLL após build ===
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${FREEGLUT_DLL}"
        "${DEST_DIR}/"
        COMMENT "Copiando freeglut.dll para pasta do executavel..."
        VERBATIM
)