#pragma once

class Tamagotchi
{
public:
	void update(float deltaSeconds);
	void feed();
	void play();
	void sleep();
	void reset();

	float hunger() const;
	float happiness() const;
	float energy() const;
	bool isAlive() const;

private:
	float hunger_ = 70.0f;
	float happiness_ = 70.0f;
	float energy_ = 70.0f;
};
