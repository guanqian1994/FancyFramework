#include <windows.h>
#include "f2d.h"
#include "ff.h"

class ExampleApp : public ffAppEventListener {
public:
    ExampleApp() {
        ffApp::Run(this, 800, 600);
    }

    void OnCreate(ffApp *pApp) {
        pApp->SetBackgroundColor(ffColors::White);

        ffRes::Get().LoadPath(L"Res", L"data");

        if (m_pSound = ffSound::Create(L"Res\\rain.ogg", ffSound::Dynamic | ffSound::GlobalFocus))
            (*m_pSound)->Play();
        m_pSprite = ffSprite::Create(L"Res\\pic.jpg");

    }

    void OnDestroy(ffApp *pApp) {
        m_pSound->Release();
        m_pSprite->Release();
    }

    void OnRemoveScene(ffScene *pScene) {
        delete pScene;
    }

    bool OnMsg(const f2dMsg &pMsg) {
        switch (pMsg.Type)
        {
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
        if (m_pSprite)
            (*m_pSprite)->Draw(pGraph, fcyVec2(400, 300));
    }
private:
    ffSound *m_pSound;
    ffSprite *m_pSprite;
};

int main() {
    ExampleApp app;
}