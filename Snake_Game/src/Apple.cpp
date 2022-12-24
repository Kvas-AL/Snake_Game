#include "Apple.h"

void Apple::LoadTexture(SDL_Renderer* Renderer)
{
	m_Texture.LoadFromFile("Data\\AppleSprite.png", Renderer);

	m_Width = m_Texture.GetWidth();
	m_Height = m_Texture.GetWidth();

	SetRandomPosition();
}

void Apple::SetRandomPosition()
{
	m_PosX = m_Width + rand() % ((SCREEN_WIDTH - m_Width) - m_Width + 1);
	m_PosY = m_Height + rand() % ((SCREEN_HEIGHT - m_Height) - m_Height + 1);
}

void Apple::Render(SDL_Renderer* Renderer)
{
	m_Texture.Render(m_PosX, m_PosY, Renderer, NULL, NULL, NULL, SDL_FLIP_NONE);
}