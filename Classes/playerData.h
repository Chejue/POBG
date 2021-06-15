// Created by ������

#ifndef POBG_PLAYERDATE_H
#define POBG_PLAYERDATE_H

#include "cocos2d.h"

USING_NS_CC;

/*��ɫ*/
class Player : public cocos2d::Node
{
public:
	Player(void) {};
	~Player(void) {};
	CREATE_FUNC(Player);

	Sprite* sprite;
	bool init();              //�����ʼ��
	float direct[2] = {};         //���ﳯ������
	char directString1[30] = {};   //���ﳯ��1
	char directString2[30] = {};   //���ﳯ��2
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;  //��¼����״̬�Ƿ���
	void update(float delta);

private:
	Animate* getAnimation(const char* direction, const int iMax, const int F, const int times);       //�����ƶ�����
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);   // ������̰����¼�
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);  // �������̧���¼�
	void onMouseMove(Event* event);                                    // ��������ƶ��¼�

};




#endif //POBG_PLAYERDATE_H