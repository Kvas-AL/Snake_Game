#include "Snake.h"

Snake::Snake() : m_MoveDirection(UP), m_VelX(0), m_VelY(0), m_SnakeSize(0)
{
	m_PosX = SCREEN_WIDTH / 2;
	m_PosY = SCREEN_HEIGHT / 2;
}

Snake::~Snake()
{
	Restart();
}

int Snake::GetSnakeSize()
{
	return m_SnakeSize;
}

void Snake::LoadTexture(SDL_Renderer* Renderer)
{
	m_Texture.LoadFromFile("Data\\SnakeSprite.png", Renderer);
	m_BodyTexture.LoadFromFile("Data\\BodySprite.png", Renderer);

	m_Width = m_Texture.GetWidth();
	m_Height = m_Texture.GetHeight();
}

void Snake::HandleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP: m_MoveDirection != DOWN ? m_MoveDirection = UP : m_MoveDirection = DOWN; break;
		case SDLK_DOWN: m_MoveDirection != UP ? m_MoveDirection = DOWN : m_MoveDirection = UP; break;
		case SDLK_LEFT: m_MoveDirection != RIGTH ? m_MoveDirection = LEFT : m_MoveDirection = RIGTH; break;
		case SDLK_RIGHT: m_MoveDirection != LEFT ? m_MoveDirection = RIGTH : m_MoveDirection = LEFT; break;
		}
	}
}

void Snake::Move()
{
	SDL_Point PrevPoint = { m_PosX,m_PosY };
	m_RenderPoints.emplace_front(PrevPoint, m_MoveDirection);

	m_VelX = 0, m_VelY = 0;
	switch (m_MoveDirection)
	{
	case UP: m_VelY -= m_SnakeVel; break;
	case DOWN: m_VelY += m_SnakeVel; break;
	case LEFT: m_VelX -= m_SnakeVel; break;
	case RIGTH: m_VelX += m_SnakeVel; break;
	}

	m_PosX += m_VelX;
	m_PosY += m_VelY;
}

void Snake::CollisionDetection(Apple& Apple)
{
	// Snake&Walls
	if (m_PosX < 0 || m_PosX > SCREEN_WIDTH - m_Width
		|| m_PosY < 0 || m_PosY > SCREEN_HEIGHT - m_Height)
	{
		Restart();
	}

	// Snake&Snake Body
	for (auto point = m_RenderPoints.begin(); point != m_RenderPoints.end(); ++point)
	{
		if (point != m_RenderPoints.begin())
		{
			if (m_PosX == point->first.x && m_PosY == point->first.y)
			{
				Restart();
				break;
			}
		}
	}

	// Snake&Apple
	if (!(m_PosY + m_Height <= Apple.GetPosY() || m_PosY >= Apple.GetPosY() + Apple.GetHeight() || m_PosX + m_Width <= Apple.GetPosX() || m_PosX >= Apple.GetPosX() + Apple.GetWidth()))
	{
		++m_SnakeSize;

		bool CorrectApplePosition = false;

		// Increases snake size and checks for apple spawn. If the apple appeared on the snake's body, the spawn location is reselected
		while (!(CorrectApplePosition))
		{
			Apple.SetRandomPosition();

			for (auto i = m_RenderPoints.begin(); i != m_RenderPoints.end(); ++i)
			{
				if (!(i->first.y + m_Height <= Apple.GetPosY() || i->first.y >= Apple.GetPosY() + Apple.GetHeight() || i->first.x + m_Width <= Apple.GetPosX() || i->first.x >= Apple.GetPosX() + Apple.GetWidth()))
				{
					CorrectApplePosition = false;
					break;
				}
				else
				{
					CorrectApplePosition = true;
				}
			}
		}
	}
}

void Snake::Restart()
{
	m_MoveDirection = UP;
	m_VelX = 0;
	m_VelY = 0;
	m_SnakeSize = 0;
	m_PosX = SCREEN_WIDTH / 2;
	m_PosY = SCREEN_HEIGHT / 2;

	m_RenderPoints.clear();
}

void Snake::Render(SDL_Renderer* Renderer)
{
	while (m_RenderPoints.size() > m_SnakeSize + 1)
	{
		m_RenderPoints.pop_back();
	}

	for (auto point = m_RenderPoints.begin(); point != m_RenderPoints.end(); ++point)
	{
		if (point == m_RenderPoints.begin())
		{
			m_Texture.Render(point->first.x, point->first.y, Renderer, NULL, point->second, NULL, SDL_FLIP_NONE);
		}
		else
		{
			m_BodyTexture.Render(point->first.x, point->first.y, Renderer, NULL, point->second, NULL, SDL_FLIP_NONE);
		}
	}
}