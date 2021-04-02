//Snake made by Silvian Achim
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

#define LENGTH 50
#define WIDTH 40

using namespace sf;

int size = 16;
int w = size * LENGTH;
int h = size * WIDTH;
int dir=0, tail = 4, gameLost;

struct position
{
	int x;
	int y;
}snake[100], fruit;;

void game()
{
	for (int i = tail; i > 0; i--)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;

	}
	if (dir == 0)
	{
		snake[0].y++;
	}
	 if (dir == 1)
	{
		snake[0].x--;
	}
	 if (dir == 2)
	{
		snake[0].x++;
	}
	if(dir==3)
	{
		snake[0].y--;
	}
	if ((snake[0].x == fruit.x) && (snake[0].y == fruit.y))
	{
		tail++;
		fruit.x = rand() % LENGTH;
		fruit.y = rand() % WIDTH;
	}
	if (snake[0].x > LENGTH)
	{
		snake[0].x = 0;
	}
	if (snake[0].x < 0)
	{
		snake[0].x = LENGTH;
	}
	if (snake[0].y > WIDTH)
	{
		snake[0].y = 0;
	}
	if (snake[0].y < 0)
	{
		snake[0].y = WIDTH;
	}
	for (int i = 1; i < tail; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			gameLost = 1;
		}
	}
}

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(w, h), "Snake made by Silvian Achim!");
	Texture t1, t2, t3, t4, t5;
	t1.loadFromFile("images/mapa.png");
	t2.loadFromFile("images/zacFace.png");
	t3.loadFromFile("images/zacBody.png");
	t4.loadFromFile("images/bush.png");
	t5.loadFromFile("images/GameOver.png");

	Sprite map(t1);
	Sprite face(t2);
	Sprite body(t3);
	Sprite bush(t4);
	Sprite gameOver(t5);

	Clock clock;
	float timer = 0, delay = 0.1;
	///ceva
	fruit.x - 10;
	fruit.y = 10;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			dir = 1; // go left
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			dir = 2; // go right
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			dir = 3; // go up
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			dir = 0; // go down
		}
		if (timer > delay)
		{
			timer = 0;
			game();
		}
		window.clear();
		if (gameLost == 1)
		{
			window.draw(gameOver);
			window.display();
		}
		else
		{
			for (int i = 0; i < LENGTH; i++)
			{
				for (int j = 0; j < WIDTH; j++)
				{
					map.setTextureRect( IntRect (i * size, j * size, size, size));
					map.setPosition(i * size, j * size);
					window.draw(map);
				}
			}
			face.setPosition(snake[0].x * size, snake[0].y * size);
			window.draw(face);
			for (int i = 1; i < tail; i++)
			{
				body.setPosition(snake[i].x * size, snake[i].y * size);
				window.draw(body);
			}
			bush.setPosition(fruit.x * size, fruit.y * size);
			window.draw(bush);
			window.display();
		}
	}
	return 0;
}
