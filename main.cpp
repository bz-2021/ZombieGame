#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "define.h"
#include "zombie.hpp"
#include "transparent_image.hpp"

// 全局变量
IMAGE g_zombie_0;
IMAGE g_skeleton_0;
IMAGE g_big_map;

void LoadResources() {
	loadimage(&g_zombie_0, ZOMBIE_0);
	loadimage(&g_big_map, BIGMAP);
}

void DelayFPS() { // 延迟到下一帧
	static clock_t cRecord = clock();

	clock_t consumption = clock() - cRecord;
	clock_t sleep = 20 - consumption;
	if (sleep > 0)
		Sleep(sleep);
	cRecord = clock();
}

int GetCommand() { // 获取用户键盘输入
	int c = 0;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)		c |= CMD_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)		c |= CMD_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)		c |= CMD_DOWN;
	if (GetAsyncKeyState('J') & 0x8000)			c |= KEY_J;
	if (GetAsyncKeyState('K') & 0x8000)			c |= KEY_K;
	if (GetAsyncKeyState('L') & 0x8000)			c |= KEY_L;
	return c;
}

int main() {

	LoadResources();
	initgraph(WIDTH, HEIGHT);

	Zombie* zombie = new Zombie(&g_zombie_0);
	BeginBatchDraw(); // 开始批量绘图，搭配FlushBatchDraw()使用，防止界面闪烁
	
	while (true) {
		cleardevice();

		putimage(zombie->getPosX(), zombie->getPosY(), &g_big_map);
		zombie->putThisFrameImage(WIDTH, HEIGHT);
		zombie->setFrame(); // 进入到下一帧

		FlushBatchDraw();

		int c = GetCommand();
		zombie->move(c);
		zombie->react(c);
		DelayFPS();
	}

	EndBatchDraw();
	closegraph();
	return 0;
}