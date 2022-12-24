#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class TextureWrapper
{
public:

	TextureWrapper();
	~TextureWrapper();

	SDL_Texture* GetTexture();
	int GetWidth();
	int GetHeight();

	bool LoadFromFile(std::string path, SDL_Renderer* Renderer);

	void Render(int x, int y, SDL_Renderer* Renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

	void Free();

private:
	SDL_Texture* m_Texture;
	int m_Width, m_Height;
};