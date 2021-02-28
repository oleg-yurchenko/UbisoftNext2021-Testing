#pragma once
#include "stdafx.h"
#include "App/SimpleSprite.h"
#include <vector>

class Player
{
public:
	Player(const char* shipname, const char* bulletname, int columns, int rows, int lives);
	void RenderPlayer();
	void AssignBackground(CSimpleSprite *background);
	void SetPosition(float x, float y);
	void MovePlayer(float m);
	void RotatePlayer(float amt);
	float GetAngle();
	int GetLives();
	void SetLives(int lives);
	void Update(float dt);
	void SetFrame(int frame);
	void SetScale(float scale);
	void DeleteSprite();
	void GetPosition(float &x, float &y);
	void Shoot();
	void RenderBullets();
	int GetBulletCount();
private:
	CSimpleSprite *m_sprite;
	CSimpleSprite* m_background;
	char* m_bulletname;
	std::vector<CSimpleSprite*> m_bullets;
	std::vector<int> m_toErase;
	std::vector<float> g_pbulletsx;
	std::vector<float> g_pbulletsy;
	int m_lives;
	float m_pos[2];
	float m_angle;
	float m_speed;
	bool m_moving;
};

