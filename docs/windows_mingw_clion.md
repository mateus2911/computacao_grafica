# Guia: Configurar MinGW + CLion para este projeto (Windows 10)

Este documento descreve passos para configurar o MinGW toolchain no CLion e garantir que o projeto CMake funcione com a `freeglut.dll`.

## 1) Instalar MinGW-w64
- Baixe e instale MinGW-w64 (recomendo a build "posix" e a exceção "seh" para x86_64). Exemplo: MSYS2 ou instalação standalone.
- Adicione o diretório `bin` do MinGW ao PATH (por exemplo: `C:\mingw64\bin`).

## 2) Instalar CLion e configurar Toolchain
- Abra CLion → File → Settings → Build, Execution, Deployment → Toolchains.
- Adicione um novo toolchain apontando para o MinGW-w64 instalado (C, C++ compilers e Debugger).
- Em "CMake", configure a versão do CMake se necessário.

## 3) Dependências (freeglut)
- Use a pasta `freeglut/` já incluída no repositório (contém `bin/x64/freeglut.dll`, `lib/x64` e `include/GL`).
- O `CMakeLists.txt` já está preparado para copiar `freeglut.dll` automaticamente após o build quando em Windows.

## 4) Abrir o projeto no CLion
- Abra a pasta do projeto (contendo `CMakeLists.txt`) no CLion.
- Selecione o toolchain MinGW e deixe o CLion rodar a configuração CMake.

## 5) Build e execução
- Clique em Build → Build Project (ou use o ícone de build).
- Após o build, verifique a pasta de saída do executável (círculo de run). A DLL `freeglut.dll` deve ter sido copiada para o mesmo diretório do executável.
- Execute o target pela interface do CLion (Run) — a janela OpenGL deve abrir.

## 6) Problemas comuns e soluções
- Erro: "freeglut.dll not found" → verifique `freeglut/bin/x64/freeglut.dll` existe e permissões; CMake copia essa DLL para o diretório do executável, mas se o caminho for diferente, ajuste `FREEGLUT_ROOT` no `CMakeLists.txt`.
- Erro de link: verifique se o MinGW é compatível (versão 64-bit vs 32-bit) e se as libs em `freeglut/lib/x64` batem com seu toolchain.
- Se preferir, você pode instalar uma versão do freeglut via pacotes do MSYS2 e linkar usando as bibliotecas do sistema.

## 7) Checklist que posso executar com você
- [ ] Confirma que o MinGW está instalado e no PATH
- [ ] Toolchain configurado no CLion
- [ ] `freeglut.dll` disponível em `freeglut/bin/x64`
- [ ] Build no CLion concluído sem erros
- [ ] Executável roda e abre janela OpenGL

Se quiser, eu posso gerar um `build_windows.bat` e instruções para baixar uma build compatível do freeglut e também preparar um checklist que você possa executar no Windows e compartilhar os logs de erro caso algo falhe.