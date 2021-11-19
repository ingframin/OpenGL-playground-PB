#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <vector>
#include "math_utils.h"
#include "ShaderProgram.h"

struct Model2D{
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint tex;

    GLuint transform;

    Model2D(GLfloat vertices[], SDL_Surface* tmp);
    void setTransform(math_utils::mat4 globalTransform);


};