#pragma once
#include "stdafx.h"
#include "App/app.h"
#include "App/SimpleSprite.h"
#include "Asteroid.h"
#include <stdlib.h>

Asteroid::Asteroid(const char* filename, float x, float y, float r, float s) {
	m_sprite = App::CreateSprite(filename, 1, 1);
	m_sprite->SetFrame(0);
	m_pos[0] = x;
	m_pos[1] = y;
	m_angle = r;
	m_background = nullptr;
	m_sprite->SetScale(0.5f);
	m_speed = s;
}

void Asteroid::RenderAsteroid() {
	m_sprite->Draw();
}

void Asteroid::AssignBackground(CSimpleSprite* background) {
	m_background = background;
}

void Asteroid::SetPosition(float x, float y) {
	m_pos[0] = x;
	m_pos[1] = y;
}

void Asteroid::GetPosition(float& x, float& y) {
	x = m_pos[0];
	y = m_pos[1];
}

void Asteroid::SetAngle(float r) {
	m_angle = r;
}

float Asteroid::GetAngle() {
	return m_angle;
}

void Asteroid::Update(float dt) {
	float backx, backy;
	m_background->GetPosition(backx, backy);
	m_pos[0] += m_speed * sin(m_angle);
	m_pos[1] -= m_speed * cos(m_angle);
	m_sprite->SetPosition(backx - m_pos[0], backy - m_pos[1]);
	m_sprite->SetAngle(m_angle);
	m_sprite->Update(dt);
}

void Asteroid::DeleteSprite() {
	delete m_sprite;
}