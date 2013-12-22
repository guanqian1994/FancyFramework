#include <windows.h>
#include "f2d.h"
#include "ff.h"

#define PI 3.14159

class ExampleApp : public ffAppEventListener {
public:
    ExampleApp() {
        ffApp::Run(this, 800, 600, L"DrawLogo - FancyFramework " FF_VERSION_W);
    }

    void OnCreate(ffApp *pApp) {
        pApp->SetBackgroundColor(ffColors::White);

        ffRes::Get().LoadPath(L"Res", L"data");

        m_curScale = 2.f;

        m_curRotation = PI;

        m_endScale = 1.0f;

        m_endRotation = 0.f;

        m_pSprite = ffSprite::Create(L"Res\\logo_256.png");
    }

    void OnDestroy(ffApp *pApp) {
        m_pSprite->Release();
    }

    void OnRemoveScene(ffScene *pScene) {
        delete pScene;
    }

    bool OnMsg(const f2dMsg &pMsg) {
        switch (pMsg.Type)
        {
        case F2DMSG_WINDOW_ONKEYUP:
            if (pMsg.Param1 == VK_SPACE) {
                m_curScale = 2.f;
                m_curRotation = PI;
            }
            break;
        case F2DMSG_WINDOW_ONCLOSE:
            if (IDYES == MessageBoxW(NULL, L"Are you sure to exit the program ?", L"Exit",
                MB_YESNO | MB_ICONQUESTION))
                return false;
            else
                return true; /// 拦截退出的消息
        default:
            break;
        }
        return false;
    }

    void OnUpdate(fDouble elapsedTime)  {
        if (m_curRotation > m_endRotation) {
            m_curRotation -= (m_curRotation - m_endRotation) * elapsedTime * 3;
        }

        if (m_curScale > m_endScale) {
            m_curScale -= (m_curScale - m_endScale) * elapsedTime * 3;
        }
    }

    void OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph) {
        if (m_pSprite) {
            (*m_pSprite)->Draw(pGraph, fcyVec2(400, 300), fcyVec2(m_curScale, m_curScale), m_curRotation);
        }

        ffDrawer &drawer = ffDrawer::Get();

        drawer.SetColor(ffColors::Black);
        drawer.DrawWString(pGraph, fcyVec2(50, 50), L"Press SPACE to play again.");

    }

private:
    fFloat m_curScale;

    fFloat m_curRotation;

    fFloat m_endScale;

    fFloat m_endRotation;

    ffSprite *m_pSprite;
};

int main() {
    ExampleApp app;
}