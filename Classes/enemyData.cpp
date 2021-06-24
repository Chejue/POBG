// Created by ³ÂÆôÅô

#include "enemyData.h"
#include "AudioEngine.h"
#include "settings.h"

USING_NS_CC;

#define sprintf_s sprintf

bool Enemy::init()
{
    if (!Node::init()) {
        return false;
    }
    return true;
}

void Enemy::enemyInit(Point position, int guntype)
{
    /* opening falling animation */
    fallSprite = Sprite::create("enemy fall.png");
    fallSprite->setPosition(Vec2(position.x, position.y + 70));
    fallSprite->setScale(0.4f);

    auto fallDownFunc = [&]() {
        isFall = false;
        removeChild(fallSprite);
    };
    auto fallDown = CallFunc::create(fallDownFunc);
    auto fall = MoveTo::create(2.7f, Vec2(position.x, position.y));
    Action* falling = Sequence::create(fall, fallDown, NULL);
    this->addChild(fallSprite);
    fallSprite->runAction(falling);

    enemy = Sprite::create("enemy right 1.png");
    enemy->setPosition(position);
    enemy->setScale(0.4f);
    enemy->setVisible(false);
    addChild(enemy);

    gunType = guntype;
    if (gunType == 1)
        for (int i = 0; i < PISTOL_BULLET; i++)
        {
            pistolBullet[i] = Bullet::create();
            pistolBullet[i]->bulletInit(Vec2(0, 0),1);
            addChild(pistolBullet[i]);
        }
    else if (gunType == 2)
        for (int i = 0; i < RIFLE_BULLET; i++)
        {
            rifleBullet[i] = Bullet::create();
            rifleBullet[i]->bulletInit(Vec2(0, 0),1);
            addChild(rifleBullet[i]);
        }
}

/* Gain the player's moving animation */
Animate* Enemy::getAnimation(const char* direction, const int iMax, const int F,const int times)
{
    /* save animation's picture */
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy.plist");
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

void Enemy::move(Point position)
{
    if (isFall)
        return;

    enemy->setVisible(true);

    /* gain direction */
    float xDir = position.x - enemy->getPositionX();
    float yDir = position.y - enemy->getPositionY();
    direct[0] = 150.0f * (xDir / sqrt(xDir * xDir + yDir * yDir));
    direct[1] = 150.0f * (yDir / sqrt(xDir * xDir + yDir * yDir));

    int X = 0, Y = 0;
    if (canMove)
    {
        if (xDir < 0)
            X = -5;
        if (yDir < 0)
            Y = -5;
        if (xDir > 0)
            X = 5;
        if (yDir > 0)
            Y = 5;
    }

    if (X == 0 && Y == 0)
    {
        if (direct[0] < 0)
            enemy->setTexture("enemy stand 1.png");
        if (direct[0] >= 0)
            enemy->setTexture("enemy stand 2.png");
        return;
    }

    /* gain direction's animation */
    if (direct[0] >= 0)
        sprintf_s(directString, "enemy right");
    if (direct[0] < 0)
        sprintf_s(directString, "enemy left");

    auto moveAnimate = getAnimation(directString, 6, 1, 1);
    auto move = MoveTo::create(0.2, Vec2(enemy->getPositionX() + X, enemy->getPositionY() + Y));
    Spawn* spawn = Spawn::create(move, moveAnimate, nullptr);
    enemy->runAction(spawn);
}

void Enemy::shoot(Point position)
{
    float xDir = position.x - enemy->getPositionX();
    float yDir = position.y - enemy->getPositionY();
    if (fabs(xDir) >= 200 || fabs(xDir) >= 200)
        return;

    if (canShoot && !isFall && canMove)
    {
        if (gunType == 1)
            for (int i = 0; i < PISTOL_BULLET; i++)
            {
                if (pistolBullet[i]->isActive == false)
                {
                    canShoot = false;
                    pistolBullet[i]->shoot(enemy->getPosition(), direct, 2.0f);
                    pistolBullet[i]->isActive = true;

                    auto progressFromTo = ProgressFromTo::create(2, 100, 0);
                    auto shootStopFunc = [&]() {
                        canShoot = true;
                    };
                    auto shootStop = CallFunc::create(shootStopFunc);
                    auto sequence = Sequence::create(progressFromTo, shootStop, nullptr);
                    runAction(sequence);
                    break;
                }
            }
        else if (gunType == 2)
            for (int i = 0; i < RIFLE_BULLET; i++)
            {
                if (rifleBullet[i]->isActive == false)
                {
                    canShoot = false;
                    rifleBullet[i]->shoot(enemy->getPosition(), direct, 1.0f);
                    rifleBullet[i]->isActive = true;

                    auto progressFromTo = ProgressFromTo::create(1, 100, 0);
                    auto shootStopFunc = [&]() {
                        canShoot = true;
                    };
                    auto shootStop = CallFunc::create(shootStopFunc);
                    auto sequence = Sequence::create(progressFromTo, shootStop, nullptr);
                    runAction(sequence);
                    break;
                }
            }
    }
}

void Enemy::Delete()
{
    removeChild(enemy);
}