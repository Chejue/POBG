// Created by ³ÂÆôÅô

#include "playerData.h"
#include "bulletData.h"

USING_NS_CC;

bool Player::init()
{
    /* opening falling animation */
    fallSprite = Sprite::create("player fall.png");
    fallSprite->setPosition(Vec2(640, 600));
    fallSprite->setScale(0.8f);

    auto fallDownFunc = [&]() 
    {
        isFall = false;
        removeChild(fallSprite);
    };
    auto fallDown = CallFunc::create(fallDownFunc);
    auto fall = MoveTo::create(3.0f, Vec2(640, 350));
    Action* falling = Sequence::create(fall, fallDown, NULL);
    this->addChild(fallSprite);
    fallSprite->runAction(falling);


    sprite = Sprite::create("right back 1.png");
    sprite->setPosition(Vec2(640, 260));
    sprite->setScale(0.8f);
    addChild(sprite);

    /* Keyboard Listener */
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    /* Mouse Listener */
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(Player::onMouseMove, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(Player::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    for (int i = 0; i < 30; i++)
    {
        playerBullet[i] = Bullet::create();
        playerBullet[i]->bulletInit(Vec2(0, 0));
        addChild(playerBullet[i]);
    }

    this->scheduleUpdate();

    return true;
}

/* Gain the player's moving animation */
Animate* Player::getAnimation(const char* direction, const int iMax, const int F,const int times)
{
    /* save animation's picture */
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player.plist");
    Vector<SpriteFrame*> frameArray;
    char str[100];
    for (int i = 1; i <= iMax; i++)
    {
        sprintf_s(str, "%s %d.png", direction, i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        frameArray.pushBack(frame);
    }

    /* sit animate */
    Animation* animation = Animation::createWithSpriteFrames(frameArray);
    animation->setLoops(times);
    animation->setDelayPerUnit(0.1f / F);

    return Animate::create(animation);
}

void Player::update(float delta)
{
    if (isFall)
        sprite->setVisible(false);
    else
        sprite->setVisible(true);

    /* using keyboard to control player's moving */
    auto A = cocos2d::EventKeyboard::KeyCode::KEY_A;
    auto S = cocos2d::EventKeyboard::KeyCode::KEY_S;
    auto D = cocos2d::EventKeyboard::KeyCode::KEY_D;
    auto W = cocos2d::EventKeyboard::KeyCode::KEY_W;

    int X = 0, Y = 0;
    if (!keyMap[cocos2d::EventKeyboard::KeyCode::KEY_SPACE])
    {
        if (keyMap[A])
            X = -3;
        if (keyMap[S])
            Y = -3;
        if (keyMap[D])
            X = 3;
        if (keyMap[W])
            Y = 3;
    }
    if (X == 0 && Y == 0)
        return;

    auto move = MoveTo::create(0.2, Vec2(sprite->getPositionX() + X, sprite->getPositionY() + Y));
    sprite->runAction(move);

    for (int i = 0; i < 30; i++)
    {
        if (playerBullet[i]->isActive == true)
        {
            //playerBullet[i]->isActive == false;
        }
    }
}

void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) 
{
    keyMap[keyCode] = true;
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE && canRoll)
    {
        canRoll = false;
        sprite->stopAllActions();
        auto progressFromTo = ProgressFromTo::create(3, 100, 0);
        auto rollFunc = [&]()
        {
            canRoll = true;
        };
        auto rollfunc = CallFunc::create(rollFunc);
        auto sequence = Sequence::create(progressFromTo, rollfunc, nullptr);
        auto rollTo = MoveTo::create(0.2, Vec2(sprite->getPositionX() + direct[0], sprite->getPositionY() + direct[1]));
        auto rollAct = getAnimation(directString2, 8, 2, 1);
        Spawn* spawn = Spawn::create(rollTo, rollAct, sequence, nullptr);
        sprite->runAction(spawn);
    }
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    keyMap[keyCode] = false;
}

void Player::onMouseMove(Event* event)
{
    EventMouse* e = (EventMouse*)event;

    /* gain direction */
    float xDir = e->getCursorX() - sprite->getPositionX();
    float yDir = e->getCursorY() - sprite->getPositionY();
    direct[0] = 150.0f * (xDir / sqrt(xDir * xDir + yDir * yDir));
    direct[1] = 150.0f * (yDir / sqrt(xDir * xDir + yDir * yDir));
    if (direct[0] >= 0 && direct[1] >= 0)
    {
        sprintf_s(directString1, "right back");
        sprintf_s(directString2, "rightb roll");
    }
    if (direct[0] > 0 && direct[1] < 0)
    {
        sprintf_s(directString1, "right front");
        sprintf_s(directString2, "rightf roll");
    }
    if (direct[0] < 0 && direct[1] >0)
    {
        sprintf_s(directString1, "left back");
        sprintf_s(directString2, "leftb roll");
    }
    if (direct[0] <= 0 && direct[1] <= 0)
    {
        sprintf_s(directString1, "left front");
        sprintf_s(directString2, "leftf roll");
    }

    /* gain direction's animation */
    if (!keyMap[cocos2d::EventKeyboard::KeyCode::KEY_SPACE])
        sprite->runAction(getAnimation(directString1, 5, 1, -1));
}

void Player::onMouseDown(Event* event)
{
    EventMouse* e = (EventMouse*)event;
    
    if (e->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
    {
        for (int i = 0; i < 30; i++)
        {
            if (playerBullet[i]->isActive == false)
            {
                playerBullet[i]->isActive = true;
                playerBullet[i]->shoot(sprite->getPosition(), direct, 0.5);

                break;
            }
        }  
    }
}
