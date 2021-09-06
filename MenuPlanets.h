#pragma once
#include "Header.h"

void MenuPlanets(RenderWindow &window, MenuItems& m, Planets & pl)
{
	vector<int> pRectX{ (xScreen / 16) * 2, (xScreen / 16) * 6, (xScreen / 16) * 9, (xScreen / 16) * 12 };
	vector<int> pRectY{ (yScreen / 10) * 3, (yScreen / 10) * 5, (yScreen / 10) * 2, (yScreen / 10) * 6 };
	
	m.menuS[5].setPosition(0, yScreen - m.menuS[5].getTextureRect().height);
	for (size_t i = 0; i < pl.plCount; i++)
		pl.planetS[i].setPosition(pRectX[i], pRectY[i]);
	pl.SetTextsPosition(pRectX, pRectY);

	int menuNum = -1;
	bool rEx = false;
	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Key::Num1){
					pl.SetPlanetStarsCount(1, 50);
					pl.CheckPlanetStarsToUnlock();
				}
				else if (event.key.code == Keyboard::Key::Num2){
					pl.SetPlanetStarsCount(2, 50);
					pl.CheckPlanetStarsToUnlock();
					pl.catchingEnd = true;
				}
				else if (event.key.code == Keyboard::Key::Num3){
					pl.SetPlanetStarsCount(3, 50);
					pl.CheckPlanetStarsToUnlock();
				}
			}
			else if (event.type == Event::MouseMoved){
				for (size_t i = 0; i < pl.plCount; i++)
				{
					if (IntRect(pRectX[i], pRectY[i], pl.planetS[i].getTextureRect().width, pl.planetS[i].getTextureRect().height).contains(event.mouseMove.x, event.mouseMove.y)) //если стрелка наведена на пункт меню
					{
						pl.SetPlanetTexture(i + 1, true);//установить соответствующую текстуру
						menuNum = i + 1; //пункт меню
						break;
					}
					else
					{
						pl.SetPlanetTexture(i + 1, false);
						menuNum = -1;
					}
					if (i == 0)
					{
						if (IntRect(0, yScreen - m.menuS[5].getTextureRect().height, m.menuS[5].getTextureRect().width, m.menuS[5].getTextureRect().height).contains(event.mouseMove.x, event.mouseMove.y)) //если стрелка наведена на пункт выхода
						{
							m.menuS[5].setTexture(m.menu2T[5]); //установить соответствующую текстуру
							menuNum = 0;
							i = pl.plCount;
						}
						else
						{
							m.menuS[5].setTexture(m.menu1T[5]);
							menuNum = -1;
						}
					}
				}
			}
			else if (event.type == Event::MouseButtonPressed)
			{
				if (menuNum == 0)
					rEx = true;
				else if (menuNum > 0 && menuNum <= 3)
				{
					LevelsMenu lm(menuNum);
					Stars st;
					st.setStarsCount(pl.GetStarsCount(menuNum));
					if (pl.GetStarsCount(menuNum) == 0 && menuNum != 2 && menuNum != 3 && menuNum != 2) //убрать, если нарисуем комикс
					{
						Texture comicsT;
						if (menuNum == 1)
							comicsT.loadFromFile("resources/1/Mind_comics1_en.png");
						//else if (menuNum == 2)
						//	comicsT.loadFromFile("resources/2/Mind_comics2_en.png");
						//else if (menuNum == 3)
						//	comicsT.loadFromFile("resources/3/Mind_comics3_en.png");
						Sprite comicsS(comicsT);
						comicsS.setPosition((xScreen - comicsS.getTextureRect().width) / 2, (yScreen - comicsS.getTextureRect().height) / 2);
						window.clear();
						window.draw(comicsS);
						window.display();
						while (true)
						{
							if (Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Insert))
								break;
							Sleep(10);
						}
					}
					bool p = true;
					while (p)
					{
						if (menuNum == 1) //раннер
							p = Runner(window, st, m, pl.planets[0].IsPlanetFinished());
						else if (menuNum == 2) //ловля животных
							p = Catching(window, st, m, pl.planets[1].IsPlanetFinished(), pl.catchingEnd);
						else if (menuNum == 3) //платформер
						{
							Flying(window, st);
							p = false; //пока что это будет полет между планетами
						}
						pl.SetPlanetStarsCount(menuNum, st.getCount());
						if (!p || lm.LevelMenu(window, m) == 0)
							break;
					}
				}
			}
		}
		if (rEx)
			break;
		
		//if (Mouse::isButtonPressed(Mouse::Left))
		//{
		//	if (menuNum == 0) //выход
		//		break;
		//	else if (menuNum > 0 && menuNum <= 3)
		//	{
		//		LevelsMenu lm(menuNum);
		//		Stars st;
		//		st.setStarsCount(pl.GetStarsCount(menuNum));
		//		if (pl.GetStarsCount(menuNum) == 0 && menuNum != 2 && menuNum != 3 && menuNum != 2) //убрать, если нарисуем комикс
		//		{
		//			Texture comicsT;
		//			if (menuNum == 1)
		//				comicsT.loadFromFile("resources/1/Mind_comics1_en.png");
		//			//else if (menuNum == 2)
		//			//	comicsT.loadFromFile("resources/2/Mind_comics2_en.png");
		//			//else if (menuNum == 3)
		//			//	comicsT.loadFromFile("resources/3/Mind_comics3_en.png");
		//			Sprite comicsS(comicsT);
		//			comicsS.setPosition((xScreen - comicsS.getTextureRect().width) / 2, (yScreen - comicsS.getTextureRect().height) / 2);
		//			window.clear();
		//			window.draw(comicsS);
		//			window.display();
		//			while (true)
		//			{
		//				if (Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Insert))
		//					break;
		//				Sleep(10);
		//			}
		//		}
		//		bool p = true;
		//		while (p)
		//		{
		//			if (menuNum == 1) //раннер
		//				p = Runner(window, st, m, pl.planets[0].IsPlanetFinished());
		//			else if (menuNum == 2) //ловля животных
		//				p = Catching(window, st, m, pl.planets[1].IsPlanetFinished(), pl.catchingEnd);
		//			else if (menuNum == 3) //платформер
		//			{
		//				Flying(window, st);
		//				p = false; //пока что это будет полет между планетами
		//			}
		//			pl.SetPlanetStarsCount(menuNum, st.getCount());
		//			if (!p || lm.LevelMenu(window, m) == 0)
		//				break;
		//		}
		//	}
		//	Sleep(10);
		//}
		pl.update();
		pl.SetTextsPosition(pRectX, pRectY);

		window.draw(m.mBgS[1]);
		for (size_t i = 0; i < pl.plCount; i++)
			window.draw(pl.planetS[i]);
		window.draw(m.menuS[5]);
		window.draw(pl.starsText);
		window.display();
		Sleep(10);
	}
	pl.WriteStarsToFile();
}