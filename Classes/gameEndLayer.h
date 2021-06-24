//
// Created by 冯天阳 on 2021/6/20.
//

#ifndef POBG_GAMEENDLAYER_H
#define POBG_GAMEENDLAYER_H

#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"
#include "string"

using namespace ui;

class gameEndLayer : public Layer {

public:
    virtual bool init();

    CREATE_FUNC(gameEndLayer);

    static Scene *createScene(RenderTexture *sqr, bool isWin);

    void quitCallback(Ref *sender);
};


#endif //POBG_GAMEENDLAYER_H
