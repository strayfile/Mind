#pragma once
#include "Header.h"

bool Catching(RenderWindow &window, Stars &stars, MenuItems& mI, bool isGameFinished, bool & AnimCatched)
{
	mI.menuS[3].setPosition(60.0, 20.0); //������� ������ ������

	float CurrentFrame = 0;
	Clock clock;

	Text text1("", mI.font, 60); //����� ��� ��������� �����
	text1.setColor(Color::Black);
	text1.setStyle(Text::Bold);
	text1.setPosition(xScreen - 150, 20.0);//������ ������� ������

	Text textAn("", mI.font, 70); //����� ��� ���-�� ��������� ��������
	textAn.setColor(Color::Black);
	textAn.setStyle(Text::Bold);
	textAn.setPosition(200.0, 20.0);//������ ������� ������

	vector<Texture> tO(3); //�������� ��� ��������
	tO[0].loadFromFile("resources/2/obl1.png");
	tO[1].loadFromFile("resources/2/obl2.png");
	tO[2].loadFromFile("resources/2/obl3.png");

	vector<Texture> tZ(3); //�������� ��� ��������
	tZ[0].loadFromFile("resources/2/z1.png");
	tZ[1].loadFromFile("resources/2/z2.png");
	tZ[2].loadFromFile("resources/2/z3.png");

	vector<Barrier*> b; //�������
	vector<Barrier*> z; //��������

	CatchingMap m(mI.mBgT[4], 1505.0, yScreen); //�������� ����

	MindCatching p; //����, ���������� � ����������
	p.setTexture("resources/2/Mind.png", (xScreen - 258) / 2, yScreen - 358, 258.0, 358.0, 14);  //�������� �������

	Clock gameTime;
	size_t gameTS = 0; //����� � ������ ���� � ��������
	float forTime = 220.0; //�������� ����(�� ��� ������� ������� ����� ����)

	size_t animCount = 0;

	bool rMenu = true; //����� �� ���� ��� ����������
	gameTime.restart();

	bool rEx = false;
	while (p.isLive()) //���� ���� ���� � �� ���� �������� �� �����
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
						barriersGenerator(b, tO, 2);//��������� ��������
			}
			if (bg == 2)
			{
				if (!AnimCatched) //���� ������� � ��������� �� ��� �������
				{
					if (animCount < 30)
						if (b.size() == 0 || (b.size() != 0 && (b[b.size() - 1]->rect.top) > 150))
							if (z.size() == 0 || (z.size() != 0 && (z[z.size() - 1]->rect.top) > 200))
								animalsGenerator(z, tZ);//��������� ��������
				}
			}
			if (b.size() > 0)
			{
				barrierDel(b, 2); //�������� ���������� �������
				if (bg == 1 && gameTS > stars.getCount() && stars.getCount() < 50 && b.size() != 0)
					if (b[b.size() - 1]->rect.top > 100)
						starsGenerator(stars, *b[b.size() - 1], 2); //��������� �����
			}
			if (z.size() > 0) //���� ���� ��������
				if(isAnimalFell(z)) //���� �������� �����
					p.setLife(0); //�����

			if (stars.rects.size() > 0)
				stars.delStar(); //�������� ���������� �����
			
			for (size_t i = 0; i < b.size(); i++)
				b[i]->dir = p.dir; //����������� �������� ������� �� ����������� �����
			for (size_t i = 0; i < z.size(); i++)
				z[i]->dir = p.dir; //������� �������� ������� �� ����, �������� �� ��������� ����
			for (size_t i = 0; i < stars.rects.size(); i++)
				stars.setDir(p.dir);

			if (p.isStartShine()) //���� ����������� ����� �����
			{
				int ind = catchAnimal(p.rect, z); //���������� ������ ������������������ ���������
				if (ind != -1) //���� �������� ���������������
				{
					delete z[ind]; //�������� ������
					z.erase(z.begin() + ind);//������� �� �������
					animCount++;
				}
			}

			if (stars.rects.size() > 0)
			{
				int ind = collisionWithStar(p, stars.rects, 0, 0, 2); //���������� ������ ������, � ������� ��������� ������������
				if (ind != -1) //���� ������������ ���������
				{
					stars.delStar(ind); //������� ������ �� �������
					stars.plusStar(); //�������� ������ ����� �� ������ ������
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
					if (IntRect(mI.menuS[3].getPosition().x, mI.menuS[3].getPosition().y, 100, 100).contains(event.mouseMove.x, event.mouseMove.y)) //���� ������� �������� �� ����� ������
					{
						mI.menuS[3].setTexture(mI.menu2T[3]); //���������� ��������������� ��������
						rEx = true;
					}
					else{
						mI.menuS[3].setTexture(mI.menu1T[3]); //�������� ������ ������
						rEx = false;
					}
				}
				if (event.type == Event::MouseButtonPressed)
				{
					if (rEx) {
						p.setLife(0); //����� �� �������
						rMenu = false;
					}
				}
			}

			if (forTime > 150 && gameTS % 20 == 0 && gameTS > 20) //���������� �������� ���� �� ��������
				forTime -= 0.01;

			p.update(time);
			for (size_t i = 0; i < b.size(); i++) //�������� ��������
				b[i]->update(time, 2);

			for (size_t i = 0; i < z.size(); i++) //�������� ��������
				z[i]->update(time, 2);

			stars.updateStars(time, 2); //�������� �����

			ostringstream timeOrScore; //������ ��� ���-�� ����� ��� �������
			if (!isGameFinished)
				timeOrScore << stars.getCount(); //��������� ���-�� �����
			else timeOrScore << gameTS;
			text1.setString(timeOrScore.str());//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 

			if (!AnimCatched)
			{
				ostringstream animC; //������ ��� ���-�� ��������
				if (!AnimCatched)
					animC << animCount << " / 30";
				textAn.setString(animC.str());
			}
			if (b.size() > 0)
				if (collisionWithBarrier(p, b, 15, 80, 2))
					p.setLife(0); //�����

			short fr = 1; //���� ���� �� �������� � �������� �� ������������
			if (!p.isLive())
				fr = 16; //���-�� ������ ���������
			for (short frameTeleport = 0; frameTeleport < fr; frameTeleport++)
			{
				window.clear();
				window.clear();
				window.draw(m.sprite1); //���������� ���� ��������
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
		else //���� ���� ��������
		{
			for (auto it : b) //������� ���� ���������� ������
				delete it;
			b.clear();
			stars.clear();
		}
	}
	window.clear();
	return rMenu; //���������� ��������� ����� ����(����� / �������)
}
