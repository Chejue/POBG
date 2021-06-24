// Created by ³ÂÆôÅô

#ifndef POBG_createBullet_H
#define POBG_createBullet_H

#include "cocos2d.h"

USING_NS_CC;

class createBullet : public cocos2d::Node
{
public:

	Sprite* bullet;

	virtual bool init();
	void bulletInit(Point position, int type);
	
	CREATE_FUNC(createBullet);
};

#endif //POBG_createBullet_H