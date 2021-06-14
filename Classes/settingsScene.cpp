//
// Created by 冯天阳 on 2021/6/14.
//

#include "settingsScene.h"

Scene *settingsScene::createSettingsScene() {
    return settingsScene::create();
}

bool settingsScene::init() {

    auto visibleSize = Director::getInstance()->getVisibleSize();

    return Scene::init();
}
