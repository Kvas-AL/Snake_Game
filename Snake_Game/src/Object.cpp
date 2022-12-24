#include "Object.h"

Object::Object() : m_PosX(0), m_PosY(0), m_Width(0), m_Height(0) {}

void Object::SetPosX(int x)
{
	m_PosX = x;
}
void Object::SetPosY(int y)
{
	m_PosY = y;
}

TextureWrapper& Object::GetTexture()
{
	return m_Texture;
}
int Object::GetPosX()
{
	return m_PosX;
}
int Object::GetPosY()
{
	return m_PosY;
}
int Object::GetWidth()
{
	return m_Width;
}
int Object::GetHeight()
{
	return m_Height;
}