#pragma once
#include "Header.h"

class Stars
{
	int stars = 0;
	Texture texture;
	double dx, dy;
	int dir = 0;
public:
	list<FloatRect*> rects;
	list<Sprite*> sprites;
	Stars()
	{
		texture.loadFromFile("resources/0/star.png"); //загрузка текстуры звезд
	}
	
	void plusStar()
	{
		stars++; //увеличение кол-ва звезд на 1
	}

	void updateStars(float time, size_t level = 0)
	{
		if (dir == 1) //если звезды двигаются
		{
			if (level == 1 || level == 0) //в первом уровне и перелетах двигаются влево
			{
				dx = -0.16;
				for (auto it : rects)
					it->left += dx*time;
			}
			else if (level == 2) //во втром вниз
			{
				dy = +0.1;
				for (auto it : rects)
					it->top += dy*time;
			}
		}
		auto it2 = rects.begin();
		for (auto it1 : sprites)
		{
			it1->setPosition((*it2)->left, (*it2)->top);
			++it2;
		}
	}
	int getCount() const
	{
		return stars;
	}
	void addStar(size_t level)
	{
		Sprite * sprite = new Sprite; //спрайт для звезды
		sprite->setTexture(texture);
		sprites.push_back(sprite);
		FloatRect * rect = new FloatRect; //координаты звезды
		if (level == 1)
		{
			(*rect).left = xScreen + 5;
			short n = rand() % 100;
			(*rect).top = 100 + n;
		}
		else if (level == 2)
		{
			(*rect).top = -100;
			vector<int> v = { 20, xScreen / 4 + 10, (xScreen / 2) + 10, (xScreen / 4) * 3 };
			short n1 = rand() % 4;
			short n2 = rand() % 20;
			(*rect).left = v[n1] + n2;
		}
		rects.push_back(rect);

		sprite->setTextureRect(IntRect(0, 0, 60, 60)); //установка текстуры, размер изображения звездочек
	}
	void addStarForFlying1()
	{
		Sprite * sprite = new Sprite;
		sprite->setTexture(texture);
		sprites.push_back(sprite);
		FloatRect * rect = new FloatRect;
		(*rect).left = xScreen + 5;
		(*rect).top = ground1 - 50;
		rects.push_back(rect);

		sprite->setTextureRect(IntRect(0, 0, 50, 50)); //размер изображения звездочек
	}
	void delStar(int ind = -1) //удалять по индексу
	{
		if (ind == -1 && (*rects.begin())->left + 60 < 0 || ind != -1) //если индекс не был задан, удаляется самая первая, если она вышла за пределы экрана
		{
			if (ind == -1)
				ind = 0;
			auto it1 = rects.begin();
			auto it2 = sprites.begin();
			size_t i = 0;
			while (i != ind)
			{
				it1++;
				it2++;
				i++;
			}
			delete (*it1);
			rects.erase(it1);
			delete (*it2);
			sprites.erase(it2);
		}
	}
	void clear()
	{
		for (auto it : rects)
			delete[] it;
		rects.clear();
		for (auto it : sprites)
			delete[] it;
		sprites.clear();
	}

	void setDir(int d)
	{
		dir = d;
	}
	void setStarsCount(size_t st)
	{
		stars = st;
	}
};