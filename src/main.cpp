#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>

#include "Const.hpp"

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

struct Particle
{
	Vector2
		position,
		acceleration,
		velocity;
	float mass, F, distance;

	Particle(Vector2 position = {0.f, 0.f}, Vector2 initial_vel = {0, 0}, float mass = 10) noexcept
		: acceleration {0.f}
	{
		this->position = position;
		this->mass = mass;
		this->velocity = initial_vel;
	}

	void update(Vector2 to) noexcept
	{
		distance = std::sqrt(
			std::pow(to.x - this->position.x, 2) +
			std::pow(to.y - this->position.y, 2)
		);
		float angle = std::atan2(
			to.y - this->position.y,
			to.x - this->position.x
		);

		F = Const::Physic::G * ((this->mass * Const::Physic::POINTER_MASS) / std::pow(distance, 2));

		this->acceleration.x = std::cos(angle) * F;
		this->acceleration.y = std::sin(angle) * F;

		this->velocity.x += this->acceleration.x;
		this->velocity.y += this->acceleration.y;

		this->position.x += this->velocity.x / this->mass;
		this->position.y += this->velocity.y / this->mass;
	}

	void draw()
	{
		DrawPixel(
			this->position.x, this->position.y,
			Color {
				255, 255,
				255, 255
			}
		);
	}
};

int main(int argc, char *argv[])
{
	std::srand(std::time(nullptr));

	InitWindow(
			Const::Window::WIDTH,
			Const::Window::HEIGHT,
			Const::Window::CAPTION);

	SetTargetFPS(60);

	std::vector<Particle> particles;
	for(int i = 0; i < 200000; i++)
	{
		particles.push_back(Particle(
				Vector2 {
					static_cast<float>(10.f - std::cos(i) * (std::rand() % 10 + 1)),
					static_cast<float>(600.f - std::sin(i) * (std::rand() % 10 + 1))
				},
				Vector2 {
					15000,
					0
				},
					static_cast<float>(std::rand() % 10 + 10000)
		));
	}

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		for(Particle &particle : particles)
		{
			particle.update(GetMousePosition());
			particle.draw();
		}

		EndDrawing();
	}

	CloseWindow();

	return EXIT_SUCCESS;
}
