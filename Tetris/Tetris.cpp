#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "Button.h"
#include "Labell.h"
#include "GameLogic.h"
void GetMenu();
void Game();
int main() {
	GetMenu();
}
void GetMenu() {
	RenderWindow menu;
	Vector2i position;
	int X, Y;
	menu.create(VideoMode(300, 300), "Menu");
	Texture texture_menu,texture_menu_black;
	texture_menu.loadFromFile("D:\\Tetris\\Menuback.png");
	texture_menu_black.loadFromFile("D:\\Tetris\\Menuback.jpg");
	Sprite menuBackGR(texture_menu);
	Sprite menuBackGRBlack(texture_menu_black);
	Button play(100, 50, "Play");
	Button music(100, 100, "Music ON");
	Button black(100, 150, "Dark OFF");
	Button exit(100, 200, "Exit");
	if (isMusic) music.setText("Music ON");
	if (!isMusic) music.setText("Music OFF");
	if (isBlack) black.setText("Black ON");
	if (!isBlack) black.setText("Black OFF");

	
	while (menu.isOpen())
	{
		
		menu.clear(Color::White);
		
		position = Mouse::getPosition(menu);
		Event e;
		Vector2i mouse;
		while (menu.pollEvent(e))
		{
			mouse = Mouse::getPosition(menu);
			play.contain(mouse);music.contain(mouse); black.contain(mouse); exit.contain(mouse);
			if (e.type == Event::Closed)
			{
				menu.close();
			}
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					if (play.select(mouse))
					{
						menu.close();
						Game();
						
					}
					if (music.select(mouse))
					{
						if (isMusic) {
							music.setText("Music OFF");
							isMusic = false;
						}
						else if (!isMusic) {
							music.setText("Music ON");
							isMusic = true;
						}
						
						
					}
					if (black.select(mouse))
					{
						if (isBlack) {
							black.setText("Black OFF");
							isBlack = false;
						}
						else if (!isBlack) {
							black.setText("Black ON");
							isBlack = true;
						}
					}
					if (exit.select(mouse))
					{
						menu.close();
					}
				}
			}
		}
		if (!isBlack) menu.draw(menuBackGR);
		else if (isBlack) menu.draw(menuBackGRBlack);
		
		play.display(menu);
		music.display(menu);
		black.display(menu);
		exit.display(menu);
		menu.display();
	}
}
void Game() {
	srand(time(0));
	RenderWindow window(VideoMode(320, 480), "Tetris");
	sf::Music music;
	music.openFromFile("Music.ogg");
	if (isMusic) { music.play(); }
	Texture texture, texture_background, texture_frame, texture_background_black,texture_black;
	texture.loadFromFile("D:\\Tetris\\tiles.png");
	texture_background.loadFromFile("D:\\Tetris\\background.png");
	texture_frame.loadFromFile("D:\\Tetris\\frame.png");
	texture_background_black.loadFromFile("D:\\Tetris\\Menuback.jpg");
	texture_black.loadFromFile("D:\\Tetris\\tilesWhite.jpg");
	Sprite sprite(texture), sprite_background(texture_background), sprite_frame(texture_frame), sprite_background_black(texture_background_black);
	if (isBlack) { sprite.setTexture(texture_black); }
	sprite.setTextureRect(IntRect(0, 0, 18, 18));
	Label gameover(50, 200, "Game Over! \n press F to quit",30);
	Label level(25, 400, "Level \n " + std::to_string(recentLevel),20);
	Label lines(100, 400, "Score \n " + std::to_string(score),20);
	if (isBlack) { level.changeColor(Color::White); lines.changeColor(Color::White); gameover.changeColor(Color::Red); }
	
	int dx = 0; bool rotate = 0; int colorNum = 1; bool beginGame = true; int n = rand() % 7;
	float timer = 0;
	float recentDelay = 0.7f;
	float delay = (float)recentDelay;
	Clock clock;
	while (window.isOpen() )
	{
		// Получаем время, прошедшее с начала отсчета, и конвертируем его в секунды
		
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		SetLevel(delay, recentDelay);
		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {

				if (event.key.code == Keyboard::Up) rotate = true;
				else if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;
				else if (event.key.code == Keyboard::Left) dx = -1;
				else if (event.key.code == Keyboard::Right) dx = 1;
				else if (event.key.code == Keyboard::F) {
					for (int i = 0; i < M; i++)
						for (int j = 0; j < N; j++) {
							field[i][j] = 0;
						}
					countOfLines = 0;
					recentLevel = 1;
					music.stop();

					window.close();
					GetMenu();
					break;
				}
			}
		}
			//перемещение по горизонтали
			for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }

			

			if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
			
			
			Rotate(rotate);

			MoveDown(timer, colorNum, delay, n);
			

			CheckLines();
			level.changeText("Level \n " + std::to_string(recentLevel));
			lines.changeText("Score \n " + std::to_string(score));
			if (beginGame)
			{
				beginGame = false;
				n = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					a[i].x = 4 + figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}
			dx = 0; rotate = 0;

			delay = recentDelay;
			//----ОТРИСОВКА----//

		
			if (!GameOver()) {
				gameover.display(window);
				
				music.stop();
			}

			else {
				window.clear(Color::White);

				if (!isBlack) window.draw(sprite_background);
				else if (isBlack) window.draw(sprite_background_black);
				for (int i = 0; i < M; i++)


					for (int j = 0; j < N; j++)
					{
						if (field[i][j] == 0) continue;
						sprite.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
						sprite.setPosition(j * 18, i * 18);
						sprite.move(28, 31); // смещение
						window.draw(sprite);
					}

				for (int i = 0; i < 4; i++)
				{
					// Разукрашиваем тетрамино
					sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
					// Устанавливаем позицию каждого кусочка тетрамино
					sprite.setPosition(a[i].x * 18, a[i].y * 18);
					sprite.move(28, 31); 
					window.draw(sprite);
				}
			
				window.draw(sprite_frame);
				level.display(window);
				lines.display(window);
			}
			
			window.display();
		
		
		
	}
}