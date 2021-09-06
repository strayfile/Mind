#pragma once
#include "Header.h"

View view;//�������� sfml ������ "���", ������� � �������� �������

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
		float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

		if (x < cLefterX) tempX = cLefterX;//������� �� ���� ����� �������
		if (x > cRighterX) tempX = cRighterX;//������� �� ���� ������ �������
		if (y < cUpperY) tempY = cUpperY;//������� �������
		if (y > cDownerY) tempY = cDownerY;//������ �������	
		view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������
		sprite.setPosition(x, y); //������ �� �������, ��������� ��� ���������� ������.
	}
};