// Created by ³ÂÆôÅô

#include "gunData.h"
#define sprintf_s sprintf

USING_NS_CC;

bool Gun::init()
{
	if (!Node::init())
		return false;

    collimator= Sprite::create("gun//collimator.png");
    reloading= Sprite::create("gun//gunReloading.png");
    collimator->setScale(0.2f);
    reloading->setScale(0.2f);
    reloading->setVisible(false);
    addChild(collimator);
    addChild(reloading);

	auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(Gun::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

void Gun::pistolInit(Point position,bool visible)
{
    pistol = Sprite::create();
    pistol->setPosition(position);
    pistol->setScale(0.5f);
    pistol->setVisible(visible);
    addChild(pistol);
}

void Gun::rifleInit(Point position, bool visible)
{
    rifle = Sprite::create();
    rifle->setPosition(position);
    rifle->setScale(0.2f);
    rifle->setVisible(visible);
    addChild(rifle);
}

void Gun::onMouseMove(Event* event)
{
    EventMouse* e = (EventMouse*)event;
    collimator->setPosition(e->getCursorX(), e->getCursorY());
    reloading->setPosition(e->getCursorX(), e->getCursorY());

    float xDir = e->getCursorX() - pistol->getPositionX();
    float yDir = e->getCursorY() - pistol->getPositionY();
    direct[0] = 150.0f * (xDir / sqrt(xDir * xDir + yDir * yDir));
    direct[1] = 150.0f * (yDir / sqrt(xDir * xDir + yDir * yDir));
}

void Gun::setGun(Point position,float direction[2],int gunType)
{
    const char* gunName;
    char str[30];

    if (gunType == 1)
    {
        rifle->setVisible(false);
        pistol->setVisible(true);
        pistol->setPosition(position);
        gunName = "pistol";
    }
    else if (gunType == 2)
    {
        pistol->setVisible(false);
        rifle->setVisible(true);
        rifle->setPosition(position);
        gunName = "rifle";
    }
    if (direction[0] >= 0 && direction[1] >= 0)
        sprintf_s(str, "gun//%s %d.png", gunName, 1);
    else if (direction[0] > 0 && direction[1] < 0)
        sprintf_s(str, "gun//%s %d.png", gunName, 2);
    else if (direction[0] < 0 && direction[1] >0)
        sprintf_s(str, "gun//%s %d.png", gunName, 3);
    else if (direction[0] <= 0 && direction[1] <= 0)
        sprintf_s(str, "gun//%s %d.png", gunName, 4);

    if (gunType == 1)
        pistol->setTexture(str);
   else if (gunType == 2)
       rifle->setTexture(str);
}

void Gun::reloadAnimation()
{
    reloading->setVisible(true);
    auto progressFromTo = ProgressFromTo::create(2, 100, 0);
    auto loadDoneFunc = [&]() {
        reloading->setVisible(false);
    };
    auto loadDone = CallFunc::create(loadDoneFunc);

    Action* loading = Sequence::create(progressFromTo, loadDone, NULL);

    reloading->runAction(loading);
}