#include <windows.h>
#include "f2d.h"
#include "ff.h"
#include "SceneA.h"
#include "SceneB.h"

bool SceneA::OnMsg(const f2dMsg &pMsg) {
    switch (pMsg.Type)
    {
    case F2DMSG_WINDOW_ONKEYUP:
        if (pMsg.Param1 == 'C') {
            ffApp::Get().AddScene(new SceneB);
            ffApp::Get().NextScene();
        }
        return true;
    default:
        return false;
    }
}

void SceneA::OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph) {
    ffDrawer &drawer = ffDrawer::Get();

    drawer.SetColor(ffColors::Black);
    drawer.DrawWString(fcyVec2(70, 70),
        L"This is scene A.\n\n"
        L"Press C key , go to scene B");
}
