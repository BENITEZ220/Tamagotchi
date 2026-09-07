#include "game.hpp"

#include <algorithm>

Game::Game()
	: window_(sf::VideoMode({800, 600}), "Tamagotchi")
	, feedButton_({90.0f, 500.0f}, {180.0f, 55.0f}, sf::Color(245, 180, 80))
	, playButton_({310.0f, 500.0f}, {180.0f, 55.0f}, sf::Color(100, 190, 245))
	, sleepButton_({530.0f, 500.0f}, {180.0f, 55.0f}, sf::Color(145, 120, 220))
{
	window_.setFramerateLimit(60);
}

void Game::run()
{
	while (window_.isOpen())
	{
		processEvents();
		update(clock_.restart().asSeconds());
		render();
	}
}

void Game::processEvents()
{
	while (const std::optional event = window_.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window_.close();
			continue;
		}

		if (const auto* key = event->getIf<sf::Event::KeyPressed>())
		{
			if (key->code == sf::Keyboard::Key::F)
				pet_.feed();
			else if (key->code == sf::Keyboard::Key::P)
				pet_.play();
			else if (key->code == sf::Keyboard::Key::S)
				pet_.sleep();
			else if (key->code == sf::Keyboard::Key::R)
				pet_.reset();
		}

		if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
		{
			if (mouse->button != sf::Mouse::Button::Left)
				continue;

			const sf::Vector2f point = window_.mapPixelToCoords(mouse->position);
			if (feedButton_.contains(point))
				pet_.feed();
			else if (playButton_.contains(point))
				pet_.play();
			else if (sleepButton_.contains(point))
				pet_.sleep();
		}
	}
}

void Game::update(float deltaSeconds)
{
	pet_.update(std::min(deltaSeconds, 0.25f));

	const sf::Vector2f mouse = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
	feedButton_.setHovered(feedButton_.contains(mouse));
	playButton_.setHovered(playButton_.contains(mouse));
	sleepButton_.setHovered(sleepButton_.contains(mouse));
}

void Game::render()
{
	window_.clear(sf::Color(33, 38, 58));

	drawStatBar(pet_.hunger(), {80.0f, 55.0f}, sf::Color(245, 180, 80));
	drawStatBar(pet_.happiness(), {80.0f, 105.0f}, sf::Color(245, 105, 150));
	drawStatBar(pet_.energy(), {80.0f, 155.0f}, sf::Color(100, 190, 245));
	drawPet();

	feedButton_.draw(window_);
	playButton_.draw(window_);
	sleepButton_.draw(window_);
	window_.display();
}

void Game::drawStatBar(float value, sf::Vector2f position, sf::Color color)
{
	sf::RectangleShape background({640.0f, 26.0f});
	background.setPosition(position);
	background.setFillColor(sf::Color(20, 24, 40));
	background.setOutlineThickness(2.0f);
	background.setOutlineColor(sf::Color(85, 90, 115));
	window_.draw(background);

	sf::RectangleShape fill({6.4f * value, 26.0f});
	fill.setPosition(position);
	fill.setFillColor(color);
	window_.draw(fill);
}

void Game::drawPet()
{
	const sf::Color bodyColor = pet_.isAlive() ? sf::Color(235, 205, 145) : sf::Color(120, 120, 130);

	sf::CircleShape body(120.0f);
	body.setPosition({280.0f, 215.0f});
	body.setFillColor(bodyColor);
	body.setOutlineThickness(6.0f);
	body.setOutlineColor(sf::Color(70, 55, 75));
	window_.draw(body);

	sf::CircleShape eye(16.0f);
	eye.setFillColor(sf::Color(35, 35, 50));
	eye.setPosition({340.0f, 285.0f});
	window_.draw(eye);
	eye.setPosition({440.0f, 285.0f});
	window_.draw(eye);

	sf::RectangleShape mouth({55.0f, 10.0f});
	mouth.setPosition({372.0f, 355.0f});
	mouth.setFillColor(sf::Color(70, 55, 75));
	window_.draw(mouth);
}
