#pragma once

#include <SFML\Graphics.hpp>
#include "ECS.h"
#include "Components.h"
#include "Systems/RenderingSystem.h"
#include "Systems/AnimationSystem.h"

class Engine
{
public:
	sf::RenderWindow* window;
	ECS::World* world;

	void Start(sf::RenderWindow* window);

	void AddSystem(ECS::EntitySystem* system);

	// Singleton - instantiate only once
	static Engine& GetInstance();

private:
	bool bQuit;
	Engine();
	// Required to prevent the reference from being copied, moved, or assigned

	Engine(Engine& copy); // Hide copy constructer

	Engine(Engine&& move); // Hide move constructer

	Engine& operator=(Engine& copy); // Hide assignment operator

	~Engine();

	void Update();

};

