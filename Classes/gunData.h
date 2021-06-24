// Created by ������

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
	Sprite* reloading;

	Sprite* pistol;
	Sprite* rifle;

	virtual bool init();
	void pistolInit(Point position, bool visible);
	void rifleInit(Point position, bool visible);
	void setGun(Point position, float direction[2], int gunType);
	void reloadAnimation();

	void onMouseMove(Event* event);

	CREATE_FUNC(Gun);
};

#endif //POBG_GUNDATE_H