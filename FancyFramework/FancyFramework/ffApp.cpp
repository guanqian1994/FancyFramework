/// 一些非接口的实现
#include "ffApp.h"
#include "ffScene.h"

void ffAppEventListener::OnCreate(ffApp *pApp) { 
}

void ffAppEventListener::OnDestroy(ffApp *pApp) { 
}

void ffAppEventListener::OnRemoveScene(ffScene *pScene) {
    delete pScene;
}

bool ffAppEventListener::OnMsg(const f2dMsg &pMsg) { 
    return false; 
}

void ffAppEventListener::OnUpdate(fDouble elapsedTime) { 
}

void ffAppEventListener::OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph) {
}

#define SETCOLORS(name, r, g, b) fcyColor ffColors::name = fcyColor(r, g, b)

SETCOLORS(Black, 0, 0, 0);
SETCOLORS(Blue, 0, 0, 255);
SETCOLORS(Brown, 165, 42, 42);
SETCOLORS(Gold, 255, 215, 0);
SETCOLORS(Gray, 128, 128, 128);
SETCOLORS(Green, 0, 128, 0);
SETCOLORS(Orange, 255, 165, 0);
SETCOLORS(Pink, 255, 192, 203);
SETCOLORS(Purple, 128, 0, 128);
SETCOLORS(Red, 255, 0, 0);
SETCOLORS(Violet, 238, 130, 238);
SETCOLORS(White, 255, 255, 255);
SETCOLORS(Yellow, 255, 255, 0);