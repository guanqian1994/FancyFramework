#include <windows.h>
#include "f2d.h"
#include "ff.h"

#include "SceneA.h"
#include "SceneB.h"

class ExampleApp : public ffAppEventListener {
public:
    ExampleApp() {
        m_pApp = ffApp::Create(this, 800, 600);
        if (m_pApp)
            m_pApp->Run();
    }

    void OnCreate(ffApp *pApp) {
        ShowCursor(FALSE);
        pApp->SetBackgroundColor(ffColors::Brown);
        pApp->AddScene(new SceneA);
    }

    void OnRemoveScene(ffScene *pScene) {
        delete pScene;
    }

    bool OnMsg(const f2dMsg &pMsg) {
        switch (pMsg.Type)
        {
        case F2DMSG_WINDOW_ONMOUSEMOVE:
            m_mousePos.x = (fInt)pMsg.Param1;
            m_mousePos.y = (fInt)pMsg.Param2;
            return true;
        case F2DMSG_WINDOW_ONCLOSE:
            if (IDYES == MessageBoxW(NULL, L"Are you sure to exit the program ?", L"Exit",
                MB_YESNO | MB_ICONQUESTION))
                return false;
            else
                return true; /// 拦截退出的消息
        default:
            return false;
        }
    }

    void OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph) {
        ffDrawer &drawer = ffDrawer::Get();

        drawer.SetColor(ffColors::White);
        drawer.DrawSolidRectangle(fcyRect(50, 50, 750, 550));
        drawer.SetColor(ffColors::Black);
        drawer.DrawSolidRectangle(fcyRect(m_mousePos.x, m_mousePos.y, m_mousePos.x + 20, m_mousePos.y + 20));
    }
private:
    ffApp *m_pApp;
    fcyVec2 m_mousePos;
};

int main() {
    ExampleApp app;
}