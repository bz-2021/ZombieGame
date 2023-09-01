#pragma once
#include "player.hpp"
#include "transparent_image.hpp"
#include "define.h"
#include <unordered_map>
#include <iostream>
#include <bitset>

typedef enum zombie_action {
	frozen,		// 4 frames
	walk,		// 8 frames
	attack,		// 10 frames
	die,		// 6 frames
	headshoot	// 8 frames
} ZombieAction;

// �����ÿ����������4-10֡�������Ӧ��Ϸ�е�֡�ʣ������ٶȻ�ܿ죬����STEP�����ٶȡ�
std::unordered_map<ZombieAction, int> zombieActionFramesMapping = {
	{frozen, 4 * STEP},
	{walk, 8 * STEP},
	{attack, 10 * STEP},
	{die, 6 * STEP},
	{headshoot, 8 * STEP},
};

class Zombie : public Player {
public:
	Zombie(IMAGE*, int d = 0, int f = 0);
	void setFrame();
	void putThisFrameImage(int, int);
	int getDirection();
	void setAction(ZombieAction);
	void setPos(int x, int y);
	int getPosX();
	int getPosY();
	void react(int);

private:
	ZombieAction action;
};

Zombie::Zombie(IMAGE* image, int direction, int frame) 
	: Player(image, direction, frame) 
{
	action = (ZombieAction)0;
}

void Zombie::setFrame() {
	frame++;
	int maxFrames = zombieActionFramesMapping[action];
	if (action == attack && frame == maxFrames) {
		action = frozen;
		frame = 0;
	}
	else if ((action == die || action == headshoot) && frame == maxFrames) {
		frame--;
	}
	else {
		frame %= maxFrames;
	}
}

// ����ǰ״̬��������ʾ����Ļ����
void Zombie::putThisFrameImage(int dstX, int dstY) {
	if (image == NULL) {
		return;
	}
	int srcX, srcY = direction * height;
	int t_frame = frame / STEP;
	switch (action)
	{
	case frozen:
		srcX = t_frame * width;
		break;
	case walk:
		srcX = (t_frame + 4) * width;
		break;
	case attack:
		srcX = (t_frame + 12) * width;
		break;
	case die:
		srcX = (t_frame + 22) * width;
		break;
	case headshoot:
		srcX = (t_frame + 28) * width;
		break;
	default:
		srcX = 100;
	}
	transparentimage3(NULL, dstX / 2 - width / 2, dstY / 2 - height / 2, width, height, srcX, srcY, image);
}

inline int Zombie::getDirection()
{
	return direction;
}

inline void Zombie::setAction(ZombieAction ac)
{
	action = ac;
}

inline void Zombie::setPos(int x, int y)
{
	posX = x, posY = y;
}

inline int Zombie::getPosX()
{
	return posX;
}

inline int Zombie::getPosY()
{
	return posY;
}

// ���ﰴ���û�����������Ӧ 
inline void Zombie::react(int _cmd)
{
	if (action == attack || action == die || action == headshoot) {

	}
	else if (!_cmd) {
		action = frozen;
	}
	else if (_cmd & KEY_J) {
		frame = 0;
		action = attack;
	}
	else if (_cmd & KEY_K) {
		frame = 0;
		action = die;
	}
	else if (_cmd & KEY_L) {
		frame = 0;
		action = headshoot;
	}
	else {
		action = walk;
	}
	_cmd &= ~KEY_J, _cmd &= ~KEY_K, _cmd &= ~KEY_L;
	if (action == walk) {
		switch (direction)
		{
		case 0:
			posX += SPEED;
			break;
		case 1:
			posX += COMPONENTSPEED, posY += COMPONENTSPEED;
			break;
		case 2:
			posY += SPEED;
			break;
		case 3:
			posX -= COMPONENTSPEED, posY += COMPONENTSPEED;
			break;
		case 4:
			posX -= SPEED;
			break;
		case 5:
			posX -= COMPONENTSPEED, posY -= COMPONENTSPEED;
			break;
		case 6:
			posY -= SPEED;
			break;
		case 7:
			posX += COMPONENTSPEED, posY -= COMPONENTSPEED;
			break;
		}
	}
}