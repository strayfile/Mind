#include "MenuPlanets.h"


int _tmain(int argc, _TCHAR* argv[])
{
	srand(unsigned(time(0)));
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	RenderWindow window(VideoMode(xScreen, yScreen), "Mind", Style::Titlebar | Style::Close);

	Image icon;
	icon.loadFromFile("resources/icon.png");
	window.setIcon(32, 32, icon.getPixelsPtr());

	MenuItems m;
	Planets planets;
	vector<int> mRectX{ (xScreen / 2) - 270, (xScreen / 2) - 120, (xScreen / 2) + 20, (xScreen / 2) + 170 };
	vector<int> mRectY{ (yScreen / 3) + 50, (yScreen / 3), (yScreen / 3), (yScreen / 3) + 50 };

	for (size_t i = 0; i < 4; i++)
		m.menuS[i].setPosition(mRectX[i], mRectY[i]);
	m.mBgS[0].setPosition((xScreen - m.mBgS[0].getTextureRect().width) / 2, 0); //спрайт фона меню

	bool isMenu = 1;
	size_t menuNum = 0;

	Music music;
	music.openFromFile("resources/music.ogg");//загружаем файл
	music.play();//воспроизводим музыку
	music.setLoop(true);
	music.setVolume(0);

	while (true){
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed || isMenu == false)
					window.close();
				else if (event.type == Event::KeyPressed)
					if (event.key.code == Keyboard::Key::Escape)
						window.close();
			}
			for (size_t i = 0; i < 4; i++)
			{
				if (IntRect(mRectX[i] - 20, mRectY[i] - 10, 100, 100).contains(Mouse::getPosition(window))) //если стрелка наведена на пункт меню
				{
					m.menuS[i].setTexture(m.menu2T[i]); //установить соответствующую текстуру
					menuNum = i + 1; //пункт меню
					break;
				}
				else
				{
					m.menuS[i].setTexture(m.menu1T[i]);
					menuNum = 0; //пункт меню не выбран
				}
			}

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menuNum != 0) //очистка экрана перед переходом к подменю
					window.clear();
				if (menuNum == 1) //меню уровней
					MenuPlanets(window, m, planets);
				else if (menuNum == 2) //настройки
					Options(window, m, music);
				else if (menuNum == 3) //помощь
					Help(window, m);
				else if (menuNum == 4) //выход
					isMenu = false;

				if (menuNum > 0) //при переходе к меню из подменю меняется позиция кнопки выхода
					m.menuS[3].setPosition(mRectX[3], mRectY[3]);
			}
			window.draw(m.mBgS[0]);
			for (size_t i = 0; i <= 3; i++)
				window.draw(m.menuS[i]);
			window.display();
			Sleep(10);
		}
		break;
	}
	return 0;
}


