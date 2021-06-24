// Created by ³ÂÆôÅô

#ifndef POBG_ENEMYDATE_H
#define POBG_ENEMYDATE_H

#include "cocos2d.h"
#include "gunData.h"

USING_NS_CC;

class Enemy : public cocos2d::Node {
public:
    Enemy(void) {};

    ~Enemy(void) {};

    CREATE_FUNC(Enemy);

    Sprite *enemy;
    Sprite *fallSprite;
    bool isFall = true;
    bool canMove = true;
    int HP = 100;
    int bossHP = 500;
    bool survive = true;

    Gun *gun;
    int gunType = 1;
    bool canShoot = true;
    Bullet *pistolBullet[PISTOL_BULLET];
    Bullet *rifleBullet[RIFLE_BULLET];

    virtual bool init();

    void enemyInit(Point position, int guntype);

    void Delete();

    void move(Point position);

    void shoot(Point position);

    float direct[2] = {};                // Direction's X & Y
    char directString[30] = {};          // Direction for moving

    Animate *getAnimation(const char *direction, const int iMax, const int F, const int times);
};

#endif //POBG_ENEMYDATE_H