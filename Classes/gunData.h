// Created by ³ÂÆôÅô

#ifndef POBG_GUNDATE_H
#define POBG_GUNDATE_H

#include "cocos2d.h"
#include "bulletData.h"

USING_NS_CC;

#define PISTOL_BULLET 15
#define RIFLE_BULLET 45

class Gun : public cocos2d::Node
{
public:
	float direct[2] = {};
	Sprite* collimator;

	Sprite* pistol;
	Sprite* rifle;

	virtual bool init();
	void pistolInit(Point position);
	void rifleInit(Point position);
	void setPosition(Point position, float direction[2]);

	void onMouseDown(Event* event);
	void onMouseMove(Event* event);

	CREATE_FUNC(Gun);
};

#endif //POBG_GUNDATE_H