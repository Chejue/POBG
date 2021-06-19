// Created by ³ÂÆôÅô

#ifndef POBG_PLAYERDATE_H
#define POBG_PLAYERDATE_H

#include "cocos2d.h"
#include "bulletData.h"

USING_NS_CC;

class Player : public cocos2d::Node
{
public:
    Player(void) {};
    ~Player(void) {};

    CREATE_FUNC(Player);

    Sprite* sprite;
    Sprite* fallSprite;
    bool isFall = true;
    Bullet* playerBullet[30];

    virtual bool init();
    float direct[2] = {};                                   // Direction's X & Y
    char directString1[30] = {};                            // Direction for moving
    char directString2[30] = {};                            // Direction for rolling
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap; // Record whether the KeyCode is pressed or not
    void update(float delta);

private:
    bool canRoll = true;
	Animate* getAnimation(const char* direction, const int iMax, const int F, const int times);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void onMouseMove(Event* event);
    void onMouseDown(Event* event);
};

#endif //POBG_PLAYERDATE_H