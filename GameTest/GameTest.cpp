/*//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------
CSimpleSprite *testSprite;
CSimpleSprite *testSprite2;
enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	

	testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	testSprite->SetPosition(400.0f, 400.0f);
	float speed = 1.0f / 15.0f;
	testSprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	testSprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	testSprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	testSprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });
	testSprite->SetScale(2.0f);

	testSprite2 = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	testSprite2->SetPosition(400.0f, 400.0f);	
	testSprite2->SetFrame(2);
	testSprite2->SetScale(1.0f);
	//------------------------------------------------------------------------
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite->Update(deltaTime);
	testSprite2->Update(deltaTime);
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		testSprite->SetAnimation(ANIM_RIGHT);
		float x, y;
		testSprite->GetPosition(x, y);
		x += 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_LEFT);
		float x, y;
		testSprite->GetPosition(x, y);
		x -= 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		testSprite->SetAnimation(ANIM_FORWARDS);
		float x, y;
		testSprite->GetPosition(x, y);
		y += 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_BACKWARDS);
		float x, y;
		testSprite->GetPosition(x, y);
		y -= 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{
		testSprite->SetScale(testSprite->GetScale() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
		testSprite->SetScale(testSprite->GetScale() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{
		testSprite->SetAngle(testSprite->GetAngle() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{
		testSprite->SetAngle(testSprite->GetAngle() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		testSprite->SetAnimation(-1);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		testSprite->SetVertex(0, testSprite->GetVertex(0) + 5.0f);
	}
	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		App::PlaySound(".\\TestData\\Test.wav");
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	

	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	static float a = 0.0f;
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	a += 0.1f;
	for (int i = 0; i < 20; i++)
	{

		float sx = 200 + sinf(a + i * 0.1f)*60.0f;
		float sy = 200 + cosf(a + i * 0.1f)*60.0f;
		float ex = 700 - sinf(a + i * 0.1f)*60.0f;
		float ey = 700 - cosf(a + i * 0.1f)*60.0f;
		g = (float)i / 20.0f;
		b = (float)i / 20.0f;
		App::DrawLine(sx, sy, ex, ey,r,g,b);
	}

	//------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite->Draw();
	testSprite2->Draw();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	App::Print(100, 100, "Sample Text");

}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	//------------------------------------------------------------------------
	// Example Sprite Code....
	delete testSprite;
	delete testSprite2;
	//------------------------------------------------------------------------
}*/

#include "stdafx.h"
#include <Windows.h>
#include <math.h>
#include "app\app.h"
#include "Player.h"
#include "App/SimpleSprite.h"
#include "Asteroid.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>

Player* p1;
CSimpleSprite* background;
int timeSinceLastBullet;
std::vector<Asteroid*> asteroids;
std::vector<int> asteroidsToDelete;
int asteroidCount;
const float asteroidRadius = 50.0f;

Asteroid* CreateAsteroid(float x, float r) {
	float y = 0.0f;
	if (rand() % 2)
		x = -x;
	int o = rand() % 4;
	switch (o) {
	case 0:
		y = 940.0f;
		break;
	case 1:
		y = x;
		x = 940.0f;
		break;
	case 2:
		y = -940.0f;
		x = x;
		break;
	case 3:
		x = -940.0f;
		y = x;
		break;
	}
	float pre = rand() % 6 + 3;
	float decimal = rand() % 100;
	pre += decimal / 100;
	return new Asteroid(".\\TestData\\asteroid.bmp", x, y, r, pre);
}

void Init() {
	srand(time(NULL));

	/*Raul's Scuffed Console™*/
	BOOL Monkey;
	Monkey = AllocConsole();
	if (Monkey && IsDebuggerPresent()) {
		freopen("CONOUT$", "w", stdout);
	}
	/*---------------------*/

	p1 = new Player(".\\TestData\\Ships.bmp", ".\\TestData\\Bullet.bmp", 2, 12, 3);
	p1->SetPosition(APP_INIT_WINDOW_WIDTH/2, APP_INIT_WINDOW_HEIGHT/2);
	p1->SetFrame(2);
	p1->SetScale(1.0f);
	timeSinceLastBullet = 0;
	background = new CSimpleSprite(".\\TestData\\background.bmp", 1, 1);
	background->SetPosition(0, 0);
	background->SetFrame(0);
	background->SetScale(15.0f);
	p1->AssignBackground(background);
	asteroidCount = 0;
}

void Update(float dt) {
	while (asteroidCount < 35) {
		float x = rand() % 941;
		float r = rand() % 7;
		asteroids.push_back(CreateAsteroid(x, r));
		asteroids.back()->AssignBackground(background);
		asteroidCount = asteroids.size();
	}
	timeSinceLastBullet++;
	background->Update(dt);
	p1->Update(dt);
	float move = 0.0f;
	float rotate = 0.0f;
	if (App::GetController().GetLeftThumbStickX() > 0.5f) {
		rotate = -App::GetController().GetLeftThumbStickX()/50;
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f) {
		rotate = -App::GetController().GetLeftThumbStickX()/50;
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f) {
		move = App::GetController().GetLeftThumbStickY();
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f) {
		move = App::GetController().GetLeftThumbStickY();
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, false) && timeSinceLastBullet > 30) {
		p1->Shoot();
		timeSinceLastBullet = 0;
	}
	p1->RotatePlayer(rotate);
	p1->MovePlayer(move);
	float posx, posy;
	p1->GetPosition(posx, posy);
	background->SetPosition(posx+APP_INIT_WINDOW_WIDTH/2, posy+APP_INIT_WINDOW_HEIGHT/2);
	for (int i = 0; i < asteroids.size(); ++i) {
		float x, y;
		asteroids[i]->GetPosition(x, y);
		if (x > 955 || x < -955 || y > 955 || y < -955) {
			asteroidsToDelete.push_back(i);
		}
		else if (posx < x+asteroidRadius && posx > x-asteroidRadius && posy < y+asteroidRadius && posy > y-asteroidRadius){
			asteroidsToDelete.push_back(i);
			p1->SetLives(p1->GetLives() - 1);
		}
		else {
			asteroids[i]->Update(dt);
		}
	}
	if (!asteroidsToDelete.empty()) {
		int deleted = 0;
		int lastI = 0;
		for (auto i: asteroidsToDelete) {
			asteroids[i-deleted]->DeleteSprite();
			delete asteroids[i-deleted];
			asteroids.erase(asteroids.begin() + i-deleted);
			if(i > lastI)
				deleted++;
			lastI = i;
		}
		asteroidsToDelete.clear();
	}
	asteroidCount = asteroids.size();
}

void Render() {
	background->Draw();
	p1->RenderBullets();
	p1->RenderPlayer();
	for (auto i : asteroids) {
		i->RenderAsteroid();
	}
	char lives[5];
	_itoa(p1->GetLives(), lives, 10);
	char backx[5];
	char backy[5];
	float x, y;
	App::GetMousePos(x, y);
	_itoa(x, backx, 10);
	_itoa(y, backy, 10);
	App::Print(700, 700, lives);
	App::Print(700, 600, backx);
	App::Print(700, 500, backy);
}

void Shutdown() {
	for (auto i : asteroids) {
		i->DeleteSprite();
		delete i;
	}
	p1->DeleteSprite();
	delete p1;
	delete background;
}