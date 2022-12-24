#pragma once
#include "Object.h"

class Apple : public Object
{
public:

	void LoadTexture(SDL_Renderer* Renderer);

	void SetRandomPosition();

	void Render(SDL_Renderer* Renderer);
};