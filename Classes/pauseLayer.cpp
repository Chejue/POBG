// Created by 冯天阳

#include "pauseLayer.h"
#include "menuButton.h"
#include "settings.h"
#include "settingsScene.h"
#include "menu.h"

bool pauseLayer::init() {

    auto background = Sprite::create("res//pauseBackground.png");
    background->setContentSize(Size(640, 360));
    background->setPosition(640, 360);
    background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(background);

    auto resumeButton = menuButton::create("Resume");
    resumeButton->addClickEventListener(CC_CALLBACK_1(pauseLayer::resumeCallback, this));
    resumeButton->::pauseLayer::setPosition(640, 460);
    addChild(resumeButton);
    auto settingsButton = menuButton::create("Settings");
    settingsButton->addClickEventListener(CC_CALLBACK_1(pauseLayer::settingsCallback, this));
    settingsButton->::pauseLayer::setPosition(640, 360);
    addChild(settingsButton);
    auto quitButton = menuButton::create("Quit");
    quitButton->addClickEventListener(CC_CALLBACK_1(pauseLayer::quitCallback, this));
    quitButton->::pauseLayer::setPosition(640, 260);
    addChild(quitButton);

    return Layer::init();
}


Scene *pauseLayer::createScene(RenderTexture *sqr) {

    auto pauseScene = Scene::create();
    auto pauseLayer = pauseLayer::create();
    pauseScene->addChild(pauseLayer, 1);

    auto background = Sprite::createWithTexture(sqr->getSprite()->getTexture());
    background->setPosition(640, 360);
    background->setColor(Color3B::GRAY);
    background->setFlippedY(true);
    pauseScene->addChild(background, 0);

    return pauseScene;
}

void pauseLayer::resumeCallback(Ref *sender) {
    Director::getInstance()->popScene();
}

void pauseLayer::settingsCallback(Ref *sender) {
    Director::getInstance()->replaceScene(settingsScene::create());
}

void pauseLayer::quitCallback(Ref *sender) {
    AudioEngine::stop(settings::getInstance().backgroundAudioOfGamingID);
    settings::getInstance().bgmOfGaming_started = false;
    Director::getInstance()->replaceScene(menu::create());
}

