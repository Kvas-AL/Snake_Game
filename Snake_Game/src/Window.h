#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 800;

class Window
{
public:
	Window();
	~Window();

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();

	bool Init();

private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
};