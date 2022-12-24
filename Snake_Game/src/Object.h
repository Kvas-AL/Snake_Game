#pragma once
#include <SDL.h>
#include <iostream>
#include "TextureWrapper.h"
#include "Window.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Object
{
public:

	Object();

	void SetPosX(int x);
	void SetPosY(int y);

	TextureWrapper& GetTexture();
	int GetPosX();
	int GetPosY();
	int GetWidth();
	int GetHeight();

protected:
	TextureWrapper m_Texture;
	int m_PosX, m_PosY;
	int m_Width, m_Height;
};