#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "define.h"
#include "zombie.hpp"
#include "transparent_image.hpp"

// ȫ�ֱ���
IMAGE g_zombie_0;
IMAGE g_skeleton_0;
IMAGE g_big_map;

void LoadResources() {
	loadimage(&g_zombie_0, ZOMBIE_0);
	loadimage(&g_big_map, BIGMAP);
}

void DelayFPS() { // �ӳٵ���һ֡
	static clock_t cRecord = clock();

	clock_t consumption = clock() - cRecord;
	clock_t sleep = 20 - consumption;
	if (sleep > 0)
		Sleep(sleep);
	cRecord = clock();
}

int GetCommand() { // ��ȡ�û���������
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
	BeginBatchDraw(); // ��ʼ������ͼ������FlushBatchDraw()ʹ�ã���ֹ������˸
	
	while (true) {
		cleardevice();

		putimage(zombie->getPosX(), zombie->getPosY(), &g_big_map);
		zombie->putThisFrameImage(WIDTH, HEIGHT);
		zombie->setFrame(); // ���뵽��һ֡

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