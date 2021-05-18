#include "Engine.h"

Engine::Engine() = default;

Engine::~Engine() = default;

void Engine::Start(sf::RenderWindow * window)
{
	bQuit = false;
	this->window = window;
	while (window->isOpen() == true) {

		Update();

	}
}

void Engine::AddSystem(ECS::EntitySystem * system)
{
	world->registerSystem(system);
	world->enableSystem(system);
}

Engine& Engine::GetInstance()
{
	static Engine _instance;

	return _instance;
}

// Run the program as long as the window is open
void Engine::Update()
{
	sf::Event _event;

	while (window->pollEvent(_event) == true) {
		// Close requested event
		if (_event.type == sf::Event::Closed) {

			window->close();

		}

	}
	world->tick(10.0f);
}
