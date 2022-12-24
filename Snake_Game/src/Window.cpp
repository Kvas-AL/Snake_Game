#include "Window.h"

Window::Window() :m_Window(nullptr), m_Renderer(nullptr) {}

Window::~Window()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	m_Renderer = nullptr;
	m_Window = nullptr;

	IMG_Quit();
	SDL_Quit();
}

SDL_Window* Window::GetWindow()
{
	return m_Window;
}

SDL_Renderer* Window::GetRenderer()
{
	return m_Renderer;
}

bool Window::Init()
{
	bool successful = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		successful = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Lineral texture filtering not enable!";
		}

		m_Window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (!(m_Window))
		{
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			successful = false;
		}
		else
		{
			m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (!(m_Renderer))
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
				successful = false;
			}
			else
			{
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << "\n";
					successful = false;
				}
			}
		}
	}
	return successful;
}
