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

    void OnCreate(ffApp *pApp) {
        pApp->SetBackgroundColor(ffColors::Brown);
    }

    void OnDestroy(ffApp *pApp) {

    }

    bool OnMsg(const f2dMsg *pMsg) {
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
        drawer.DrawWString(fcyVec2(60, 70), L"Hello world!\nÄãºÃ£¬ÊÀ½ç£¡");

        pGraph->End();
    }
private:
    ffApp *pApp;
};

int main() {
    UserApp userapp;
}