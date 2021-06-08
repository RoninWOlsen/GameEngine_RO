#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(void) = default;

PhysicsSystem::~PhysicsSystem(void) = default;

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<struct BoxCollider> touchingBox, ECS::ComponentHandle<struct BoxCollider> touchedBox, float x, float y)
{
	return
		touchingBox->rightEdge + x > touchedBox->leftEdge &&
		touchedBox->rightEdge > touchingBox->leftEdge + x &&
		touchedBox->bottomEdge + y > touchedBox->topEdge &&
		touchedBox->bottomEdge > touchingBox->bottomEdge + y;
}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<struct BoxCollider> touchingBox, sf::RectangleShape touchedRectangle, float x, float y)
{
	float touchedRectLeft = touchedRectangle.getPosition().x;
	float touchedRectRight = touchedRectLeft + touchedRectangle.getGlobalBounds().width;
	float touchedRectTop = touchedRectangle.getPosition().y;
	float touchedRectBottom = touchedRectTop + touchedRectangle.getGlobalBounds().height;

	return
		touchingBox->rightEdge + x > touchedRectLeft &&
		touchedRectRight > touchingBox->leftEdge + x &&
		touchingBox->bottomEdge + y > touchedRectTop &&
		touchedRectBottom > touchingBox->topEdge + y;
}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<struct BoxCollider> touchingBox, sf::RectangleShape touchedRectangle)
{
	float touchedRectLeft = touchedRectangle.getPosition().x;
	float touchedRectRight = touchedRectLeft + touchedRectangle.getGlobalBounds().width;
	float touchedRectTop = touchedRectangle.getPosition().y;
	float touchedRectBottom = touchedRectTop + touchedRectangle.getGlobalBounds().height;

	return
		touchingBox->rightEdge > touchedRectLeft &&
		touchedRectRight > touchingBox->leftEdge &&
		touchingBox->bottomEdge > touchedRectTop &&
		touchedRectBottom > touchingBox->topEdge;
}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<struct BoxCollider> touchingBox, ECS::ComponentHandle<struct BoxCollider> touchedBox)
{
	return
		touchingBox->rightEdge > touchedBox->leftEdge &&
		touchedBox->rightEdge > touchingBox->leftEdge &&
		touchedBox->bottomEdge > touchedBox->topEdge &&
		touchedBox->bottomEdge > touchingBox->bottomEdge;
}

void PhysicsSystem::PushEntity(ECS::ComponentHandle<struct Transform> transform, ECS::ComponentHandle<struct BoxCollider> touchingBox, ECS::ComponentHandle<struct BoxCollider> touchedBox)
{
	// Scenario dealing with collision from the right side by accelerating rightward
	if (
		transform->xspeed > 0 &&
		touchedBox->rightEdge + transform->xspeed > touchedBox->leftEdge &&
		touchingBox->topEdge < touchedBox->bottomEdge &&
		touchingBox->bottomEdge > touchedBox->topEdge
		) {
		transform->xspeed = 0;
	}
	// Scenario dealing with collision from the bottom side by accelerating downward
	if (
		transform->yspeed > 0 &&
		touchedBox->bottomEdge + transform->yspeed > touchedBox->topEdge &&
		touchingBox->leftEdge < touchedBox->rightEdge &&
		touchingBox->rightEdge > touchedBox->leftEdge
		) {
		transform->yspeed = 0;
	}
	// Scenario dealing with collision from the left side by accelerating leftward
	if (
		transform->xspeed < 0 &&
		touchedBox->leftEdge + transform->xspeed > touchedBox->rightEdge &&
		touchingBox->topEdge < touchedBox->bottomEdge &&
		touchingBox->bottomEdge > touchedBox->topEdge
		) {
		transform->xspeed = 0;
	}
	// Scenario dealing with collision from the top side by accelerating upward
	if (
		transform->yspeed < 0 &&
		touchedBox->topEdge + transform->yspeed > touchedBox->bottomEdge &&
		touchingBox->leftEdge < touchedBox->rightEdge &&
		touchingBox->rightEdge > touchedBox->leftEdge
		) {
		transform->yspeed = 0;
	}
}

void PhysicsSystem::PushEntity(ECS::ComponentHandle<struct Transform> transform, ECS::ComponentHandle<struct BoxCollider> touchingBox, sf::RectangleShape touchedRectangle)
{
	float touchedRectLeft = touchedRectangle.getPosition().x;
	float touchedRectRight = touchedRectLeft + touchedRectangle.getGlobalBounds().width;
	float touchedRectTop = touchedRectangle.getPosition().y;
	float touchedRectBottom = touchedRectTop + touchedRectangle.getGlobalBounds().height;

	// Scenario dealing with collision from the right side by accelerating rightward
	if (
		transform->xspeed > 0 &&
		touchingBox->rightEdge + transform->xspeed > touchedRectLeft &&
		touchingBox->topEdge < touchedRectBottom &&
		touchingBox->bottomEdge > touchedRectTop
		) {
		transform->xspeed = 0;
	}
	// Scenario dealing with collision from the bottom side by accelerating downward
	if (
		transform->yspeed > 0 &&
		touchingBox->bottomEdge + transform->yspeed > touchedRectTop &&
		touchingBox->leftEdge < touchedRectLeft &&
		touchingBox->rightEdge > touchedRectLeft
		) {
		transform->yspeed = 0;
	}
	// Scenario dealing with collision from the left side by accelerating leftward
	if (
		transform->xspeed < 0 &&
		touchingBox->leftEdge + transform->xspeed > touchedRectRight &&
		touchingBox->topEdge < touchedRectBottom &&
		touchingBox->bottomEdge > touchedRectTop
		) {
		transform->xspeed = 0;
	}
	// Scenario dealing with collision from the top side by accelerating upward
	if (
		transform->yspeed < 0 &&
		touchingBox->topEdge + transform->yspeed > touchedRectBottom &&
		touchingBox->leftEdge < touchedRectRight &&
		touchingBox->rightEdge > touchedRectLeft
		) {
		transform->yspeed = 0;
	}
}

void PhysicsSystem::PushEntity(ECS::Entity * touchingEntity, ECS::Entity * touchedEntity)
{
	float newTouchingX = touchingEntity->get<struct Transform>()->xpos;
	float newTouchingY = touchingEntity->get<struct  Transform>()->ypos;
	float newTouchingXSpeed = touchingEntity->get<struct Transform>()->xspeed;
	float newTouchingYSpeed = touchingEntity->get<struct Transform>()->yspeed;
	float newTouchedX = touchedEntity->get<struct Transform>()->xpos;
	float newTouchedY = touchedEntity->get<struct Transform>()->ypos;

	// Travelling rightward, pushing from the left side
	if (newTouchingXSpeed > 0 &&
		newTouchingX < newTouchedX) {
		touchedEntity->get<struct Transform>()->xpos++;
	}
	// Travelling leftward, pushing from the right
	else if (newTouchingXSpeed < 0 &&
		newTouchingX > newTouchedX) {
		touchedEntity->get<struct Transform>()->xpos--;
	}
	// Travelling downward, pushing from the top
	else if (newTouchingYSpeed > 0 &&
		newTouchingY < newTouchedY) {
		touchedEntity->get<struct Transform>()->ypos++;
	}
	// Travelling upward, pushing from the bottom
	else if (newTouchingYSpeed < 0 &&
		newTouchingY > newTouchedY) {
		touchedEntity->get<struct Transform>()->ypos--;
	}
}

void PhysicsSystem::tick(ECS::World * world, float deltaTime)
{
	world->each<struct BoxCollider, struct Sprite2D, struct Transform>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<struct BoxCollider> collider,
			ECS::ComponentHandle<struct Sprite2D> sprite,
			ECS::ComponentHandle<struct Transform> transform)-> void {
				collider->Update(
					transform->xpos,
					transform->ypos,
					sprite->self.getTextureRect().width,
					sprite->self.getTextureRect().height);
		});
	// Collider for box and transform entities
	world->each<struct BoxCollider, struct Transform>(
		[&](ECS::Entity* touchingEntity,
			ECS::ComponentHandle<struct BoxCollider> touchingBox,
			ECS::ComponentHandle<struct Transform> transform) -> void {
				world->each<struct BoxCollider>(
					[&](ECS::Entity* touchedEntity,
						ECS::ComponentHandle<struct BoxCollider> touchedBox) -> void {
							// Statement to avoid comparing the same entity to itself
							if (touchingEntity->getEntityId() == touchedEntity->getEntityId()) {
								return;
							}

							// Initial collision check
							if (!IsColliding(touchingBox, touchedBox)) {
								return;
							}

							// Final collision check
							PushEntity(touchingEntity, touchedEntity);
					});
		});

	// Actual push
	world->each<struct Transform>(
		[&](ECS::Entity* entity, ECS::ComponentHandle<struct Transform> transform) -> void {
			transform->move();
		});
}
