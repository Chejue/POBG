// Created by ³ÂÆôÅô

#include "createBullet.h"

USING_NS_CC;

bool createBullet::init()
{
	if (!Node::init())
		return false;

	//this->scheduleUpdate();

	return true;
}

/* type: player 0; enemy 1 */
void createBullet::bulletInit(Point position,int type)
{
	if (type==1)
		bullet = Sprite::create("res//pistol_Bullet.png");
	else
		bullet = Sprite::create("res//rifle_Bullet.png");

	bullet->setPosition(position.x, position.y + 30);
	bullet->setScale(0.5f);
	auto fall = MoveTo::create(0.6f, Vec2(position.x, position.y - 10));
	auto fallDown = MoveTo::create(0.3f, Vec2(position));
	Action* falling = Sequence::create(fall, fallDown, NULL);
	
	addChild(bullet);
	bullet->runAction(falling); 
}