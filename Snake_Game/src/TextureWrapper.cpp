#include "TextureWrapper.h"

TextureWrapper::TextureWrapper() : m_Texture(nullptr), m_Width(0), m_Height(0) {}

TextureWrapper::~TextureWrapper()
{
	Free();
}

SDL_Texture* TextureWrapper::GetTexture()
{
	return m_Texture;
}

int TextureWrapper::GetWidth()
{
	return m_Width;
}

int TextureWrapper::GetHeight()
{
	return m_Height;
}

bool TextureWrapper::LoadFromFile(std::string path, SDL_Renderer* Renderer)
{
	bool successful = true;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (!(loadedSurface))
	{
		std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << "\n";
		successful = false;
	}
	else
	{
		m_Texture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
		if (!(m_Texture))
		{
			std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << "\n";
			successful = false;
		}
		else
		{
			m_Width = loadedSurface->w;
			m_Height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	return successful;
}

void TextureWrapper::Render(int x, int y, SDL_Renderer* Renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, m_Width, m_Height };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(Renderer, m_Texture, clip, &renderQuad, angle, center, flip);
}

void TextureWrapper::Free()
{
	if (m_Texture)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
		m_Width = 0;
		m_Height = 0;
	}
}