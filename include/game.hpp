#pragma once

#include "button.hpp"
#include "tamagotchi.hpp"

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void update(float deltaSeconds);
	void render();
	void drawStatBar(float value, sf::Vector2f position, sf::Color color);
	void drawPet();

	sf::RenderWindow window_;
	sf::Clock clock_;
	Tamagotchi pet_;
	Button feedButton_;
	Button playButton_;
	Button sleepButton_;
};
