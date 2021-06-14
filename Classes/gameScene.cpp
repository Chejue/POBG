//
// Created by 冯天阳 on 2021/6/14.
//

#include "gameScene.h"
#include "mapLayer.h"

Scene *gameScene::createGameScene() {
    return gameScene::create();
}

bool gameScene::init() {
    addChild(mapLayer::createMapLayer());

    return Scene::init();
}
