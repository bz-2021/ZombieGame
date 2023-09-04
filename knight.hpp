#pragma once

#include "player.hpp"
#include "define.h"
#include "transparent_image.hpp"
#include <unordered_map>

typedef enum knight_action {
	k_stance,	// 4 frames
	k_walk,		// 8 frames
	k_attack,	// 8 frames
	k_die,		// 8 frames
	k_aim,		// 4 frames
} KnightAction;

std::unordered_map<KnightAction, int> knightActionFrameMapping = {
	{k_stance, 4 * STEP},
	{k_walk, 8 * STEP},
	{k_attack, 4 * STEP},
	{k_die, 8 * STEP},
	{k_aim, 4 * STEP},
};

class Knight : public Player {
public:
	Knight(IMAGE*, int d = 0, int f = 0);
	void setFrame();
	void putThisFrameImage();
	void react(int);
	int getPosX() { return posX; };
	int getPosY() { return posY; };

private:
	KnightAction action;
};

Knight::Knight(IMAGE* img, int d, int f) : Player(img, d, f) {
	action = (KnightAction)0;
	width = img->getwidth() / KNIGHT_TOTAL_FRAMRS;
}

void Knight::setFrame() {
	frame++;
	int maxFrame = knightActionFrameMapping[action];
	if ((action == k_attack || action == k_aim) && frame == maxFrame) {
		action = k_stance;
		frame = 0;
	}
	else if (action == k_die && frame == maxFrame) {
		frame--;
	}
	else {
		frame %= maxFrame;
	}
}

// 将当前状态的人物显示到屏幕
void Knight::putThisFrameImage() {
	if (image == NULL) {
		return;
	}
	int srcX, srcY = direction * height;
	int t_frame = frame / STEP;
	switch (action)
	{
	case k_stance:
		srcX = t_frame * width;
		break;
	case k_walk:
		srcX = (t_frame + 4) * width;
		break;
	case k_attack:
		srcX = (t_frame + 12) * width;
		break;
	case k_die:
		srcX = (t_frame + 20) * width;
		break;
	case k_aim:
		srcX = (t_frame + 28) * width;
	}
	transparentimage3(NULL, WIDTH / 2 - width / 2, HEIGHT / 2 - height / 2, width, height, srcX, srcY, image);
}

// 人物按照用户输入做出反应
inline void Knight::react(int _cmd)
{
	if (action == k_attack || action == k_die || action == k_aim) {
		// 不做反应
	}
	else if (!_cmd) {
		action = k_stance;
	}
	else if (_cmd & CMD_ATTACK) {
		frame = 0;
		action = k_attack;
	}
	else if (_cmd & CMD_DIE) {
		frame = 0;
		action = k_die;
	}
	else if (_cmd & KEY_L) {
		frame = 0;
		action = k_aim;
	}
	else {
		action = k_walk;
	}
	if (action == k_walk) {
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