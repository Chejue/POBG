//
// Created by 冯天阳 on 2021/6/8.
//

#include "modeScene.h"
#include "menuButton.h"
#include "ui/CocosGUI.h"

bool modeScene::init() {
    //get visibleSize

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //create layer

    auto layer = LayerColor::create(Color4B::WHITE);
    layer->setPosition(origin);
    layer->setContentSize(visibleSize);
    addChild(layer);

    //background

    auto background = Sprite::create("background.png");
    background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    background->setPosition(origin);
    background->setContentSize(visibleSize);
    layer->addChild(background);

    return Scene::init();
}

Scene *modeScene::createModeScene() {
    return modeScene::create();
}
