#pragma once

void DelayFPS() { // 延迟到下一帧
	static clock_t cRecord = clock();

	clock_t consumption = clock() - cRecord;
	clock_t sleep = 20 - consumption;
	if (sleep > 0)
		Sleep(sleep);
	cRecord = clock();
}

int GetPlayer1Command() { // 获取用户1键盘输入
	int c = 0;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)		c |= CMD_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)		c |= CMD_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)		c |= CMD_DOWN;
	if (GetAsyncKeyState('J') & 0x8000)			c |= CMD_ATTACK;
	if (GetAsyncKeyState('K') & 0x8000)			c |= CMD_DIE;
	if (GetAsyncKeyState('L') & 0x8000)			c |= KEY_L;
	return c;
}

int GetPlayer2Command() { // 获取用户2键盘输入
	int c = 0;
	if (GetAsyncKeyState('A') & 0x8000)		c |= CMD_LEFT;
	if (GetAsyncKeyState('D') & 0x8000)		c |= CMD_RIGHT;
	if (GetAsyncKeyState('W') & 0x8000)		c |= CMD_UP;
	if (GetAsyncKeyState('S') & 0x8000)		c |= CMD_DOWN;
	if (GetAsyncKeyState('F') & 0x8000)		c |= CMD_ATTACK;
	if (GetAsyncKeyState('G') & 0x8000)		c |= CMD_DIE;
	if (GetAsyncKeyState('H') & 0x8000)		c |= KEY_L;
	return c;
}