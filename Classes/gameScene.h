// Created by 冯天阳

#ifndef POBG_GAMESCENE_H
#define POBG_GAMESCENE_H

#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"
#include "playerData.h"
#include "enemyData.h"

using namespace ui;

class gameScene : public Scene {
public:

    virtual bool init();

    CREATE_FUNC(gameScene);

    TMXTiledMap *map;
    Player *player;
    Enemy* enemy;

    bool isCanReach(float x, float y);

    void update(float dt);

    void timeCounter(float dt);

    void doPause();

    void gameScene::enemyUpdate(float dt);

private:

    Vec2 tileCoordForPosition(const Vec2 position);

};


#endif //POBG_GAMESCENE_H
