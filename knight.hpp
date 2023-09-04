#pragma once

#include "player.hpp"
#include <unordered_map>

typedef enum knight_action {
	stance,		// 4 frames
	walk,		// 8 frames
	attack,		// 8 frames
	die,		// 8 frames
	aim,		// 4 frames
} KnightAction;

std::unordered_map<KnightAction, int> knightActionFrameMapping = {
	{stance, 4 * STEP},
	{walk, 8 * STEP},
	{attack, 8 * STEP},
	{die, 8 * STEP},
	{aim, 4 * STEP},
};

class Knight : public Player {
public:
	Knight(IMAGE*, int d = 0, int f = 0);
	void setFrame();

private:
	KnightAction action;
};

Knight::Knight(IMAGE* img, int d, int f) : Player(img, d, f) {
	action = (KnightAction)0;
}

void Knight::setFrame() {
	frame++;
	int maxFrame = knightActionFrameMapping[action];
	if (action == attack && frame == maxFrame) {
		action = stance;
		frame = 0;
	}
	else if (action == die && frame == maxFrame) {
		frame--;
	}
	else {
		frame %= maxFrame;
	}
}

