#include "button.hpp"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, sf::Color color)
	: color_(color)
{
	shape_.setPosition(position);
	shape_.setSize(size);
	shape_.setFillColor(color_);
	shape_.setOutlineThickness(3.0f);
	shape_.setOutlineColor(sf::Color(35, 35, 55));
}

bool Button::contains(sf::Vector2f point) const
{
	return shape_.getGlobalBounds().contains(point);
}

void Button::setHovered(bool hovered)
{
	shape_.setFillColor(hovered ? sf::Color(255, 255, 255) : color_);
}

void Button::draw(sf::RenderWindow& window) const
{
	window.draw(shape_);
}
