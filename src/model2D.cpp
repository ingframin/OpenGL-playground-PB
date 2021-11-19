#include "model2D.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <vector>
#include "math_utils.h"
#include "ShaderProgram.h"

static uint64_t entity_ids=0;

Model2D::Model2D(GLfloat vertices[], SDL_Surface* tmp){
    ID = entity_ids;
    entity_ids++;
    /*This constructor does too many things.
    It will be split into multiple methods*/
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*28, vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &ebo);
    
    //It's a rectangle so only 2 triangles
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0};

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
   

    ShaderProgram sp;
    //Temporary
    // Create and compile the vertex shader
    sp.loadShader("./shaders/vertex.glsl",GL_VERTEX_SHADER);
    
    // Create and compile the fragment shader
    sp.loadShader("./shaders/fragment.glsl",GL_FRAGMENT_SHADER);
    
    // Link the vertex and fragment shader into a shader program
    sp.linkProgram();
    glUseProgram(sp.getProgramID());

     // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(sp.getProgramID(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)0);

    GLint colAttrib = glGetAttribLocation(sp.getProgramID(), "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));

    GLint texAttrib = glGetAttribLocation(sp.getProgramID(), "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(5 * sizeof(GLfloat)));

    transform = glGetUniformLocation(sp.getProgramID(), "transform");
    int Mode = GL_RGB;

    if (tmp->format->BytesPerPixel == 4)
    {
        Mode = GL_RGBA;
    }
    // Load texture
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, Mode, tmp->w, tmp->h, 0, Mode, GL_UNSIGNED_BYTE, tmp->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);


}


void Model2D::setTransform(math_utils::mat4 globalTransform){
    glUniformMatrix4fv(transform, 1, GL_FALSE, globalTransform.getM());
}