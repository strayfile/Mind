#pragma once
#include "Header.h"

bool Catching(RenderWindow &window, Stars &stars, MenuItems& mI, bool isGameFinished, bool & AnimCatched)
{
	mI.menuS[3].setPosition(60.0, 20.0); //позиция кнопки выхода

	float CurrentFrame = 0;
	Clock clock;

	Text text1("", mI.font, 60); //текст для собранных звезд
	text1.setColor(Color::Black);
	text1.setStyle(Text::Bold);
	text1.setPosition(xScreen - 150, 20.0);//задаем позицию текста

	Text textAn("", mI.font, 70); //текст для кол-ва пойманных животных
	textAn.setColor(Color::Black);
	textAn.setStyle(Text::Bold);
	textAn.setPosition(200.0, 20.0);//задаем позицию текста

	vector<Texture> tO(3); //текстуры для обломков
	tO[0].loadFromFile("resources/2/obl1.png");
	tO[1].loadFromFile("resources/2/obl2.png");
	tO[2].loadFromFile("resources/2/obl3.png");

	vector<Texture> tZ(3); //текстуры для зверушек
	tZ[0].loadFromFile("resources/2/z1.png");
	tZ[1].loadFromFile("resources/2/z2.png");
	tZ[2].loadFromFile("resources/2/z3.png");

	vector<Barrier*> b; //обломки
	vector<Barrier*> z; //животные

	CatchingMap m(mI.mBgT[4], 1505.0, yScreen); //загрузка фона

	MindCatching p; //Минд, управление и прорисовка
	p.setTexture("resources/2/Mind.png", (xScreen - 258) / 2, yScreen - 358, 258.0, 358.0, 14);  //загрузка текстур

	Clock gameTime;
	size_t gameTS = 0; //время с начала игры в секундах
	float forTime = 220.0; //скорость игры(на нее делится текущее время игры)

	size_t animCount = 0;

	bool rMenu = true; //выход из игры или перезапуск
	gameTime.restart();

	bool rEx = false;
	while (p.isLive()) //пока Минд жива и ни одно животное не упало
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		gameTS = gameTime.getElapsedTime().asSeconds();
		time = time / forTime;

		p.dx = 0;
		if (p.isLive())
		{
			if (animCount >= 30)
				AnimCatched = true;

			short int bg = rand() % 10;
			if (bg == 0)
			{
				if (z.size() == 0 || (z.size() != 0 && (z[z.size() - 1]->rect.top) > 200))
					if (b.size() == 0 || (b.size() != 0 && (b[b.size() - 1]->rect.top) > 400))
						barriersGenerator(b, tO, 2);//генерация обломков
			}
			if (bg == 2)
			{
				if (!AnimCatched) //если уровень с животными не был пройден
				{
					if (animCount < 30)
						if (b.size() == 0 || (b.size() != 0 && (b[b.size() - 1]->rect.top) > 150))
							if (z.size() == 0 || (z.size() != 0 && (z[z.size() - 1]->rect.top) > 200))
								animalsGenerator(z, tZ);//генерация животных
				}
			}
			if (b.size() > 0)
			{
				barrierDel(b, 2); //удаление устаревших преград
				if (bg == 1 && gameTS > stars.getCount() && stars.getCount() < 50 && b.size() != 0)
					if (b[b.size() - 1]->rect.top > 100)
						starsGenerator(stars, *b[b.size() - 1], 2); //генерация звезд
			}
			if (z.size() > 0) //если есть животные
				if(isAnimalFell(z)) //если животное упало
					p.setLife(0); //выход

			if (stars.rects.size() > 0)
				stars.delStar(); //удаление устаревших звезд
			
			for (size_t i = 0; i < b.size(); i++)
				b[i]->dir = p.dir; //направление обломков зависит от направления перса
			for (size_t i = 0; i < z.size(); i++)
				z[i]->dir = p.dir; //падение животных зависит от того, началась ли двигаться Минд
			for (size_t i = 0; i < stars.rects.size(); i++)
				stars.setDir(p.dir);

			if (p.isStartShine()) //если запустилась магия рожек
			{
				int ind = catchAnimal(p.rect, z); //возвращает индекс телепортированного животного
				if (ind != -1) //если животное телепортировано
				{
					delete z[ind]; //очистить память
					z.erase(z.begin() + ind);//удалить из массива
					animCount++;
				}
			}

			if (stars.rects.size() > 0)
			{
				int ind = collisionWithStar(p, stars.rects, 0, 0, 2); //возвращает индекс звезды, с которой произошло столкновение
				if (ind != -1) //если столкновение произошло
				{
					stars.delStar(ind); //удалить звезду по индексу
					stars.plusStar(); //добавить звезду персу на данном уровне
				}
			}


			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Key::Right || event.key.code == Keyboard::Key::D){
						p.dir = 1;
						p.dx = 4;
					}
					if (event.key.code == Keyboard::Key::Left || event.key.code == Keyboard::Key::A){
						p.dir = 1;
						p.dx = -4;
					}
					if (event.key.code == Keyboard::Key::Space  && p.dir != 0){
						p.shineHorns();
					}
				}
				else if (event.type == Event::MouseMoved){
					if (IntRect(mI.menuS[3].getPosition().x, mI.menuS[3].getPosition().y, 100, 100).contains(event.mouseMove.x, event.mouseMove.y)) //если стрелка наведена на пункт выхода
					{
						mI.menuS[3].setTexture(mI.menu2T[3]); //установить соответствующую текстуру
						rEx = true;
					}
					else{
						mI.menuS[3].setTexture(mI.menu1T[3]); //текстура кнопки выхода
						rEx = false;
					}
				}
				if (event.type == Event::MouseButtonPressed)
				{
					if (rEx) {
						p.setLife(0); //выход из раннера
						rMenu = false;
					}
				}
			}

			if (forTime > 150 && gameTS % 20 == 0 && gameTS > 20) //увеличение скорости игры со временем
				forTime -= 0.01;

			p.update(time);
			for (size_t i = 0; i < b.size(); i++) //движение обломков
				b[i]->update(time, 2);

			for (size_t i = 0; i < z.size(); i++) //движение животных
				z[i]->update(time, 2);

			stars.updateStars(time, 2); //движение звезд

			ostringstream timeOrScore; //строки для кол-ва звезд или времени
			if (!isGameFinished)
				timeOrScore << stars.getCount(); //выводится кол-во звезд
			else timeOrScore << gameTS;
			text1.setString(timeOrScore.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 

			if (!AnimCatched)
			{
				ostringstream animC; //строки для кол-ва животных
				if (!AnimCatched)
					animC << animCount << " / 30";
				textAn.setString(animC.str());
			}
			if (b.size() > 0)
				if (collisionWithBarrier(p, b, 15, 80, 2))
					p.setLife(0); //выход

			short fr = 1; //если игра не окончена и телепорт не используется
			if (!p.isLive())
				fr = 16; //кол-во кадров телепорта
			for (short frameTeleport = 0; frameTeleport < fr; frameTeleport++)
			{
				window.clear();
				window.clear();
				window.draw(m.sprite1); //прорисовка всех спрайтов
				if (!p.isLive())
				{
					p.teleportFromPlay(frameTeleport);
					Sleep(20);
				}
				window.draw(p.sprite);
				for (auto it : z)
					window.draw(it->sprite);
				for (auto it : b)
					window.draw(it->sprite);
				for (auto it : stars.sprites)
					window.draw(*it);
				window.draw(text1);
				if (!AnimCatched)
					window.draw(textAn);

				window.draw(mI.menuS[3]);
				window.display();
			}
		}
		else //если игра окончена
		{
			for (auto it : b) //очистка всей выделенной памяти
				delete it;
			b.clear();
			stars.clear();
		}
	}
	window.clear();
	return rMenu; //возвращает выбранный пункт меню(выход / рестарт)
}
