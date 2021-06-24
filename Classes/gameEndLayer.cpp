//
// Created by 冯天阳 on 2021/6/20.
//

#include "gameEndLayer.h"
#include "menuButton.h"
#include "settings.h"

bool gameEndLayer::init() {
    auto background = Sprite::create("res//pauseBackground.png");
    background->setContentSize(Size(640, 360));
    background->setPosition(640, 360);
    background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(background);

    auto quitButton = menuButton::create("Quit");
    quitButton->addClickEventListener(CC_CALLBACK_1(gameEndLayer::quitCallback, this));
    quitButton->::gameEndLayer::setPosition(640, 260);
    addChild(quitButton);

    return Layer::init();
}

Scene *gameEndLayer::createScene(RenderTexture *sqr, bool isWin) {

    auto gameEndScene = Scene::create();
    auto gameEndLayer = gameEndLayer::create();
    gameEndScene->addChild(gameEndLayer, 1);

    auto background = Sprite::createWithTexture(sqr->getSprite()->getTexture());
    background->setPosition(640, 360);
    background->setColor(Color3B::GRAY);
    background->setFlippedY(true);
    gameEndScene->addChild(background, 0);

    std::string result;
    if (isWin)
        result = "Win!";
    else
        result = "Failed!";

    auto resultLabel = Label::createWithTTF(result, "fonts//arial.ttf", 48);
    resultLabel->setPosition(640, 400);
    resultLabel->setTextColor(Color4B::BLACK);
    gameEndScene->addChild(resultLabel, 1);

    return gameEndScene;
}

void gameEndLayer::quitCallback(Ref *sender) {
    AudioEngine::stop(settings::getInstance().backgroundAudioOfGamingID);
    settings::getInstance().bgmOfGaming_started = false;
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();
}
