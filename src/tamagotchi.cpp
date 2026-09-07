#include "tamagotchi.hpp"

#include <algorithm>

namespace
{
float clampStat(float value)
{
	return std::clamp(value, 0.0f, 100.0f);
}
}

void Tamagotchi::update(float deltaSeconds)
{
	hunger_ = clampStat(hunger_ - 2.0f * deltaSeconds);
	happiness_ = clampStat(happiness_ - 1.0f * deltaSeconds);
	energy_ = clampStat(energy_ - 1.5f * deltaSeconds);
}

void Tamagotchi::feed()
{
	hunger_ = clampStat(hunger_ + 28.0f);
	energy_ = clampStat(energy_ + 4.0f);
}

void Tamagotchi::play()
{
	if (energy_ < 12.0f)
		return;

	hunger_ = clampStat(hunger_ - 6.0f);
	happiness_ = clampStat(happiness_ + 25.0f);
	energy_ = clampStat(energy_ - 15.0f);
}

void Tamagotchi::sleep()
{
	energy_ = clampStat(energy_ + 30.0f);
	hunger_ = clampStat(hunger_ - 8.0f);
}

void Tamagotchi::reset()
{
	hunger_ = 70.0f;
	happiness_ = 70.0f;
	energy_ = 70.0f;
}

float Tamagotchi::hunger() const { return hunger_; }
float Tamagotchi::happiness() const { return happiness_; }
float Tamagotchi::energy() const { return energy_; }

bool Tamagotchi::isAlive() const
{
	return hunger_ > 0.0f && happiness_ > 0.0f && energy_ > 0.0f;
}
