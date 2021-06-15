// Created by 陈启鹏

#include "playerData.h"

USING_NS_CC;

bool Player::init()
{
    
    /* 降落动画，未完成
        
        sprite = Sprite::create("player fall.png");
        sprite->setPosition(Vec2(640, 600));
        sprite->setScale(0.8f);

        auto fall = MoveTo::create(3.0f, Vec2(640, 290));
    */

    sprite = Sprite::create("left back 1.png");
    sprite->setPosition(Vec2(640, 290));
    sprite->setScale(0.8f);
    addChild(sprite);

    /* 键盘事件监听 */
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    /* 鼠标事件监听 */
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(Player::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    this->scheduleUpdate();

    return true;
}

/* 获取人物移动动画 */
Animate* Player::getAnimation(const char* direction, const int iMax, const int F,const int times)
{
    /* 动画图储存 */
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player.plist");
    Vector<SpriteFrame*> frameArray;
    char str[100];
    for (int i = 1; i <= iMax; i++)
    {
        sprintf_s(str, "%s %d.png", direction, i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        frameArray.pushBack(frame);
    }

    /* 动画设置 */
    Animation* animation = Animation::createWithSpriteFrames(frameArray);
    animation->setLoops(times);
    animation->setDelayPerUnit(0.1f / F);

    return Animate::create(animation);
}

void Player::update(float delta)
{
    /* 键盘控制移动事件 */
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

}

// 定义键盘按下事件
void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) 
{
    keyMap[keyCode] = true;
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
    {
        auto roll = MoveTo::create(0.2, Vec2(sprite->getPositionX() + direct[0], sprite->getPositionY() + direct[1]));
        auto rollAct = getAnimation(directString2, 8, 2, 1);
        Spawn* spawn = Spawn::create(roll, rollAct, nullptr);
        sprite->runAction(spawn);
    }
}

/* 定义键盘抬起事件 */
void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    keyMap[keyCode] = false;
}

/* 定义鼠标移动事件 */
void Player::onMouseMove(Event* event)
{
    EventMouse* e = (EventMouse*)event;

    //获取人物朝向
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

    /* 获取朝向动画 */
    if (!keyMap[cocos2d::EventKeyboard::KeyCode::KEY_SPACE])
        sprite->runAction(getAnimation(directString1, 4, 1, 1));
}