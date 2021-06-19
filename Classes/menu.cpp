// Created by 冯天阳

#include "menu.h"
#include "menuButton.h"
#include "modeScene.h"
#include "settingsScene.h"
#include "gameScene.h"
#include "AudioEngine.h"
#include "settings.h"

USING_NS_CC;

bool menu::init() {

    if (!settings::getInstance().bgmOfMenu_started) {
        auto backgroundAudioOfMenuID = AudioEngine::play2d("music//bgmOfMenu.mp3", true);
        AudioEngine::setVolume(backgroundAudioOfMenuID, settings::getInstance().backgroundAudioOfMenuVolume);
        settings::getInstance().backgroundAudioOfMenuID = backgroundAudioOfMenuID;
        settings::getInstance().bgmOfMenu_started = true;
    }

    //get visibleSize
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //create layer

    auto layer = LayerColor::create();
    layer->setPosition(origin);
    layer->setContentSize(visibleSize);
    addChild(layer);

    //background

    auto background = Sprite::create("res//backgroundOfMenu.png");
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

void menu::enterModeScene(Ref *sender) {
    if (!settings::getInstance().silenced) {
        auto buttonClickedSound = AudioEngine::play2d("music//button_clicked.mp3", false);
        AudioEngine::setVolume(buttonClickedSound, settings::getInstance().effectsVolume);
    }
    auto modeScene = modeScene::create();
    auto transitionScene = TransitionFade::create(0.5f, modeScene);
    Director::getInstance()->replaceScene(transitionScene);
}

void menu::enterGameScene(Ref *sender) {
    if (!settings::getInstance().silenced) {
        auto buttonClickedSound = AudioEngine::play2d("music//button_clicked.mp3", false);
        AudioEngine::setVolume(buttonClickedSound, settings::getInstance().effectsVolume);
    }
    auto gameScene = gameScene::create();
    auto transitionScene = TransitionFade::create(0.5f, gameScene);
    Director::getInstance()->replaceScene(transitionScene);
}

void menu::enterSettingsScene(Ref *sender) {
    if (!settings::getInstance().silenced) {
        auto buttonClickedSound = AudioEngine::play2d("music//button_clicked.mp3", false);
        AudioEngine::setVolume(buttonClickedSound, settings::getInstance().effectsVolume);
    }
    auto settingsScene = settingsScene::create();
    auto transitionScene = TransitionFade::create(0.5f, settingsScene);
    Director::getInstance()->replaceScene(transitionScene);
}

void menu::menuClose(Ref *sender) {
    auto buttonClickedSound = AudioEngine::play2d("music//button_clicked.mp3", false);
    Director::getInstance()->end();
}

