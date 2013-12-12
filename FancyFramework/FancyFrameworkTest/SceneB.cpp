#include <windows.h>
#include "f2d.h"
#include "ff.h"
#include "SceneA.h"
#include "SceneB.h"

bool SceneB::OnMsg(const f2dMsg &pMsg) {
    switch (pMsg.Type)
    {
    case F2DMSG_WINDOW_ONKEYUP:
        switch (pMsg.Param1)
        {
        case 'C':
            ffApp::Get().AddScene(new SceneA);
            ffApp::Get().NextScene();
            break;
        case 'W':
            ffApp::Get().SetWindow(800, 600, true);
            break;
        case 'F':
            ffApp::Get().SetWindow(800, 600, false);
            break;
        default:
            return false;
        }
        return true;
        return true;
    default:
        return false;
    }
}

void SceneB::OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph) {
    ffDrawer &drawer = ffDrawer::Get();

    drawer.SetColor(ffColors::Black);
    drawer.DrawWString(fcyVec2(70, 70),
        L"This is scene B.\n\n"
        L"Press W key , set to window mode\n"
        L"Press F key , set to full screen mode\n\n"
        L"Press C key , go to scene A");
}
