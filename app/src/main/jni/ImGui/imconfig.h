#pragma once

namespace {
	int (*ANativeWindow_getWidth_)(const void* window);
}






static int screenWidth = -1, glWidth, screenHeight = -1, glHeight;


static float scaleX,scaleY;
static float density = -1;

void displayKeyboard(bool pShow);





