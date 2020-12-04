#ifndef DISPLAY
#define DISPLAY
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>
class Display
{
public:
	
	Display(const std::string& title, unsigned int width, unsigned int height);
	
	float getRatio() const;
	void update() const;

	void clear(float r, float g, float b, float a);
	virtual ~Display();

private:
	SDL_Window* m_window;
	SDL_GLContext m_context;
	unsigned int width;
	unsigned int height;

};

#endif