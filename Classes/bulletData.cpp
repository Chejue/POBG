// Created by ������

#include "bulletData.h"

USING_NS_CC;

bool Bullet::init()
{
	if (!Node::init())
		return false;

	//this->scheduleUpdate();

	return true;
}

void Bullet::bulletInit(Point position)
{
	isActive = false;
	bullet = Sprite::create("gun\\bullet.png");
	bullet->setPosition(position);
	addChild(bullet);
}

void Bullet::shoot(Point position, float direction[2], float speed)
{
	bullet->setPosition(position);
	float shootX = 5.0f * direction[0] / speed;
	float shootY = 5.0f * direction[1] / speed;
	auto moveto = MoveTo::create(speed, Vec2(position.x + shootX, position.y + shootY));
	bullet->runAction(moveto);
}