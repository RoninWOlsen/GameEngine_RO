//#include <SFML\Graphics.hpp>
#include "../GameEngine_RO/Engine.h"
#include <iostream>

int main(int argc, char* args[]) {

	// Declare and get instance of singleton

	Engine& gameEngine = Engine::GetInstance();

	sf::RenderWindow window(sf::VideoMode(800, 600), "GameEngine");

	// Create the world for attach entities and systems to
	gameEngine.world = ECS::World::createWorld();

	// Define entities here
	ECS::Entity* bg;
	ECS::Entity* tux;
	ECS::Entity* guy;

	// Add systems to the engine
	gameEngine.AddSystem(new RenderingSystem());
	gameEngine.AddSystem(new AnimationSystem());
	/*gameEngine.AddSystem(new InputSystem(&window));
	gameEngine.AddSystem(new MovementSystem());*/
	gameEngine.AddSystem(new PhysicsSystem());

	// Add entities to the world
	bg = gameEngine.world->create();
	guy = gameEngine.world->create();
	tux = gameEngine.world->create();


	// Assign components to entities after creation
	bg->assign<Transform>(0, 0);
	bg->assign<Sprite2D>("../debug/pics/bg.jpg");

	guy->assign<Transform>(25, 32);
	guy->assign<Sprite2D>("../debug/pics/herosheet.png");
	guy->assign<Animator>(32, 32, 200.0f, 4, 1);
	guy->assign<BoxCollider>();

	tux->assign<Transform>(200, 200, 0.4f, 0.4f);
	tux->assign<Sprite2D>("../debug/pics/tux_from_linux.png");
	tux->assign<Animator>(56, 72, 2000.0f, 3, 9);
	tux->assign<InputController>();
	tux->assign<BoxCollider>();

	std::cout << bg->getEntityId() << " is the entity id" << std::endl;
	std::cout << tux->getEntityId() << " is the entity id" << std::endl;
	std::cout << guy->getEntityId() << " is the entity id" << std::endl;

	// Pass window reference to engine and start
	gameEngine.Start(&window);

	return 0;
}