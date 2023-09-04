#pragma once
#include <graphics.h>

class GameMap {
public:
	GameMap(IMAGE* img, int x = 0, int y = 0) : img(img), posX(x), posY(y) {}
	int getX() { return posX; }
	int getY() { return posY; }
	void setPos(int x, int y) { posX = x, posY = y; }
	void GrawMap() { putimage(posX, posY, img); }
	void move(int, int);

private:
	IMAGE* img;
	int posX;
	int posY;
};

void GameMap::move(int x, int y) { // 根据不同的键盘输入设置地图的移动方向
	posX = x - WIDTH / 2;
	posY = y - HEIGHT / 2;
	//auto bothPressed = [&_cmd](int a, int b)
	//{
	//	return (_cmd & a) && (_cmd & b);
	//};
	//if (bothPressed(CMD_UP, CMD_LEFT)) {
	//	posX += COMPONENTSPEED, posY += COMPONENTSPEED;
	//}
	//else if (bothPressed(CMD_UP, CMD_RIGHT)) {
	//	posX -= COMPONENTSPEED, posY += COMPONENTSPEED;
	//}
	//else if (bothPressed(CMD_RIGHT, CMD_DOWN)) {
	//	posX -= COMPONENTSPEED, posY -= COMPONENTSPEED;
	//}
	//else if (bothPressed(CMD_DOWN, CMD_LEFT)) {
	//	posX += COMPONENTSPEED, posY -= COMPONENTSPEED;
	//}
	//else if (_cmd & CMD_LEFT) {
	//	posX += SPEED;
	//}
	//else if (_cmd & CMD_UP) {
	//	posY += SPEED;
	//}
	//else if (_cmd & CMD_RIGHT) {
	//	posX -= SPEED;
	//}
	//else if (_cmd & CMD_DOWN) {
	//	posY -= SPEED;
	//}
}