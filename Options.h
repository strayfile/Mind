#pragma once
#include "Header.h"

void Options(RenderWindow &window, MenuItems& m, Music & music)
{
	m.menuS[5].setPosition(0, yScreen - m.menuS[5].getTextureRect().height);
	Texture v1, v2;
	v1.loadFromFile("resources/0/volume1.png");
	v2.loadFromFile("resources/0/volume2.png");
	Sprite sv1(v1), sv2(v2);
	sv1.setPosition((xScreen / 2) - 200, yScreen / 2); //полоса громкости
	sv2.setPosition((xScreen / 2) - 210, (yScreen / 2) - 10); //уровень громкости
	int menuNum = -1;
	while (true)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				float mus = music.getVolume();
				if (event.key.code == Keyboard::Key::Left || event.key.code == Keyboard::Key::A)
				{
					if (sv2.getPosition().x > (xScreen / 2) - 200) {

						sv2.setPosition(sv2.getPosition().x - 39.3f, (yScreen / 2) - 10);
						if (music.getVolume() - 11.1 < 0)
							music.setVolume(0);
						else music.setVolume(music.getVolume() - 11.1);

					}
				}
				else if (event.key.code == Keyboard::Key::Right || event.key.code == Keyboard::Key::D)
				{
					if (sv2.getPosition().x < (xScreen / 2) + 130){
						sv2.setPosition(sv2.getPosition().x + 39.3f, (yScreen / 2) - 10);
						float mus1 = music.getVolume() + 11.1;
						music.setVolume(mus1);
						mus = (int)music.getVolume();
						mus = 1;
					}
				}
			}
		}
		if (IntRect(0, yScreen - m.menuS[5].getTextureRect().height, m.menuS[5].getTextureRect().width, m.menuS[5].getTextureRect().height).contains(Mouse::getPosition(window))) //если стрелка наведена на пункт выхода
		{
			m.menuS[5].setTexture(m.menu2T[5]); //установить соответствующую текстуру
			menuNum = 0;
		}
		else
		{
			m.menuS[5].setTexture(m.menu1T[5]);
			menuNum = -1;
		}
		if (Mouse::isButtonPressed(Mouse::Left))
			if (menuNum == 0) //выход
				break;

		window.draw(m.mBgS[1]);
		window.draw(m.menuS[5]);
		window.draw(sv1);
		window.draw(sv2);
		window.display();
		Sleep(10);
	}
}