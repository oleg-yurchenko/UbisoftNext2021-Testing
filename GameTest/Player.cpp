#include "stdafx.h"
#include "Player.h"
#include "App\app.h"
#include <math.h>
#include <vector>

Player::Player(const char* shipname, const char* bulletname, int columns, int rows, int lives) {
	m_sprite = App::CreateSprite(shipname, columns, rows);
	m_bulletname = (char*)bulletname;
	m_lives = lives;
	m_pos[0] = 0.0f;
	m_pos[1] = 0.0f;
	m_angle = m_sprite->GetAngle();
	m_speed = 0.0f;
	m_moving = false;
	m_background = nullptr;
}

void Player::RenderPlayer() {
	m_sprite->Draw();
}

void Player::AssignBackground(CSimpleSprite *background) {
	m_background = background;
}

void Player::SetPosition(float x, float y) {
	m_sprite->SetPosition(x, y);
}

void Player::MovePlayer(float m) {
	if (m != 0)
		m_moving = true;
	else
		m_moving = false;
	if (m_speed < 2.5f && m_speed > -5.0f)
		m_speed += 0.02 * m;
	float x, y;
	y = m_speed * cos(m_angle);
	x = m_speed * sin(m_angle);
	m_pos[0] -= x;
	m_pos[1] += y;
	//m_sprite->SetPosition(m_pos[0], m_pos[1]);
}

void Player::RotatePlayer(float amt) {
	m_angle += amt;
	m_sprite->SetAngle(m_angle);
}

float Player::GetAngle() {
	return m_angle;
}

int Player::GetLives() {
	return m_lives;
}

void Player::SetLives(int lives) {
	m_lives = lives;
}

void Player::Update(float dt) {
	m_sprite->Update(dt);
	if (m_speed > 0)
		m_speed -= 0.01;
	else if (m_speed < 0)
		m_speed += 0.01;
	if (m_moving)
		this->SetFrame(3);
	else
		this->SetFrame(2);
	if (!m_bullets.empty()) {
		for (int i = 0; i < m_bullets.size(); ++i) {
			if (g_pbulletsx[i] > 955 || g_pbulletsx[i] < -955 || g_pbulletsy[i] > 955 || g_pbulletsy[i] < -955) {
				m_toErase.push_back(i);
			}
			else {
				g_pbulletsx[i] += 10 * sin(m_bullets[i]->GetAngle());
				g_pbulletsy[i] -= 10 * cos(m_bullets[i]->GetAngle());
				m_bullets[i]->SetPosition(m_pos[0] - g_pbulletsx[i] + APP_INIT_WINDOW_WIDTH / 2, m_pos[1] - g_pbulletsy[i] + APP_INIT_WINDOW_HEIGHT / 2);
				m_bullets[i]->Update(dt);
			}
		}
	}
	if (!m_toErase.empty()) {
		for (int i = 0; i < m_toErase.size(); ++i) {
			delete m_bullets[m_toErase[i]];
			m_bullets.erase(m_bullets.begin()+m_toErase[i]);
			g_pbulletsx.erase(g_pbulletsx.begin() + m_toErase[i]);
			g_pbulletsy.erase(g_pbulletsy.begin() + m_toErase[i]);
		}
		m_toErase.clear();
	}
}

void Player::SetFrame(int frame) {
	m_sprite->SetFrame(frame);
}

void Player::SetScale(float scale) {
	m_sprite->SetScale(scale);
}

void Player::DeleteSprite() {
	delete m_sprite;
}

void Player::GetPosition(float &x, float &y) {
	x = m_pos[0];
	y = m_pos[1];
}

void Player::Shoot() {
	m_bullets.push_back(App::CreateSprite(m_bulletname, 1, 1));
	m_bullets.back()->SetAngle(m_angle);
	g_pbulletsx.push_back(m_pos[0] + 40 * sin(m_bullets.back()->GetAngle()));
	g_pbulletsy.push_back(m_pos[1] - 40 * cos(m_bullets.back()->GetAngle()));
	m_bullets.back()->SetPosition(m_pos[0] - g_pbulletsx.back() + APP_INIT_WINDOW_WIDTH / 2, m_pos[1] - g_pbulletsy.back() + APP_INIT_WINDOW_HEIGHT / 2 );
	m_bullets.back()->SetFrame(0);
	m_bullets.back()->SetScale(0.25f);
}

void Player::RenderBullets() {
	if (!m_bullets.empty()) {
		for (auto i : m_bullets) {
			i->Draw();
		}
	}
}

int Player::GetBulletCount() {
	return m_bullets.size();
}