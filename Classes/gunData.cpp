// Created by ³ÂÆôÅô

#include "gunData.h"
#include "bulletData.h"

USING_NS_CC;

bool Gun::init()
{
	if (!Node::init())
		return false;

    collimator= Sprite::create("gun\\collimator.png");

    collimator->setScale(0.1f);
    addChild(collimator);

	auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(Gun::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

void Gun::pistolInit(Point position)
{
    pistol = Sprite::create("gun\\pistol 1.png");
    pistol->setPosition(position);
    pistol->setScale(0.5f);
    pistol->setVisible(false);
    addChild(pistol);
}

void Gun::rifleInit(Point position)
{
    rifle = Sprite::create("gun\\rifle.png");
    rifle->setPosition(position);
    pistol->setScale(0.5f);
    addChild(rifle);
}

void Gun::onMouseMove(Event* event)
{
    EventMouse* e = (EventMouse*)event;
    collimator->setPosition(e->getCursorX(), e->getCursorY());

    float xDir = e->getCursorX() - pistol->getPositionX();
    float yDir = e->getCursorY() - pistol->getPositionY();
    direct[0] = 150.0f * (xDir / sqrt(xDir * xDir + yDir * yDir));
    direct[1] = 150.0f * (yDir / sqrt(xDir * xDir + yDir * yDir));
}

void Gun::setPosition(Point position,float direction[2])
{
    pistol->setVisible(true);
    pistol->setPosition(position);
    if (direction[0] >= 0 && direction[1] >= 0)
        pistol->setTexture("gun\\pistol 1.png");
    else if (direction[0] > 0 && direction[1] < 0)
        pistol->setTexture("gun\\pistol 2.png");
    else if (direction[0] < 0 && direction[1] >0)
        pistol->setTexture("gun\\pistol 3.png");
    else if (direction[0] <= 0 && direction[1] <= 0)
        pistol->setTexture("gun\\pistol 4.png");
}