#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "define.h"
#include "zombie.hpp"
#include "transparent_image.hpp"
#include "control.hpp"
#include "map.hpp"

// ȫ�ֱ���
IMAGE g_zombie_0;
IMAGE g_skeleton_0;
IMAGE g_big_map;

void LoadResources() {
	loadimage(&g_zombie_0, ZOMBIE_0);
	loadimage(&g_big_map, BIGMAP);
}

int main() {

	LoadResources();
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw(); // ��ʼ������ͼ������FlushBatchDraw()ʹ�ã���ֹ������˸

	GameMap* map = new GameMap(&g_big_map);
	Zombie* zombie = new Zombie(&g_zombie_0);
	
	while (true) {
		cleardevice();

		//putimage(zombie->getPosX(), zombie->getPosY(), &g_big_map);
		map->GrawMap();
		zombie->putThisFrameImageOntoScreenCenter(zombie->getPosX() + map->getX(), zombie->getPosY() + map->getY());
		zombie->setFrame(); // ���뵽��һ֡

		FlushBatchDraw();

		int c = GetPlayer2Command();
		int cmap = GetPlayer1Command();
		zombie->move(c);
		zombie->react(c);
		map->move(cmap);
		DelayFPS();
	}

	EndBatchDraw();
	closegraph();
	return 0;
}