#pragma once
#include "Header.h"

class Barrier
{
public:
	double dx, dy;
	int dir = 0;
	short d = 0;
	FloatRect rect;
	Sprite sprite;

	Barrier(){};
	void setTexture(Texture& texture, int y, float W, float H, size_t level)
	{
		sprite.setTexture(texture);
		if (level == 1)
		{
			rect.left = xScreen + 10;
			rect.top = ground - y;
		}
		else if (level == 2)
		{
			rect.left = y;
			rect.top = -500;
		}
		dx = 0; dy = 0;
		rect.width = W; rect.height = H;
		sprite.setTextureRect(IntRect(0, 0, W, H));
	}
	void setTextureForFlying(Texture& texture, float W, float H, int ground)
	{
		sprite.setTexture(texture);
		rect.left = xScreen + 10; rect.top = ground - H;
		dx = 0; dy = 0;
		rect.width = W; rect.height = H;
		sprite.setTextureRect(IntRect(0, 0, W, H));
	}
	virtual void update(float time, size_t level)
	{
		if (dir == 1)
		{
			if (level == 1 || level == 3)
			{
				dx = -0.16;
				rect.left += dx*time;
			}
			else if (level == 2)
			{
				dy = +0.1;
				rect.top += dy*time;
			}
		}
		sprite.setPosition(rect.left, rect.top);
	}
};