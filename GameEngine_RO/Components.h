#pragma once
#include "Engine.h"

struct Transform {

public:
	ECS_DECLARE_TYPE;
	float xpos;
	float ypos;
	float rotation;
	float xspeed;
	float yspeed;
	float xspeedMod;
	float yspeedMod;
	bool bColliding;

	Transform(
		float xpos,
		float ypos,
		float xspeed = 0.0f,
		float yspeed = 0.0f) :
		xpos(xpos),
		ypos(ypos),
		rotation(0),
		xspeed(0.0f),
		yspeed(0.0f),
		xspeedMod(xspeed),
		yspeedMod(yspeed),
		bColliding(false)
	{
		
	}

	void updateSpeed(float x, float y) {
		xspeed = x;
		yspeed = y;
	}

	void move() {
		if (!bColliding) {
			// Halve the speed when moving diagonally
			if (xspeed != 0 && yspeed != 0) {
				xspeed /= 2;
				yspeed /= 2;
			}

			xpos += xspeed;
			ypos += yspeed;
		}
	}
};

struct Sprite2D {
public:
	ECS_DECLARE_TYPE;
	sf::Sprite self;
	std::string filepath;
	int width;
	int height;

	Sprite2D(std::string filepath) {
		this->filepath = filepath;
	}
};

struct Animator {
public:
	ECS_DECLARE_TYPE;
	int spriteWidth;
	int spriteHeight;
	int currentColumn;
	int currentRow;
	int totalColumns;
	int totalRows;

	float currentTime;
	float nextFrameTime;

	bool bFacingRight;

	Animator(int spriteWidth, int spriteHeight, float nextFrameTime, int totalColumns, int totalRows) :
		spriteWidth(spriteWidth), spriteHeight(spriteHeight), nextFrameTime(nextFrameTime), totalColumns(totalColumns), totalRows(totalRows)
	{
		currentColumn = 0;
		currentRow = 0;
		currentTime = 0;
		bFacingRight = true;
	}
};

struct InputController {
public:
	ECS_DECLARE_TYPE;
	bool bInputActive;
	bool bW, bA, bS, bD, bUp, bLeft, bDown, bRight;

	InputController()
	{
		std::memset(this, false, sizeof(InputController));
		bInputActive = true;
	}

};

struct BoxCollider {
public:
	ECS_DECLARE_TYPE;
	int leftEdge, rightEdge, bottomEdge, topEdge;

	BoxCollider()
	{
		std::memset(this, 0, sizeof(BoxCollider));
	}

	void Update(int xside, int yside, int width, int height) {
		leftEdge = xside;
		rightEdge = xside + width;
		topEdge = yside;
		bottomEdge = yside + height;
	}
};


ECS_DEFINE_TYPE(Transform);
ECS_DEFINE_TYPE(Sprite2D);
ECS_DEFINE_TYPE(Animator);
ECS_DEFINE_TYPE(InputController);
ECS_DEFINE_TYPE(BoxCollider);