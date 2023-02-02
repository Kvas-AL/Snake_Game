#include "GameLoop.h"

void GameLoop()
{
	Window window;
	if (!window.Init())
	{
		std::cout << "Faild to initialize!\n";
	}
	else
	{
		srand(time(NULL));

		bool quit = false;

		SDL_Event event;
		Snake snake;
		Apple apple;

		uint64_t timerEnd = SDL_GetTicks64();
		float frameTime = 0.f;
		float updateTime = 0.07f;

		snake.LoadTexture(window.GetRenderer());
		apple.LoadTexture(window.GetRenderer());

		while (!quit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
				snake.HandleEvent(event);
			}
			uint64_t timerStart = SDL_GetTicks64();

			float deltaTime = (timerStart - timerEnd) / 1000.f;
			frameTime += deltaTime;

			if (frameTime >= updateTime)
			{
				snake.Move();
				snake.CollisionDetection(apple);

				frameTime = 0.f;
			}

			timerEnd = SDL_GetTicks64();

			// Displaying the game score on the window title
			std::string Score = "Snake Score: " + std::to_string(snake.GetSnakeSize() * 100);
			SDL_Window* Window = window.GetWindow();
			SDL_SetWindowTitle(Window, Score.c_str());

			SDL_SetRenderDrawColor(window.GetRenderer(), 0x00, 0x33, 0x66, 0xFF);
			SDL_RenderClear(window.GetRenderer());

			snake.Render(window.GetRenderer());
			apple.Render(window.GetRenderer());

			SDL_RenderPresent(window.GetRenderer());
		}
	}
}