#pragma once

#include "player.hpp"

typedef enum knight_action {
	stance,		// 4 frames
	walk,		// 8 frames
	attack,		// 8 frames
	die,		// 8 frames
	aim,		// 4 frames
} KnightAction;

class Knight : public Player {

};