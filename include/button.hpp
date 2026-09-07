#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(const sf::Vector2f& position, const sf::Vector2f& size, sf::Color color);

	bool contains(sf::Vector2f point) const;
	void setHovered(bool hovered);
	void draw(sf::RenderWindow& window) const;

private:
	sf::RectangleShape shape_;
	sf::Color color_;
};
