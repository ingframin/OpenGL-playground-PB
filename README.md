# OpenGL playground
Project to experiment while I study c++ and OpenGL 

## Roadmap
1. Fix Model2D class
2. Add 3D Model class
3. Restructure code for less decoupling and improve architecture
4. Proper input handling
5. Implement Font rendering
6. Add physics
7. Implement audio (music + sound effects)
8. Implement event handling
9. Implement state management
10. Make a game out of it (?)

## To compile with GCC
    g++ -DGLEW_STATIC glew.c main.cpp math_utils.cpp ShaderProgram.cpp Display.cpp model2D.cpp -O3 -o./build/game.exe -I./include -L./lib -lOpengl32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer 