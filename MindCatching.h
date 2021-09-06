#pragma once
#include "Person.h"

class MindCatching : public Person
{
	bool shine = false;
	bool startShine = false;
public:
	void shineHorns()
	{
		if (!shine)
			shine = true;
	}
	bool isStartShine() const
	{
		return startShine;
	}
	void update(float time) override
	{
		if (rect.left + dx*time > 10 && rect.left + dx*time + rect.width < xScreen - 10)
			rect.left += dx*time;
		if (shine)
		{
			if (currentFrame == 0)
				startShine = true;
			else startShine = false;
		}
		if (shine)
		{
			currentFrame += 0.005*time;
			if (currentFrame > 14)
			{
				currentFrame = 0;
				shine = false;
			}
			else sprite.setTextureRect(IntRect(rect.width * int(currentFrame), 0, rect.width, rect.height));
		}
		else sprite.setTextureRect(IntRect(0, 0, rect.width, rect.height));
		sprite.setPosition(rect.left, rect.top);
	}
	void teleportFromPlay(size_t i)
	{
		sprite.setTextureRect(IntRect(rect.width * int(i), rect.height, rect.width, rect.height));
	}
};
