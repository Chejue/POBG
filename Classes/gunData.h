// Created by ³ÂÆôÅô

#ifndef POBG_GUNDATE_H
#define POBG_GUNDATE_H

#include "cocos2d.h"

USING_NS_CC;

class Gun : public cocos2d::Node
{
public:
	Sprite* pistol;
	Sprite* rifle;

	virtual bool init();
	void gunInit(Point position);
	static Gun* createGun(Point position);


	CREATE_FUNC(Gun);
};

#endif //POBG_GUNDATE_H