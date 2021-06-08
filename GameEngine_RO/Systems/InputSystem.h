#pragma once
#include "..\Engine.h"


class InputSystem : public ECS::EntitySystem
{
private:
	sf::RenderWindow* window;

public:
	InputSystem();

	InputSystem(sf::RenderWindow* win);

	~InputSystem();

	void tick(ECS::World* world, float deltaTime) override;

	void GetKeyEvents(ECS::World* world);
};