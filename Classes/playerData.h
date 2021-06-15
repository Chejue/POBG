// Created by 陈启鹏

#ifndef POBG_PLAYERDATE_H
#define POBG_PLAYERDATE_H

#include "cocos2d.h"

USING_NS_CC;

/*角色*/
class Player : public cocos2d::Node
{
public:
    Player(void){};
    ~Player(void){};
    CREATE_FUNC(Player);

    Sprite *sprite;
    bool init();											//人物初始化
    float direct[2] = {};									//人物朝向坐标
    char directString1[30] = {};							//人物朝向1
    char directString2[30] = {};							//人物朝向2
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap; //记录按键状态是否按下
    void update(float delta);

private:
    Animate *getAnimation(const char *direction, const int iMax, const int F, const int times); //人物移动动画
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);							// 定义键盘按下事件
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);							// 定义键盘抬起事件
    void onMouseMove(Event *event);																// 定义鼠标移动事件
};

#endif //POBG_PLAYERDATE_H