#include "InputSystem.h"

InputSystem::InputSystem() = default;

InputSystem::InputSystem(sf::RenderWindow * win)
{
	this->window = win;
}

InputSystem::~InputSystem() = default;

void InputSystem::tick(ECS::World * world, float deltaTime)
{
	GetKeyEvents(world);
}

void InputSystem::GetKeyEvents(ECS::World * world)
{
	world->each<struct InputController>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<struct InputController> input
			)->void
		{
			input->bW = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			input->bA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			input->bS = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			input->bD = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
			input->bUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
			input->bLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
			input->bDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
			input->bRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
			printf("Hello");
		});
}