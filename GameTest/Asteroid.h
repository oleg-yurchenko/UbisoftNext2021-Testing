#pragma once
#include "stdafx.h"
#include "App/SimpleSprite.h"

class Asteroid
{
public:
	Asteroid(const char* filename, float x, float y, float r, float s);
	void RenderAsteroid();
	void AssignBackground(CSimpleSprite* background);
	void SetPosition(float x, float y);
	void GetPosition(float& x, float& y);
	void SetAngle(float r);
	float GetAngle();
	void Update(float dt);
	void DeleteSprite();
private:
	CSimpleSprite* m_sprite;
	float m_pos[2];
	float m_angle;
	CSimpleSprite* m_background;
	float m_speed;
};
