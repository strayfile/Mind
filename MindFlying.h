#pragma once
#include "Person.h"

class MindFlying : public Person
{
public:
	void update(float time) override
	{
		if ((dir == 2 || dir == 3) && !onGround)
			dy = dy + 0.00089*time;

		rect.top += dy*time;

		if ((rect.top + rect.height > ground2))
		{
			rect.top = ground2 - rect.height;
			dy = 0;
			onGround = true;
		}
		else if ((rect.top + rect.height < ground1))
		{
			rect.top = ground1 - rect.height;
			dy = 0;
			onGround = true;
		}
		if ((rect.top + rect.height < ground2) && (rect.top + rect.height > ground1))
		{
			onGround = false;
		}

		sprite.setPosition(rect.left, rect.top);
	}
};
