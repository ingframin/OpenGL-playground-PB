#include "Display.h"

Display::Display(const std::string &title, unsigned int width, unsigned int height)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	m_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_OPENGL);
	m_context = SDL_GL_CreateContext(m_window);
	glViewport(0, 0, width, height);
	this->width = width;
	this->height = height;
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
}

Display::~Display()
{
	SDL_DestroyWindow(m_window);
	SDL_GL_DeleteContext(m_context);
}

void Display::clear(float r, float g, float b, float a)
{
	//Clear screen
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::update() const
{
	//glFlush();
	SDL_GL_SwapWindow(m_window);
}

float Display::getRatio() const
{
	return (float)height / (float)width;
}