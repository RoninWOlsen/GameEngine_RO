#include "RenderingSystem.h"
#include <iostream>

sf::Texture* RenderingSystem::loadTexture(std::string filepath)
{
	sf::Texture* texture = new sf::Texture();

	if (!texture->loadFromFile(filepath)) {
		std::cerr << "Error::::-------------------------------" << std::endl;
		std::cerr << "Unable to load image: " << filepath << std::endl << "Is this image the current directory?" << std::endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	return texture;
}

RenderingSystem::RenderingSystem() = default;

RenderingSystem::~RenderingSystem() = default;

void RenderingSystem::tick(ECS::World * world, float deltaTime)
{
	// Clear before drawing all textures
	Engine::GetInstance().window->clear();

	world->each<struct Transform, struct Sprite2D>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<Transform> transform,
			ECS::ComponentHandle<Sprite2D> sprite)->void
		{
			// Check if an entity has their texture loaded
			if (textureMap.count(sprite->filepath) < 1) {
				textureMap[sprite->filepath] = loadTexture(sprite->filepath);
			}
			// If no texture is found, then add a texture to the map
			if (sprite->self.getTexture() == nullptr) {
				sprite->self.setTexture(*textureMap[sprite->filepath]);
				sprite->width = (int) std::floor(sprite->self.getGlobalBounds().width);
				sprite->height = (int) std::floor(sprite->self.getGlobalBounds().height);
			}
			// Update and draw to the screen
			sprite->self.setPosition(transform->xpos, transform->ypos);
			Engine::GetInstance().window->draw(sprite->self);
		});
	// Display updates
	Engine::GetInstance().window->display();
}
