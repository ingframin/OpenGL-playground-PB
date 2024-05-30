#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <vector>
#include "math_utils.h"
#include "ShaderProgram.h"

/*This is a temporary struct to free up space in the main.
It must be fixed:
- Proper model handling (vertices, normals, colors and texture coordinates in separate VBOs?)
- Proper texture handling
- Remove hardcoding of the shaders
- Reduce decoupling
- Separate different transforms: rotation, scaling and translation
- Add animation/frames/spritesheet
*/

struct Model2D{
    //Entity ID
    uint64_t ID;
    /********/
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint tex;

    GLuint transform;
    GLuint projection;
    Model2D(GLfloat vertices[], int len, SDL_Surface* tmp);
    void setTransform(math_utils::mat4 proj, math_utils::mat4 globalTransform);
    void move(float dx, float dy);
    void rotate(float angle);
    void scale(float sc);
    void draw();

};