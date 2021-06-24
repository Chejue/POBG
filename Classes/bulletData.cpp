// Created by ������

#include "bulletData.h"
#include "AudioEngine.h"
#include "settings.h"

USING_NS_CC;

bool Bullet::init()
{
	if (!Node::init())
		return false;

	//this->scheduleUpdate();

	return true;
}

/* type: player 0; enemy 1 */
void Bullet::bulletInit(Point position,bool type)
{
	isActive = false;
	if (!type)
		bullet = Sprite::create("gun//bullet.png");
	else
		bullet = Sprite::create("gun//enemyBullet.png");
	bullet->setPosition(position);
	addChild(bullet);
}

void Bullet::shoot(Point position, float direction[2], float speed)
{
	bullet->setPosition(position);
	float shootX = 10.0f * direction[0];
	float shootY = 10.0f * direction[1];
	auto moveto = MoveTo::create(speed, Vec2(position.x + shootX, position.y + shootY));
	/*auto progressFromTo = ProgressFromTo::create(0.5, 100, 0);
	Action* shooting = Sequence::create(moveto, progressFromTo, NULL);*/
	bullet->runAction(moveto);

	auto reloadGunSound = AudioEngine::play2d("music//shoot.mp3", false);
	AudioEngine::setVolume(reloadGunSound, settings::getInstance().effectsVolume);
}