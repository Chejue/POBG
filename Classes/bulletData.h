// Created by ³ÂÆôÅô

#ifndef POBG_BULLETDATE_H
#define POBG_BULLETDATE_H

#include "cocos2d.h"

USING_NS_CC;

class Bullet : public cocos2d::Node
{
public:
	bool isActive;
	Sprite* bullet;

	virtual bool init();
	void bulletInit(Point position, bool type);
	void shoot(Point position, float direction[2], float speed);
	//static Bullet* createBullet(Point position);

	CREATE_FUNC(Bullet);
};

#endif //POBG_BULLETDATE_H