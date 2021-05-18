#pragma once
#include "Engine.h"

struct Transform {

public:
	ECS_DECLARE_TYPE;
	float xpos;
	float ypos;
	float rotation;

	Transform(float newx, float newy)
		: xpos(newx), ypos(newy) {
		rotation = 0.0f;
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


ECS_DEFINE_TYPE(Transform)
ECS_DEFINE_TYPE(Sprite2D)
ECS_DEFINE_TYPE(Animator)