#include <windows.h>
#include "f2d.h"
#include "ff.h"

#define WINDOW_WIDTH 800
#define WINDOW_HWIGHT 600

class ExampleApp : public ffAppEventListener {
public:
    ExampleApp() {
        m_pApp = ffApp::Create(this, WINDOW_WIDTH, WINDOW_HWIGHT);
        if (m_pApp)
            m_pApp->Run();
    }

    void OnCreate(ffApp *pApp) {
        ShowCursor(FALSE);
        pApp->SetBackgroundColor(ffColors::Brown);
    }

    void OnDestroy(ffApp *pApp) {

    }

    bool OnMsg(const f2dMsg &pMsg) {
        switch (pMsg.Type)
        {
        case F2DMSG_WINDOW_ONMOUSEMOVE:
            m_mousePos.x = (fInt)pMsg.Param1;
            m_mousePos.y = (fInt)pMsg.Param2;
            return true;
        case F2DMSG_WINDOW_ONKEYUP:
            switch (pMsg.Param1)
            {
            case 'W':
                m_pApp->SetWindow(WINDOW_WIDTH, WINDOW_HWIGHT, true);
                break;
            case 'F':
                m_pApp->SetWindow(WINDOW_WIDTH, WINDOW_HWIGHT, false);
                break;
            default:
                return false;
            }
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

    void OnUpdate(fDouble elapsedTime) {

    }

    void OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph) {
        ffDrawer &drawer = ffDrawer::Get();

        drawer.SetColor(ffColors::White);
        drawer.DrawSolidRectangle(fcyRect(50, 50, 750, 550));
        drawer.SetColor(ffColors::Black);
        drawer.DrawSolidRectangle(fcyRect(m_mousePos.x, m_mousePos.y, m_mousePos.x + 20, m_mousePos.y + 20));

        drawer.DrawWString(fcyVec2(70, 70), 
            L"Hello, world!\n\nPress W key , set to window mode\nPress F key , set to full screen mode");
    }
private:
    ffApp *m_pApp;
    fcyVec2 m_mousePos;
};

int main() {
    ExampleApp app;
}