// Created by 冯天阳

#include "mapLayer.h"

bool mapLayer::init() {
    auto map = TMXTiledMap::create("map//Desert1.tmx");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    map->setPosition(-325, -300);
    this->addChild(map);
    return Layer::init();
}

Layer *mapLayer::createMapLayer() {
    return mapLayer::create();
}
