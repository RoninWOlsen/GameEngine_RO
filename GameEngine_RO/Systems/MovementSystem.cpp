#include "MovementSystem.h"
#include <iostream>

MovementSystem::MovementSystem(void) = default;

MovementSystem::~MovementSystem(void) = default;

void MovementSystem::tick(ECS::World * world, float deltaTime)
{
	world->each<InputController, Transform, Animator>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<InputController>input,
			ECS::ComponentHandle<Transform> transform,
			ECS::ComponentHandle<Animator> animator)->void {
				if (input->bInputActive == true) {
					// W
					if (input->bW == true) {
						transform->yspeed = -transform->yspeedMod;
					}
					// S
					else if (input->bS == true)
					{
						transform->yspeed = transform->yspeedMod;
					}
					// Stop
					else {
						animator->currentRow = 0;
						transform->yspeed = 0;
					}

					// A
					if (input->bA == true)
					{
						transform->xspeed = -transform->xspeedMod;
						animator->bFacingRight = false;
						animator->currentRow = 1;
						std::cout << transform->xspeed << std::endl;
					}
					// D
					else if (input->bD == true)
					{
						transform->xspeed = transform->xspeedMod;
						animator->bFacingRight = true;
						animator->currentRow = 1;
					}
					// Stop
					else {
						animator->currentColumn = 0;
						transform->xspeed = 0;
					}
					transform->move();

					printf("X: %f\nY: %f\n", transform->xpos, transform->ypos);
				}

		});
}