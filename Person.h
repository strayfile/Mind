#pragma once
#include "Header.h"

class Person
{
	bool life = true;
public:
	float dx, dy;
	int dir = 0;
	FloatRect rect;
	string file;
	Image image;
	Texture texture;
	Sprite sprite;
	float currentFrame = 0;
	int frames;
	bool onGround;
	Person() = default;
	void setTexture(string f, float x, float y, float W, float H, int fr)
	{
		file = f;
		image.loadFromFile(file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);	
		rect.left = x; rect.top = y;
		rect.width = W; rect.height = H;
		dx = 0; dy = 0;
		frames = fr;
		sprite.setTextureRect(IntRect(0, 0, W, H));
	}

	virtual void update(float time){};

	bool isLive() const
	{
		return life;
	}
	void setLife(bool l)
	{
		life = l;
	}
};
