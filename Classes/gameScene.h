// Created by 冯天阳

#ifndef POBG_GAMESCENE_H
#define POBG_GAMESCENE_H

#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"
#include "playerData.h"

using namespace ui;

class gameScene : public Scene {
public:

    virtual bool init();

    CREATE_FUNC(gameScene);

    TMXTiledMap *map;
    Player *player;

    bool isCanReach(float x, float y);

    void update(float delta);

    void doPause();

private:

};


#endif //POBG_GAMESCENE_H
