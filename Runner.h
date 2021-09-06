#pragma once
#include "Header.h"

bool Runner(RenderWindow &window, Stars &stars, MenuItems& mI, bool isGameFinished)
{
	mI.menuS[3].setPosition(60.0, 20.0);
	
	float CurrentFrame = 0;
	Clock clock;

	Text text1("", mI.font, 70);
	text1.setColor(Color::Black);
	text1.setStyle(Text::Bold);
	text1.setPosition(xScreen - 150, 20);//������ ������� ������

	vector<Texture> textures(4); //�������� ��� �������
	textures[0].loadFromFile("resources/1/rock.png");
	textures[1].loadFromFile("resources/1/thorn.png");
	textures[2].loadFromFile("resources/1/snag.png");
	textures[3].loadFromFile("resources/1/thorns.png");

	vector<Barrier*> b;

	RunnerMap m(mI.mBgT[3], 3585.0, yScreen); //�������� ����

	MindRunner p; //����, ���������� � ����������
	p.setTexture("resources/1/Mind.png", 20.0, 0.0, 340.0, 360.0, 36);  //�������� �������

	Clock gameTime;
	size_t gameTS = 0; //����� � ������ ���� � ��������
	int forTime = 250; //�������� ����(�� ��� ������� ������� ����� ����)

	bool rMenu = true; //����� �� ���� ��� ����������
	bool rEx = false;

	while (p.isLive()) //���� ���� ����
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		gameTS = gameTime.getElapsedTime().asSeconds();
		time = time / forTime;
		if (p.dir == 0)
			gameTime.restart();

		if (p.isLive())
		{
			if (p.dir == 1) //�������� � �������� �������
			{
				short int bg = rand() % 110;
				if (bg == 0)
					if (b.size() == 0 || (b.size() != 0 && (b[b.size() - 1]->rect.left + (b[b.size() - 1]->rect.width)) < xScreen - 500))
						barriersGenerator(b, textures, 1); //��������� �������

				if (b.size() > 0)
				{
					barrierDel(b, 1); //�������� ���������� �������
					if (bg == 100 && gameTS > stars.getCount() && stars.getCount() < 50 && b.size() != 0)
						starsGenerator(stars, *(*(b.end() - 1)), 1); //��������� �����
				}
				if (stars.rects.size() > 0)
					stars.delStar(); //�������� ���������� �����
			}
			for (size_t i = 0; i < b.size(); i++)
				b[i]->dir = m.dir;
			for (size_t i = 0; i < stars.rects.size(); i++)
				stars.setDir(m.dir);

			if (stars.rects.size() > 0)
			{
				int ind = collisionWithStar(p, stars.rects, 130, 5, 1);
				if (ind != -1)
				{
					stars.delStar(ind);
					stars.plusStar();
				}
			}

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::MouseMoved){
					if (IntRect(mI.menuS[3].getPosition().x, mI.menuS[3].getPosition().y, 100, 100).contains(event.mouseMove.x, event.mouseMove.y)) //���� ������� �������� �� ����� ������
					{
						mI.menuS[3].setTexture(mI.menu2T[3]); //���������� ��������������� ��������
						rEx = true;
					}
					else {
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
				else if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Key::Right || event.key.code == Keyboard::Key::D){
						p.dir = 1;
						p.dx = 0.1;
						m.dir = 1;
					}
					else if (event.key.code == Keyboard::Key::Up || event.key.code == Keyboard::Key::W || event.key.code == Keyboard::Key::Space && p.dir != 0){
						if (p.onGround)
						{
							p.dy = -0.8;
							p.onGround = false;
						}
					}
				}
			}

			if (forTime > 150 && gameTS % 10 == 0 && gameTS > 20)
				forTime -= 1;

			m.update(time);
			p.update(time);
			for (size_t i = 0; i < b.size(); i++)
				b[i]->update(time, 1);

			stars.updateStars(time, 1);
			ostringstream timeOrScore; //������ ��� ���-�� ����� ��� �������
			if (!isGameFinished)
				timeOrScore << stars.getCount();
			else timeOrScore << gameTS;
			text1.setString(timeOrScore.str());//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 

			if (b.size() > 0)
				if (collisionWithBarrier(p, b, 130, 5, 1))
					p.setLife(0); /////����� �� �������

			short fr = 1; //���� ���� ��� �� ���������
			if (!p.isLive()) //���� ��� ���������
				fr = 16; //���������� ������������
			for (short frameTeleport = 0; frameTeleport < fr; frameTeleport++)
			{
				window.clear();
				window.draw(m.sprite1); //���������� ���� ��������
				window.draw(m.sprite2);
				if (!p.isLive()) //���� ���� ���������
				{
					p.teleportFromPlay(frameTeleport); //����� ������ ����������������
					Sleep(50);
				}
				window.draw(p.sprite);
				for (auto it : stars.sprites)
					window.draw(*it);
				for (auto it : b)
					window.draw(it->sprite);
				window.draw(text1);
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




	//while (p.isLive()) //���� ���� ����
	//{
	//	Sleep(10);
	//	if (IntRect(mI.menuS[3].getPosition().x, mI.menuS[3].getPosition().y, 100, 100).contains(Mouse::getPosition(window))) //���� ������� �������� �� ����� ������
	//	{
	//		mI.menuS[3].setTexture(mI.menu2T[3]); //���������� ��������������� ��������
	//		if (Mouse::isButtonPressed(Mouse::Left))
	//		{
	//			p.setLife(0); //����� �� �������
	//			rMenu = false;
	//		}
	//	}
	//	else mI.menuS[3].setTexture(mI.menu1T[3]); //�������� ������ ������

	//	float time = clock.getElapsedTime().asMicroseconds();
	//	clock.restart();
	//	gameTS = gameTime.getElapsedTime().asSeconds();
	//	time = time / forTime;
	//	if (p.dir == 0)
	//		gameTime.restart();

	//	if (p.isLive())
	//	{
	//		if (p.dir == 1) //�������� � �������� �������
	//		{
	//			short int bg = rand() % 110;
	//			if (bg == 0)
	//				if (b.size() == 0 || (b.size() != 0 && (b[b.size() - 1]->rect.left + (b[b.size() - 1]->rect.width)) < xScreen - 500))
	//					barriersGenerator(b, textures, 1); //��������� �������

	//			if (b.size() > 0)
	//			{
	//				barrierDel(b, 1); //�������� ���������� �������
	//				if (bg == 100 && gameTS > stars.getCount() && stars.getCount() < 50 && b.size() != 0)
	//					starsGenerator(stars, *(*(b.end() - 1)), 1); //��������� �����
	//			}
	//			if (stars.rects.size() > 0)
	//				stars.delStar(); //�������� ���������� �����
	//		}
	//		for (size_t i = 0; i < b.size(); i++)
	//			b[i]->dir = m.dir;
	//		for (size_t i = 0; i < stars.rects.size(); i++)
	//			stars.setDir(m.dir);

	//		if (stars.rects.size() > 0)
	//		{
	//			int ind = collisionWithStar(p, stars.rects, 130, 5, 1);
	//			if (ind != -1)
	//			{
	//				stars.delStar(ind);
	//				stars.plusStar();
	//			}
	//		}

	//		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))))
	//		{
	//			p.dir = 1;
	//			p.dx = 0.1;
	//			m.dir = 1;
	//		}
	//		if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Space)) && p.dir != 0)
	//		{
	//			if (p.onGround)
	//			{
	//				p.dy = -0.8;
	//				p.onGround = false;
	//			}
	//		}

	//		if (forTime > 150 && gameTS % 10 == 0 && gameTS > 20)
	//			forTime -= 1;

	//		m.update(time);
	//		p.update(time);
	//		for (size_t i = 0; i < b.size(); i++)
	//			b[i]->update(time, 1);

	//		stars.updateStars(time, 1);
	//		ostringstream timeOrScore; //������ ��� ���-�� ����� ��� �������
	//		if (!isGameFinished)
	//			timeOrScore << stars.getCount();
	//		else timeOrScore << gameTS;
	//		text1.setString(timeOrScore.str());//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 

	//		if (b.size() > 0)
	//			if (collisionWithBarrier(p, b, 130, 5, 1))
	//				p.setLife(0); /////����� �� �������

	//		short fr = 1; //���� ���� ��� �� ���������
	//		if (!p.isLive()) //���� ��� ���������
	//			fr = 16; //���������� ������������
	//		for (short frameTeleport = 0; frameTeleport < fr; frameTeleport++)
	//		{
	//			window.clear();
	//			window.draw(m.sprite1); //���������� ���� ��������
	//			window.draw(m.sprite2);
	//			if (!p.isLive()) //���� ���� ���������
	//			{
	//				p.teleportFromPlay(frameTeleport); //����� ������ ����������������
	//				Sleep(50);
	//			}
	//			window.draw(p.sprite);
	//			for (auto it : stars.sprites)
	//				window.draw(*it);
	//			for (auto it : b)
	//				window.draw(it->sprite);
	//			window.draw(text1);
	//			window.draw(mI.menuS[3]);
	//			window.display();
	//		}
	//	}
	//	else //���� ���� ��������
	//	{
	//		for (auto it : b) //������� ���� ���������� ������
	//			delete it;
	//		b.clear();
	//		stars.clear();
	//	}
	//}
	window.clear();
	return rMenu;
}
