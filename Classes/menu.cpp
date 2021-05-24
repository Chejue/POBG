//
// Created by 冯天阳 on 2021/5/14.
//

#include "menu.h"
#include "menuButton.h"

USING_NS_CC;

bool menu::init() {
    if (!Scene::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto layer = LayerColor::create(Color4B::WHITE);
    layer->setPosition(origin);
    layer->setContentSize(visibleSize);
    this->addChild(layer);

    //background

    auto background = Sprite::create("background.png");
    background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    background->setPosition(origin);
    background->setContentSize(visibleSize);
    layer->addChild(background);

    auto startButton = menuButton::create("Start Game");
    startButton->::menu::setPosition(visibleSize.width / 2, visibleSize.height / 2 - 50);
    layer->addChild(startButton);

    auto settingsButton = menuButton::create("Settings");
    settingsButton->::menu::setPosition(visibleSize.width / 2, visibleSize.height / 2 - 120);
    layer->addChild(settingsButton);


    auto helpButton = menuButton::create("Help");
    helpButton->::menu::setPosition(visibleSize.width / 2, visibleSize.height / 2 -190);
    layer->addChild(helpButton);

    auto quitButton = menuButton::create("Quit");
    quitButton->::menu::setPosition(visibleSize.width / 2, visibleSize.height / 2 -260);
    layer->addChild(quitButton);


    return true;
}
