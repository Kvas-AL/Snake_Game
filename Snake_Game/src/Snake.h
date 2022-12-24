#pragma once
#include "Object.h"
#include "Apple.h"
#include <deque>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

enum MoveDirection
{
	UP = 360,
	DOWN = 180,
	LEFT = 270,
	RIGTH = 90
};

class Snake : public Object
{
public:

	Snake();
	~Snake();

	int GetSnakeSize();

	void LoadTexture(SDL_Renderer* Renderer);

	void HandleEvent(SDL_Event& event);

	void Move();

	void CollisionDetection(Apple& Apple);

	void Restart();

	void Render(SDL_Renderer* Renderer);

private:
	const float m_SnakeVel = 10.f;

	int m_SnakeSize;
	int m_VelX, m_VelY;
	TextureWrapper m_BodyTexture;
	MoveDirection m_MoveDirection;
	std::deque<std::pair<SDL_Point, int>> m_RenderPoints;
};