#include <SFML/Graphics.hpp>
#include "cat.h"
#include "info.h"
#include "iostream"
#include "chrono"
#include "MainMenu.h"

// ������: ������� ���� �������� ��� ������.
// ��� ����� �������, �����, �������.
// �� ����� ����� � ����� ���� �� �������� ���� �����.

// TODO
// ������ [�������, �����, ����]
// ����������

// ����������
// �������� ������ �� ������:
// * ���������
// * ������
// * �������



void updateCatPicture(const  sf::Texture & texture, sf::Sprite & sprite,
	std::chrono::time_point<std::chrono::steady_clock>& startTime) {
	sprite.setTexture(texture);
	startTime = std::chrono::high_resolution_clock::now();
}


int main() {
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tamagotchi!");
	window.setFramerateLimit(60);
	MainMenu mainMenu(&window);

	if (!mainMenu.render()) return 0;


	sf::Event event;

	sf::Texture idle;
	sf::Texture eating;
	if (!idle.loadFromFile("cat_idle.png") or !eating.loadFromFile("cat_eat.png")) {
		// error...
	}
	sf::Sprite sprite;
	sprite.setTexture(idle);
	sprite.scale(sf::Vector2f(.01f, .01f));
	
	// Game logic
	Cat cat( 1, 100, 1000, 1000);
	Info info(&cat);

	

	std::chrono::time_point<std::chrono::steady_clock> startTime
		= std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration;

	while (window.isOpen())	{
		if (cat.isDead()) // TODO ���� ��������� 
			exit(0);
		if (cat.isSuccess())
			exit(0); // TODO ���� ������ 

		duration = std::chrono::high_resolution_clock::now() - startTime;

		cat.live();

		sprite.setScale(sf::Vector2f(float(cat.getSize()) / cat.getMaxSize(),
			float(cat.getSize()) / cat.getMaxSize()));

		while (window.pollEvent(event)) {

			if (duration.count() > 1) {
				sprite.setTexture(idle);
			}

			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				// �������� ������� ������� - ��������� ��������������� ��������
				if (event.key.code == sf::Keyboard::Escape) window.close();

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
					cat.increaseFull(50);
					updateCatPicture(eating, sprite, startTime);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
					cat.increaseHydr(50);
					updateCatPicture(eating, sprite, startTime);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
					cat.increaseClean(50);
					updateCatPicture(eating, sprite, startTime);
				}
			}
		}


		info.update();
		//text.setString(info.getStr());

		// ��������� ����������� �������� �� ���������
		window.clear(sf::Color::White);
		window.draw(sprite);
		//window.draw(text);
		window.display();
	}

	return 0;
}