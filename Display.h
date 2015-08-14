#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>
class Display
{
public:
	
	Display(const std::string& title, unsigned int width, unsigned int height);
	
	float getRatio();
	void update();

	void dispose();
	void clear(float r, float g, float b, float a);
	virtual ~Display();

private:
	SDL_Window* m_window;
	SDL_GLContext m_context;
	unsigned int width;
	unsigned int height;

};

