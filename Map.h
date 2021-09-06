#pragma once
#include "Header.h"

class Map
{
public:
	Image image;
	Sprite sprite1;
	Map() = default;
	virtual void update(float time){}
};

class RunnerMap : public Map
{
public:
	double dx, w;
	int dir = 0;
	FloatRect rect1, rect2;
	Image image;
	Sprite sprite2;
	RunnerMap(Texture & t, float W, float H)
	{
		sprite1.setTexture(t);
		sprite2.setTexture(t);
		rect1.left = 0; rect2.left = rect1.left + W;
		dx = 0;
		w = W;
		sprite1.setTextureRect(IntRect(rect1.left, 0, W, H));
		sprite2.setTextureRect(IntRect(0, 0, W, H));
	}

	virtual void update(float time) override
	{
		if (rect1.left + w > xScreen && rect1.left < -1500)
			rect2.left = rect1.left + w;
		else if (rect2.left + w > xScreen && rect2.left < -1500)
			rect1.left = rect2.left + w;
		if (dir == 1)
		{
			dx = -0.16;
			rect1.left += dx*time;
			rect2.left += dx*time;
		}
		sprite1.setPosition(rect1.left, 0);
		sprite2.setPosition(rect2.left, 0);
	}
};
class CatchingMap : public Map
{
public:
	CatchingMap(Texture & t, float W, float H)
	{
		sprite1.setTexture(t); //загрузка текстуры фона
		sprite1.setTextureRect(IntRect(0, 0, W, H));
		sprite1.setPosition((xScreen - sprite1.getTextureRect().width) / 2, 0.0); //установка позиции фона
	}
};

class FlyingMap : public Map
{
public:
	float dx, dy, w, h;
	bool dir = 0;
	FloatRect rect1, rect2;
	Image image;
	Texture texture;
	Sprite sprite1, sprite2;

	FlyingMap(Texture & t, float W, float H)
	{
		sprite1.setTexture(t);
		sprite2.setTexture(t);
		rect1.left = 0; rect2.left = rect1.left + W;
		dx = 0; dy = 0;
		w = W; h = H;
		sprite1.setTextureRect(IntRect(rect1.left, 0, W, H));
		sprite2.setTextureRect(IntRect(0, 0, W, H));
	}

	virtual void update(float time) override
	{
		if (rect1.left + w > xScreen && rect1.left < -1500)
			rect2.left = rect1.left + w;
		else if (rect2.left + w > xScreen && rect2.left < -1500)
			rect1.left = rect2.left + w;
		if (dir == 1)
		{
			dx = -0.16f;
			rect1.left += dx*time;
			rect2.left += dx*time;
		}
		sprite1.setPosition(rect1.left, 0);
		sprite2.setPosition(rect2.left, 0);
	}
};