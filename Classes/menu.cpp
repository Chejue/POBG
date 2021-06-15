//
// Created by 冯天阳 on 2021/5/14.
//

#include "menu.h"
#include "menuButton.h"
#include "modeScene.h"
#include "settingsScene.h"
#include "gameScene.h"
#include "AudioEngine.h"
#include "settings.h"

USING_NS_CC;

bool menu::init() {

    auto backgroundAudioID = AudioEngine::play2d("music//test.mp3", true);
    settings::getInstance().backgroundAudioID = backgroundAudioID;
    settings::getInstance().backgroundAudioVolume = 1.0f;

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

    auto background = Sprite::create("res//background.png");
    background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    background->setPosition(origin);
    background->setContentSize(visibleSize);
    layer->addChild(background);

    //menuButton

    auto startButton = menuButton::create("Start Game");
    startButton->::menu::setPosition(visibleSize.width / 2, visibleSize.height / 2 - 50);
    startButton->addClickEventListener(CC_CALLBACK_1(menu::enterGameScene, this));
    layer->addChild(startButton);

    auto settingsButton = menuButton::create("Settings");
    settingsButton->::menu::setPosition(visibleSize.width / 2, visibleSize.height / 2 - 150);
    settingsButton->addClickEventListener(CC_CALLBACK_1(menu::enterSettingsScene, this));
    layer->addChild(settingsButton);

    auto quitButton = menuButton::create("Quit");
    quitButton->::menu::setPosition(visibleSize.width / 2, visibleSize.height / 2 - 250);
    quitButton->addClickEventListener(CC_CALLBACK_1(menu::menuClose, this));
    layer->addChild(quitButton);

    return Scene::init();
}

Scene *menu::createMenuScene() {

    return menu::create();
}

void menu::enterModeScene(Ref *sender) {
    auto modeScene = modeScene::createModeScene();
    auto transitionScene = TransitionFade::create(0.5f, modeScene);
    Director::getInstance()->replaceScene(transitionScene);
}

void menu::enterGameScene(Ref *sender) {
    auto gameScene = gameScene::createGameScene();
    auto transitionScene = TransitionFade::create(0.5f, gameScene);
    Director::getInstance()->replaceScene(transitionScene);
}

void menu::enterSettingsScene(Ref *sender) {
    auto settingsScene = settingsScene::createSettingsScene();
    auto transitionScene = TransitionFade::create(0.5f, settingsScene);
    Director::getInstance()->replaceScene(settingsScene);
}

void menu::menuClose(Ref *sender) {
    Director::getInstance()->end();
}

