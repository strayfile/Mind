#pragma once
#include "Header.h"

#pragma comment(lib,"User32.lib")
//int xScreen = (GetSystemMetrics(SM_CXSCREEN) / 100) * (768 / (GetSystemMetrics(SM_CYSCREEN) / 100));
int xScreen = 1366;
int yScreen = 768;
int ground = (yScreen / 100) * 94;
int ground1 = (yScreen - yScreen / 100 * 20) / 2;
int ground2 = yScreen - yScreen / 100 * 20;

class MenuItems
{
public:
	vector<Texture> menu1T, menu2T, mBgT;
	vector<Sprite> menuS, mBgS;
	Font font;

	MenuItems()
	{
		//текстуры
		Texture mT;
		for (size_t i = 0; i < 6; i++)
		{
			menu1T.push_back(mT); //кнопки меню 1й вариант
			menu2T.push_back(mT); //кнопки меню 2й вариант
			if (i < 5) //фоны
				mBgT.push_back(mT);
		}
		menu1T[0].loadFromFile("resources/0/Play1.png");
		menu1T[1].loadFromFile("resources/0/Options1.png");
		menu1T[2].loadFromFile("resources/0/Help1.png");
		menu1T[3].loadFromFile("resources/0/Exit1.png");
		menu1T[4].loadFromFile("resources/0/Restart1.png");
		menu1T[5].loadFromFile("resources/00/Home1.png");
		menu2T[0].loadFromFile("resources/0/Play2.png");
		menu2T[1].loadFromFile("resources/0/Options2.png");
		menu2T[2].loadFromFile("resources/0/Help2.png");
		menu2T[3].loadFromFile("resources/0/Exit2.png");
		menu2T[4].loadFromFile("resources/0/Restart2.png");
		menu2T[5].loadFromFile("resources/00/Home2.png");

		mBgT[0].loadFromFile("resources/0/Menu.png"); //фон меню
		mBgT[1].loadFromFile("resources/00/PlanetsM.png"); //фон меню планет
		mBgT[2].loadFromFile("resources/00/middleMenu.png"); //фон промежуточных меню
		mBgT[3].loadFromFile("resources/1/mapRunner.png"); //фон раннера
		mBgT[4].loadFromFile("resources/2/mapCatching.png"); //фон ловли животных

		font.loadFromFile("resources/0/font.ttf"); //шрифт кол-ва звезд и времени

		//спрайты
		Sprite mS;
		for (size_t i = 0; i < 6; i++) //загрузка 1й версии текстур для кнопок меню
		{
			menuS.push_back(mS);
			menuS[i].setTexture(menu1T[i]);
		}
		for (size_t i = 0; i < 5; i++) //загрузка фонов в спрайты
		{
			mBgS.push_back(mS);
			mBgS[i].setTexture(mBgT[i]);
		}
	}
};

class LevelsMenu
{
	size_t level;
	int mX[2];
	float Y;
public:
	LevelsMenu(size_t l)
	{
		level = l;
		mX[0] = (xScreen / 2) - 120; //коорд х для кнопки выхода
		mX[1] = (xScreen / 2) + 10; //коорд х для кнопки рестарта
		Y = (yScreen / 3); //коорд y для кнопок
	}

	bool LevelMenu(RenderWindow &window, MenuItems &m)
	{
		window.clear();
		m.menuS[3].setPosition(mX[0], Y); //установка позиций для кнопок
		m.menuS[4].setPosition(mX[1], Y);
		m.mBgS[2].setPosition((xScreen - m.mBgS[2].getTextureRect().width) / 2, 0.0); //установка позиции фона
		size_t menuNum = 0;
		int r = -1;
		while (window.isOpen()){
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::MouseMoved){
					for (size_t i = 0, j = 3; i < 2; i++, j++)
					{
						if (IntRect(mX[i], Y, 100, 100).contains(event.mouseMove.x, event.mouseMove.y))
						{
							m.menuS[j].setTexture(m.menu2T[j]); //установить соответствующую текстуру
							menuNum = i + 1; //пункт меню
							break;
						}
						else
						{
							m.menuS[j].setTexture(m.menu1T[j]); //установить соответствующую текстуру
							menuNum = 0; //пункт меню не выбран
						}
					}
				}
				if (event.type == Event::MouseButtonPressed)
				{
					if (menuNum == 1) //выход
						r = 0;
					else if (menuNum == 2)//рестарт
						r = 1;
					if (menuNum == 1 || menuNum == 2)
						break;
				}
			}
			window.clear();
			window.draw(m.mBgS[2]);
			for (size_t i = 3; i <= 4; i++)
				window.draw(m.menuS[i]);
			window.display();
			if (r == 0)
				return 0;
			else if (r == 1)
				return 1;
			Sleep(10);
		}

		//while (window.isOpen())
		//{
		//	for (size_t i = 0, j = 3; i < 2; i++, j++)
		//	{
		//		if (IntRect(mX[i], Y, 100, 100).contains(Mouse::getPosition(window)))
		//		{
		//			m.menuS[j].setTexture(m.menu2T[j]); //установить соответствующую текстуру
		//			menuNum = i + 1; //пункт меню
		//			break;
		//		}
		//		else
		//		{
		//			m.menuS[j].setTexture(m.menu1T[j]); //установить соответствующую текстуру
		//			menuNum = 0; //пункт меню не выбран
		//		}
		//	}
		//	if (Mouse::isButtonPressed(Mouse::Left))
		//	{
		//		if (menuNum == 1) //выход
		//			r = 0;
		//		else if (menuNum == 2)//рестарт
		//			r = 1;
		//	}
		//	window.clear();
		//	window.draw(m.mBgS[2]);
		//	for (size_t i = 3; i <= 4; i++)
		//		window.draw(m.menuS[i]);
		//	window.display();
		//	if (r != -1)
		//		return r;
		//	Sleep(10);
		//}
		return r;
	}
};

class Planet
{
	bool unlocked = false;
	bool finished = false;
public:
	void SetTexture(size_t numberOfPlanet, Sprite & s, vector<Texture> & t)
	{
		if (IsPlanetUnlocked())
			s.setTexture(t[numberOfPlanet]);
		else s.setTexture(t[0]);
		if (numberOfPlanet == 3 && unlocked)
			s.setTextureRect(IntRect(0, 0, 209, 160));
	}
	bool IsPlanetUnlocked() const
	{
		return unlocked;
	}
	void Unlock()
	{
		unlocked = true;
	}
	void Finish()
	{
		finished = true;
	}
	bool IsPlanetFinished() const
	{
		return finished;
	}
};

class Planets
{
	vector<int> stars;  //кол-во набранных звезд в уровнях
	vector<Texture> planetsT1, planetsT2; //текстуры планет
	Font font;
public:
	size_t plCount = 4; //количество планет
	vector<Sprite> planetS; //спрайты планет
	vector<Planet> planets;
	Text starsText;
	bool catchingEnd = false;
	Planets()
	{
		int st = 0;
		for (size_t i = 0; i < plCount; i++)
			stars.push_back(st); //заполняем нулями для дальнейшей перезаписи кол-ва звезд в уровнях

		//текстуры
		Texture mT;
		for (size_t i = 0; i <= plCount; i++)
		{
			planetsT1.push_back(mT); //планеты 1й вариант
			planetsT2.push_back(mT); //планеты 2й вариант
		}
		planetsT1[0].loadFromFile("resources/00/pl.png");
		planetsT1[1].loadFromFile("resources/00/pl1.png");
		planetsT1[2].loadFromFile("resources/00/pl2.png");
		planetsT1[3].loadFromFile("resources/00/pl3.png");
		planetsT1[4] = planetsT1[0];

		planetsT2[0].loadFromFile("resources/00/pl_.png");
		planetsT2[1].loadFromFile("resources/00/pl1_.png");
		planetsT2[2].loadFromFile("resources/00/pl2_.png");
		planetsT2[3].loadFromFile("resources/00/pl3_.png");
		planetsT2[4] = planetsT2[0];

		if (!ReadStarsFromFile())
		{}

		//спрайты
		Sprite p1S;
		Planet pl;
		for (size_t i = 0; i < plCount; i++) //загрузка 1й версии текстур планет
		{
			planetS.push_back(p1S);
			planets.push_back(pl);
		}
		CheckPlanetStarsToUnlock();
		CheckPlanetToFinish();
		planets[0].Unlock();
		for (size_t i = 0; i < plCount; i++)
			planets[i].SetTexture(i + 1, planetS[i], planetsT1);

		font.loadFromFile("resources/0/font.ttf");
		starsText.setString("");
		starsText.setFont(font);
		starsText.setCharacterSize(30);
		starsText.setColor(Color::Black);
		starsText.setStyle(Text::Bold);
	}

	void SetPlanetTexture(size_t numberOfPlanet, bool mouseOn)
	{
		if (mouseOn)
			planets[numberOfPlanet - 1].SetTexture(numberOfPlanet, planetS[numberOfPlanet - 1], planetsT2);
		else planets[numberOfPlanet - 1].SetTexture(numberOfPlanet, planetS[numberOfPlanet - 1], planetsT1);
	}
	void SetPlanetStarsCount(size_t numberOfPlanet, size_t n)
	{
		stars[numberOfPlanet - 1] = n;
	}
	void SetTextsPosition(vector<int> & pRectX, vector<int> & pRectY)
	{
		for (size_t i = 0; i < plCount; i++) //задаем позицию текста для кол-ва звезд на планете
			if (!planets[i].IsPlanetFinished() && planets[i].IsPlanetUnlocked()) //если планета не пройдена, но разблокирована
				starsText.setPosition(pRectX[i] + 45, pRectY[i] + planetS[i].getTextureRect().height);
	}
	void CheckPlanetStarsToUnlock()
	{
		for (size_t i = 1; i < plCount; i++)
			if (!planets[i].IsPlanetUnlocked() && planets[i - 1].IsPlanetFinished())
				planets[i].Unlock();
	}
	void CheckPlanetToFinish()
	{
		for (size_t i = 0; i < plCount; i++)
			if (!planets[i].IsPlanetFinished() && stars[i] >= 50)
				planets[i].Finish();
	}
	void update()
	{
		CheckPlanetToFinish();
		CheckPlanetStarsToUnlock();
		for (size_t i = 0; i < plCount; i++)
		{
			if (!planets[i].IsPlanetFinished() && planets[i].IsPlanetUnlocked())
			{
				ostringstream sText; //строкa для кол-ва звезд
				sText << stars[i] << " / 50";
				starsText.setString(sText.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			}
		}
	}
	size_t GetStarsCount(size_t numberOfPlanet) const
	{
		return stars[numberOfPlanet - 1];
	}

	bool ReadStarsFromFile()
	{
		ifstream fin("resources/levels.bin", ios_base::binary | ios_base::in);
		if (!fin.is_open())
		{
			if (WriteStarsToFile())
				return true;
		}
		for (size_t i = 0; i < plCount; i++)
			fin.read((char*)&stars[i], sizeof(int));
		fin.read((char*)&catchingEnd, sizeof(bool));
		fin.close();
		return true;
	}
	bool WriteStarsToFile()
	{
		ofstream fout("resources/levels.bin", ios_base::binary | ios_base::out);
		if (!fout.is_open())
		{
			return false;
		}
		for (size_t i = 0; i < plCount; i++)
			fout.write((char*)&stars[i], sizeof(int));
		fout.write((char*)&catchingEnd, sizeof(bool));
		fout.close();
		return true;
	}
};


int catchAnimal(FloatRect& rect, vector<Barrier*> & b)
{
	int ind = 0;
	for (auto it : b)
	{
		if (it->rect.top + it->rect.height < yScreen - 10)
		{
			if ((rect.left > it->rect.left && rect.left < it->rect.left + it->rect.width) || (rect.left + rect.width > it->rect.left && rect.left + rect.width < it->rect.left + it->rect.width))
				return ind;
			else if ((it->rect.left > rect.left && it->rect.left < rect.left + rect.width) || (it->rect.left + it->rect.width > rect.left && it->rect.left + it->rect.width < rect.left + rect.width))
				return ind;
		}
		ind++;
	}
	return -1;
}

void barriersGenerator(vector<Barrier*> & b, vector<Texture> & textures, short level)
{
	Barrier * barrier = new Barrier;
	b.push_back(barrier);
	if (level == 1)
	{
		short n = rand() % 4;
		if (n == 0) //камень
			barrier->setTexture(textures[n], 75, 90, 88, 1); //высота по отношению к земле, ширина, высота
		if (n == 1) //шип1
			barrier->setTexture(textures[n], 85, 95, 88, 1);
		if (n == 2) //коряга
			barrier->setTexture(textures[n], 60, 130, 95, 1);
		if (n == 3) //шип2
			barrier->setTexture(textures[n], 80, 66, 95, 1);
	}
	else if (level == 2)
	{
		vector<int> v = { 20, xScreen / 4 + 10, (xScreen / 2) + 10, (xScreen / 4) * 3 };
		short n1 = rand() % 3;
		short n2 = rand() % 4;
		if (n1 == 0) //обломок1
			barrier->setTexture(textures[n1], v[n2], 234, 156, 2);
		if (n1 == 1) //обломок2
			barrier->setTexture(textures[n1], v[n2], 200, 97, 2);
		if (n1 == 2) //обломок3
			barrier->setTexture(textures[n1], v[n2], 228, 220, 2);
	}
}

void animalsGenerator(vector<Barrier*> & b, vector<Texture> & textures)
{
	Barrier * barrier = new Barrier;
	b.push_back(barrier);
	vector<int> v = { 20, xScreen / 4 + 10, (xScreen / 2) + 10, (xScreen / 4) * 3 };
	short n1 = rand() % 3;
	short n2 = rand() % 4;
	if (n1 == 0) //животное1
		barrier->setTexture(textures[n1], v[n2], 160, 187, 2);
	if (n1 == 1) //животное2
		barrier->setTexture(textures[n1], v[n2], 120, 138, 2);
	if (n1 == 2) //животное3
		barrier->setTexture(textures[n1], v[n2], 180, 200, 2);
}

void starsGenerator(Stars & s, Barrier & b, int level)
{
	if (level == 1 && b.rect.left + b.rect.width < xScreen - 200)
		if (s.rects.size() == 0 || s.rects.back()->top > yScreen - 50)
			s.addStar(level);
	if (level == 2 && b.rect.top > 50)
		if (s.rects.size() == 0 || s.rects.back()->top > yScreen - 200)
			s.addStar(level);
}

void barrierDel(vector<Barrier*> & b, short level)
{
	if (level == 1)
	{
		if (b[0]->rect.left + b[0]->rect.width < 0)
		{
			delete b[0];
			b.erase(b.begin());
		}
	}
	if (level == 2)
	{
		if (b[0]->rect.top > yScreen)
		{
			delete b[0];
			b.erase(b.begin());
		}
	}
}

bool isAnimalFell(vector<Barrier*> & b)
{
	if (b[0]->rect.top > yScreen)
	{
		delete b[0];
		b.erase(b.begin());
		return true;
	}
	return false;
}

bool collision(FloatRect rect1, FloatRect rect2, size_t cutFrX, int cutFrY, int rect1W, int rect1H, int rect2W, int rect2H)
{
	int k = 0;
	if ((rect1.left + cutFrX >= rect2.left && rect1.left + cutFrX <= rect2.left + rect2W) && (rect1.top + cutFrY >= rect2.top && rect1.top + cutFrY <= rect2.top + rect2H))
		k++;
	if ((rect1.left - cutFrX + rect1W >= rect2.left && rect1.left - cutFrX + rect1W <= rect2.left + rect2W) && (rect1.top + cutFrY >= rect2.top && rect1.top + cutFrY <= rect2.top + rect2H))
		k++;
	if ((rect1.left + cutFrX >= rect2.left && rect1.left + cutFrX <= rect2.left + rect2W) && (rect1.top - cutFrY + rect1H >= rect2.top && rect1.top - cutFrY + rect1H <= rect2.top + rect2H))
		k++;
	if ((rect1.left - cutFrX + rect1W >= rect2.left && rect1.left - cutFrX + rect1W <= rect2.left + rect2W) && (rect1.top - cutFrY + rect1H >= rect2.top && rect1.top - cutFrY + rect1H <= rect2.top + rect2H))
		k++;
	if (k != 0)
		return 1;
	k = 0;
	if ((rect2.left >= rect1.left + cutFrX && rect2.left <= rect1.left - cutFrX + rect1W) && (rect2.top >= rect1.top + cutFrY && rect2.top <= rect1.top - cutFrY + rect1H))
		k++;
	if ((rect2.left + rect2W >= rect1.left + cutFrX && rect2.left + rect2W <= rect1.left - cutFrX + rect1W) && (rect2.top >= rect1.top + cutFrY && rect2.top <= rect1.top - cutFrY + rect1H))
		k++;
	if ((rect2.left >= rect1.left + cutFrX && rect2.left <= rect1.left - cutFrX + rect1W) && (rect2.top + rect2H >= rect1.top + cutFrY && rect2.top + rect2H <= rect1.top - cutFrY + rect1H))
		k++;
	if ((rect2.left + rect2W >= rect1.left + cutFrX && rect2.left + rect2W <= rect1.left - cutFrX + rect1W) && (rect2.top + rect2H >= rect1.top + cutFrY && rect2.top + rect2H <= rect1.top - cutFrY + rect1H))
		k++;
	if (k != 0)
		return 1;
	else return 0;
}

bool collisionWithBarrier(Person &p, vector<Barrier*> & b, int cutFrX,int cutFrY, int level)
{
	if ((level == 1 && (p.rect.left + p.rect.width) + 100 > b[0]->rect.left) || (level == 2 && p.rect.top - 50 < b[0]->rect.top + b[0]->rect.height))
	{
		for (size_t i = 0; i < b.size(); i++)
			if (collision(p.rect, b[i]->rect, cutFrX, cutFrY, p.rect.width, p.rect.height, b[i]->rect.width, b[i]->rect.height))
				return 1;
	}
	return 0;
}

int collisionWithStar(Person & p, list<FloatRect*> & rects, int cutFrX, int cutFrY, int level)
{
	if ((level == 1 && (p.rect.left + p.rect.width) + 50 >(*rects.begin())->left) || (level == 2 && p.rect.top - 50 < (*rects.begin())->top + (*rects.begin())->height))
	{
		int ind = 0;
		for (auto it : rects)
		{
			if (collision(p.rect, (*it), cutFrX, cutFrY, p.rect.width, p.rect.height, 60.0, 60.0))
				return ind;
			ind++;
		}
	}
	return -1;
}