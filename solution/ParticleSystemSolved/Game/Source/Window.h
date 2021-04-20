#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class Window : public Module
{
public:
	// Constructor
	Window();

	// Destructor
	virtual ~Window();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Changes the title
	void SetTitle(const char* title);

	// Retrives the window size
	void GetWindowSize(uint& width, uint& height) const;

	// Retrieves the window scale
	uint GetScale() const;

public:
	// The window we'll be rendering to
	SDL_Window* window;

	// The surface contained by the window
	SDL_Surface* screenSurface;

private:
	SString title;
	uint width;
	uint height;
	uint scale;
};
#endif // __WINDOW_H__