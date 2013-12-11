#include "f2d.h"
#include "ff.h"

class UserApp : public ffAppEventListener {
public:
    UserApp() {
        pApp = ffApp::Create(this, 800, 600);
        if (pApp) {
            pApp->Run();
        }
    }

    void OnCreate(ffApp &pApp) {
        pApp.SetBackgroundColor(ffColors::Brown);
    }

    void OnDestroy(ffApp &pApp) {

    }

    bool OnMsg(const f2dMsg &pMsg) {
        switch (pMsg.Type)
        {
        case F2DMSG_WINDOW_ONMOUSEMOVE:
            m_mousePos.x = (fInt)pMsg.Param1;
            m_mousePos.y = (fInt)pMsg.Param2;
            break;
        default:
            break;
        }
        return false;
    }

    void OnUpdate(fDouble elapsedTime) {

    }

    void OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph) {
        pApp->ScreenClear();

        pGraph->Begin();

        ffDrawer &drawer = ffDrawer::Get();

        drawer.SetColor(ffColors::White);
        drawer.DrawSolidRectangle(fcyRect(50, 50, 800 - 100, 600 - 100));
        drawer.SetColor(ffColors::Black);
        drawer.DrawSolidRectangle(fcyRect(m_mousePos.x, m_mousePos.y, m_mousePos.x + 20, m_mousePos.y + 20));

        pGraph->End();
    }
private:
    ffApp *pApp;
    fcyVec2 m_mousePos;
};

int main() {
    UserApp userapp;
    // 卧槽尼玛真叼
    // 就是这么屌啊！
}