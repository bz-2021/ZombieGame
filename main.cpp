#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "define.h"
#include "zombie.hpp"
#include "transparent_image.hpp"
#include "control.hpp"
#include "map.hpp"
#include "knight.hpp"

// 全局变量
IMAGE g_zombie_0;
IMAGE g_knight_0;
IMAGE g_big_map;

void LoadResources() {
	loadimage(&g_zombie_0, ZOMBIE_0);
	loadimage(&g_big_map, BIGMAP);
	loadimage(&g_knight_0, KNIGHT_0);
}

int main() {

	LoadResources();
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw(); // 开始批量绘图，搭配FlushBatchDraw()使用，防止界面闪烁

	GameMap* map = new GameMap(&g_big_map);
	Zombie* zombie = new Zombie(&g_zombie_0);
	Knight* knight = new Knight(&g_knight_0);
	
	while (true) {
		cleardevice();

		//putimage(zombie->getPosX(), zombie->getPosY(), &g_big_map);
		map->GrawMap();
		zombie->putThisFrameImage(zombie->getPosX() + map->getX(), zombie->getPosY() + map->getY());
		zombie->setFrame(); // 进入到下一帧

		knight->putThisFrameImage();
		knight->setFrame();

		int player1_cmd = GetPlayer1Command();
		knight->react(player1_cmd);
		knight->move(player1_cmd);
		map->move(knight->getPosX(), knight->getPosY());

		int player2_cmd = GetPlayer2Command();
		zombie->react(player2_cmd);
		zombie->move(player2_cmd);

		FlushBatchDraw();
		DelayFPS();
	}

	delete zombie;
	delete map;
	delete& g_big_map;
	delete& g_zombie_0;
	delete& g_knight_0;

	EndBatchDraw();
	closegraph();
	
	return 0;
}