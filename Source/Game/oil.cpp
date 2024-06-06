#include "stdafx.h"
#include "oil.h"
#include <fstream>

void Oil::oil_init() {
	for (int i = 0; i < 200; i++)
	{
		oil_now[i].LoadBitmapByString({ "Resources/oil/oil.bmp" });
		oil_now[i].SetTopLeft(920 + i*2, 180);
	}
	oil_ruler.LoadBitmapByString({ "Resources/oil/oil_ruler.bmp" });
	oil_ruler.SetTopLeft(920, 170);
}

void Oil::show_oil() {
	for (int i = 0; i < 200; i++)
	{
		if (oil / 50 <= i)break;
		oil_now[i].ShowBitmap(1);
	}
	oil_ruler.ShowBitmap(1);
}

void Oil::oil_decrease(int i) {
	oil -= i;
}

void Oil::reset() {
	oil = 10000;
}