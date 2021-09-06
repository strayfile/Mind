#pragma once
#include "Header.h"

void Help(RenderWindow &window, MenuItems& m)
{
	m.menuS[5].setPosition(0, yScreen - m.menuS[5].getTextureRect().height);
	Texture h;
	h.loadFromFile("resources/0/helpIm.png");
	Sprite sH(h);
	sH.setPosition((xScreen / 2) - 500, 0.0);
	int menuNum = -1;
	bool rEx = false;
	while (true)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::MouseMoved){
				if (IntRect(0, yScreen - m.menuS[5].getTextureRect().height, m.menuS[5].getTextureRect().width, m.menuS[5].getTextureRect().height).contains(event.mouseMove.x, event.mouseMove.y)) //если стрелка наведена на пункт выхода
				{
					m.menuS[5].setTexture(m.menu2T[5]); //установить соответствующую текстуру
					menuNum = 0;
				}
				else
				{
					m.menuS[5].setTexture(m.menu1T[5]);
					menuNum = -1;
				}
			}
			if (event.type == Event::MouseButtonPressed)
			{
				if (menuNum == 0) {
					rEx = true;
					break;
				}
			}
		}
		if (rEx)
			break;
		//if (IntRect(0, yScreen - m.menuS[5].getTextureRect().height, m.menuS[5].getTextureRect().width, m.menuS[5].getTextureRect().height).contains(Mouse::getPosition(window))) //если стрелка наведена на пункт выхода
		//{
		//	m.menuS[5].setTexture(m.menu2T[5]); //установить соответствующую текстуру
		//	menuNum = 0;
		//}
		//else
		//{
		//	m.menuS[5].setTexture(m.menu1T[5]);
		//	menuNum = -1;
		//}
		//if (Mouse::isButtonPressed(Mouse::Left))
		//	if (menuNum == 0) //выход
		//		break;

		window.draw(m.mBgS[1]);
		window.draw(m.menuS[5]);
		window.draw(sH);
		window.display();
		Sleep(10);
	}
}