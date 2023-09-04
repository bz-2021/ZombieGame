#pragma once

// screen size
#define WIDTH		1200
#define HEIGHT		775

#define ZOMBIE_TOTAL_FRAMES 36
#define KNIGHT_TOTAL_FRAMRS 32
#define TOTAL_DIRECTIONS 8

// keys
#define	CMD_UP			1 << 0
#define	CMD_DOWN		1 << 1
#define	CMD_LEFT		1 << 2
#define	CMD_RIGHT		1 << 3
#define CMD_ATTACK			1 << 4
#define CMD_DIE			1 << 5
#define KEY_L			1 << 6

// control
#define STEP	3
#define SPEED	3
#define COMPONENTSPEED (int)(SPEED * 0.7) // 若不转换为int则会导致对角线方向移动速度不一致问题

// resources
#define ZOMBIE_0	_T("./res/zombie_1.png")
#define KNIGHT_0  _T("./res/skeleton_0.png")
#define BIGMAP		_T("./res/big_map.jpg")