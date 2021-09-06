#include "MindFlying.h"
#include "Map.h"
#include "Barrier.h"
#include "Stars.h"

int met = 50;
void barriersGenerator(vector<Barrier*> & b, vector<Texture> & textures);
bool starsGenerator(Stars & s, Barrier & b);
void barrierDel(vector<Barrier*> & b);
bool collision(FloatRect rect1, FloatRect rect2, size_t cutFr, int rect1W, int rect1H, int rect2W, int rect2H);
bool collisionWithBarrier(Person &p, vector<Barrier*> & b);
int collisionWithStar(Person & p, list<FloatRect*> & rects);
int minMet()
{
	met--;
	return met;
}

void Flying(RenderWindow &window, Stars &stars)
{
	Clock clock;

	Font font;
	font.loadFromFile("resources/0/font.ttf");
	Text text("", font, 50);
	text.setColor(Color::Black);
	text.setStyle(Text::Bold);

	vector<Texture> textures(2);
	textures[0].loadFromFile("resources/0/Meteor.png");
	textures[1].loadFromFile("resources/0/small_meteor.png");

	Texture StarForScore;//создаем объект Texture (текстура)
	StarForScore.loadFromFile("resources/0/star.png");//загружаем картинку
	Sprite SpriteForScore;//создаем объект Sprite(спрайт)
	SpriteForScore.setTexture(StarForScore);//передаём в него объект Texture (текстуры)
	SpriteForScore.setPosition(xScreen - 110, 20);//задаем начальные координаты появления спрайта

	vector<Barrier*> b;
	int BarrierCount = 0;

	Texture back;
	back.loadFromFile("resources/0/all_sky.png");
	FlyingMap m(back, 3585.0, yScreen);
	Person * p = new MindFlying;
	p->setTexture("resources/0/rocket.png", 50.0f, ground2, 262.0f, 100.0f, 1);

	size_t st = 0;
	while (p->isLive())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			return;

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 200;


		if (b.size() > 0)//здесь надо что проигрыш
		{
			if (collisionWithBarrier((*p), b))
			{
				for (auto it : b)
					delete it;
				b.clear();
				stars.clear();
				p->setLife(0);
			}
		}
		if (met == 0)//здесь надо что выигрыш
			p->setLife(0);
		if (p->isLive())
		{
			if (p->dir == 1) //создание и удаление преград
			{
				short int bg = rand() % 250;
				if (bg == 0)
				{
					if ((b.size() == 0 || (b.size() != 0 && (b[b.size() - 1]->rect.left + (b[b.size() - 1]->rect.width)) < xScreen - 500)))
					{
						barriersGenerator(b, textures);
					}
				}
				if (b.size() > 0)
				{
					barrierDel(b);
					if (bg == 100 && st < 30 && b.size() != 0)
						if (starsGenerator(stars, *(*(b.end() - 1))))
							st++;
				}
				if (stars.rects.size() > 0)
					stars.delStar();
			}
			for (size_t i = 0; i < b.size(); i++)
				b[i]->dir = m.dir;
			for (size_t i = 0; i < stars.rects.size(); i++)
				stars.setDir(m.dir);

			(*p).dir = 1;
			(*p).dx = 0.1f;
			m.dir = 1;

			if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))) && p->dir != 0)
			{
				(*p).dir = 2;
				(*p).dy = -0.8f;
				(*p).onGround = false;
			}
			if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))) && p->dir != 0)
			{
				(*p).dir = 3;
				(*p).dy = 0.8f;
				(*p).onGround = false;
			}
			if (stars.rects.size() > 0)
			{
				int ind = collisionWithStar((*p), stars.rects);
				if (ind != -1)
				{
					stars.delStar(ind);
					stars.plusStar();
				}
			}

			m.update(time);
			(*p).update(time);
			for (size_t i = 0; i < b.size(); i++)
				b[i]->update(time, 3);

			stars.updateStars(time);
			ostringstream playerScoreString;
			playerScoreString << stars.getCount();
			text.setString(playerScoreString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			text.setPosition(xScreen - 180, 20);//задаем позицию текста

			window.clear();
			window.draw(m.sprite1);
			window.draw(m.sprite2);
			window.draw((*p).sprite);
			for (auto it : stars.sprites)
				window.draw(*it);
			for (auto it : b)
				window.draw(it->sprite);
			window.draw(text);
			window.draw(SpriteForScore);//выводим спрайт на экран
			window.display();
		}
	}
	window.clear();
}

void barriersGenerator(vector<Barrier*> & b, vector<Texture> & textures)
{
	Barrier * barrier = new Barrier;
	b.push_back(barrier);
	short n = rand() % 3;
	if (n == 0)
		barrier->setTextureForFlying(textures[n], 160, 164, ground1);
	if (n == 1)
		barrier->setTextureForFlying(textures[n], 118, 120, ground2);
}

bool starsGenerator(Stars & s, Barrier & b)
{
	if (b.rect.left + b.rect.width < xScreen - 50)
	{
		if (s.rects.size() == 0 || (*(s.rects.cbegin()))->left < xScreen - 50)
		{
			s.addStarForFlying1();
			return 1;
		}
	}
	return 0;
}

int collisionWithStar(Person & p, list<FloatRect*> & rects)
{
	if ((p.rect.left + p.rect.width) + 100 > (*rects.begin())->left)
	{
		int cutFr = 0;
		int ind = 0;
		for (auto it : rects)
		{
			if (collision(p.rect, (*it), cutFr, p.rect.width, p.rect.height, 60, 60))
				return ind;
			ind++;
		}
	}
	return -1;
}

bool collision(FloatRect rect1, FloatRect rect2, size_t cutFr, int rect1W, int rect1H, int rect2W, int rect2H)
{
	int k = 0;
	if (rect1.left + cutFr >= rect2.left && rect1.left + cutFr <= rect2.left + rect2W && rect1.top >= rect2.top && rect1.top <= rect2.top + rect2H)
		k++;
	if (rect1.left - cutFr + rect1W >= rect2.left && rect1.left - cutFr + rect1W <= rect2.left + rect2W && rect1.top >= rect2.top && rect1.top <= rect2.top + rect2H)
		k++;
	if (rect1.left + cutFr >= rect2.left && rect1.left + cutFr <= rect2.left + rect2W && rect1.top + rect1H >= rect2.top && rect1.top + rect1H <= rect2.top + rect2H)
		k++;
	if (rect1.left - cutFr + rect1W >= rect2.left && rect1.left - cutFr + rect1W <= rect2.left + rect2W && rect1.top + rect1H >= rect2.top && rect1.top + rect1H <= rect2.top + rect2H)
		k++;
	if (k != 0)
		return 1;
	else return 0;
}

void barrierDel(vector<Barrier*> & b)
{
	if (b[0]->rect.left + b[0]->rect.width < 0)
	{
		minMet();
		delete b[0];
		b.erase(b.begin());
	}
}

bool collisionWithBarrier(Person &p, vector<Barrier*> & b)
{
	if ((p.rect.left + p.rect.width) + 100 > b[0]->rect.left)
	{
		int cutFr = 3;
		for (size_t i = 0; i < b.size(); i++)
			if (collision(p.rect, b[i]->rect, cutFr, p.rect.width, p.rect.height, b[i]->rect.width, b[i]->rect.height))
				return 1;
	}
	return 0;
}