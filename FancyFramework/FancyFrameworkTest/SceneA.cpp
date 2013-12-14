#include <windows.h>
#include "f2d.h"
#include "ff.h"
#include "SceneA.h"
#include "SceneB.h"

bool SceneA::OnMsg(const f2dMsg &pMsg) {
    ffApp &pApp = ffApp::Get();

    switch (pMsg.Type)
    {
    case F2DMSG_WINDOW_ONKEYUP:
        switch (pMsg.Param1)
        {
        case 'C':
            pApp.AddScene(new SceneB);
            pApp.NextScene();
            break;
        case 'M':
            pApp.MouseLock(!pApp.IsEnabledMouseLock());
            break;
        default:
            return false;
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
        L"This is scene A.\n"
        L"Press M key , enable/disable mouse lock\n\n"
        L"Press C key , go to scene B");
}
