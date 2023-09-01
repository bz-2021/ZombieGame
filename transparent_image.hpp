#pragma once
#include <graphics.h>
#pragma comment( lib, "MSIMG32.LIB")

// 用于显示透明图像
void transparentimage3(IMAGE* dstimg, int x, int y, int w, int h, int srcX, int srcY, IMAGE* srcimg) {
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, srcX, srcY, w, h, bf);
}