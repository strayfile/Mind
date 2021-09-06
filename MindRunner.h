#pragma once
#include "Person.h"

class MindRunner : public Person
{
	float fJump = 0;
public:
	bool onGround;
	void update(float time) override
	{
		if (!onGround)
			dy = dy + 0.00089*time;
		rect.top += dy*time;
		if (rect.top + rect.height < ground)
			onGround = false;
		else if (rect.top + rect.height > ground)
		{
			rect.top = ground - rect.height;
			dy = 0;
			onGround = true;
			fJump = 0;
		}
		if (onGround)
		{
			currentFrame += 0.005*time;
			if (currentFrame > frames)
				currentFrame -= frames;
			if (dx > 0 && onGround)
			{

				if (currentFrame < frames / 2)
					sprite.setTextureRect(IntRect(rect.width * int(currentFrame), 0, rect.width, rect.height));
				else
					sprite.setTextureRect(IntRect(rect.width * (int(currentFrame) - frames / 2), rect.height, rect.width, rect.height));
			}
		}
		else if (dx > 0 && !onGround)
		{
			fJump += 0.005*time;
			if (fJump > 18)
				fJump -= 18;
			sprite.setTextureRect(IntRect(rect.width * int(fJump), rect.height * 2, rect.width, rect.height));
		}
		sprite.setPosition(rect.left, rect.top);
	}
	void teleportFromPlay(size_t i)
	{
		sprite.setTextureRect(IntRect(rect.width * int(i), rect.height * 5, rect.width, rect.height));
	}
};
