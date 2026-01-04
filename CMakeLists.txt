cmake_minimum_required(VERSION 3.10)
project(Meteor_Runner LANGUAGES C)

set(CMAKE_C_STANDARD 99)

# === Política CMP0072 e preferência GLVND ===
if (POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()
set(OpenGL_GL_PREFERENCE GLVND)

# === Encontrar OpenGL e GLUT ===
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# === Caminhos do freeglut (RELATIVOS AO PROJETO) ===
set(FREEGLUT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/freeglut")
include_directories("${FREEGLUT_ROOT}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
link_directories("${FREEGLUT_ROOT}/lib/x64")

# === Arquivos fonte ===
set(SOURCES
    src/main.c
    src/assets.c
    src/player.c
    src/scene.c
    src/camera.c
)

# === Executável ===
add_executable(${PROJECT_NAME} ${SOURCES})

# === Linkar bibliotecas (cross-platform) ===
if (WIN32)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            freeglut
            opengl32
            glu32
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
else()
    if (OPENGL_FOUND)
        target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
    endif()
    if (GLUT_FOUND)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${GLUT_LIBRARIES})
        include_directories(${GLUT_INCLUDE_DIRS})
    endif()

    # === Link GLU (resolve gluLookAt, gluPerspective) ===
    target_link_libraries(${PROJECT_NAME} PRIVATE GLU m)
endif()