#pragma once
#include "Header.h"

View view;//объявили sfml объект "вид", который и является камерой

class Camera{

private:
	float cLefterX, cRighterX, cUpperY, cDownerY;
	Sprite sprite;
public:

	float SetCLefterX(float X)
	{
		cLefterX = X;
		return cLefterX;
	}
	float SetCRighterX(float X)
	{
		cRighterX = X;
		return cRighterX;
	}
	float SetCUpperY(float Y)
	{
		cUpperY = Y;
		return cUpperY;
	}
	float SetCDownerY(float Y)
	{
		cDownerY = Y;
		return cDownerY;
	}

	float GetCLefterX()
	{
		return cLefterX;
	}
	float GetCRighterX()
	{
		return cRighterX;
	}
	float GetCUpperY()
	{
		return cUpperY;
	}
	float GetCDownerY()
	{
		return cDownerY;
	}

	void GetPlayerCoordView(float x, float y)
	{
		float tempX = x; float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края

		if (x < cLefterX) tempX = cLefterX;//убираем из вида левую сторону
		if (x > cRighterX) tempX = cRighterX;//убираем из вида правую сторону
		if (y < cUpperY) tempY = cUpperY;//верхнюю сторону
		if (y > cDownerY) tempY = cDownerY;//нижнюю сторону	
		view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты
		sprite.setPosition(x, y); //следим за игроком, передавая его координаты камере.
	}
};