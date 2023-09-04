#pragma once
#include <graphics.h>
#include "define.h"

class Player {
public:
	void setDirection(int);
	void move(int);
	Player(IMAGE*, int d = 0, int f = 0);

protected:
	IMAGE*	image;		// 序列帧图像的指针
	int		direction;	// 当前方向 0-8
	int		frame;		// 当前动作帧数
	int		height;		// 切割序列帧图像时单位高度
	int		width;		// 切割序列帧图像时单位宽度
	int		posX;		// 所处位置X坐标
	int		posY;		// 所处位置Y坐标
};

Player::Player(IMAGE* playerImage, int d, int f) {
	direction = d;
	frame = f;
	image = playerImage;
	posX = WIDTH / 2;
	posY = HEIGHT / 2;
	width = playerImage->getwidth() / TOTAL_FRAMES;
	height = playerImage->getheight() / TOTAL_DIRECTIONS;
}

void Player::setDirection(int d) {
	direction = d % 8;
}

void Player::move(int _cmd) { // 根据不同的键盘输入设置人物的移动方向
	auto bothPressed = [&_cmd](int a, int b) 
	{
		return (_cmd & a) && (_cmd & b);
	};
	if (bothPressed(CMD_UP, CMD_LEFT)) {
		direction = 1;
	}
	else if (bothPressed(CMD_UP, CMD_RIGHT)) {
		direction = 3;
	}
	else if (bothPressed(CMD_RIGHT, CMD_DOWN)) {
		direction = 5;
	}
	else if (bothPressed(CMD_DOWN, CMD_LEFT)) {
		direction = 7;
	}
	else if (_cmd & CMD_LEFT) {
		direction = 0;
	}
	else if (_cmd & CMD_UP) {
		direction = 2;
	}
	else if (_cmd & CMD_RIGHT) {
		direction = 4;
	}
	else if (_cmd & CMD_DOWN) {
		direction = 6;
	}
}
