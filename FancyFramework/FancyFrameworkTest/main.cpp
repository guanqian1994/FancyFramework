#define _CRT_NON_CONFORMING_SWPRINTFS

#include <windows.h>
#include "f2d.h"
#include "ff.h"

#define PI 3.1415926

class FpsPrintLayer : public ffLayer {
public:
    FpsPrintLayer() {
        m_delay = 0.2;
        m_elapse = 0;
    }

    void OnRender(fDouble elapsedTime, ffGraphics *pGraph) {
        pGraph->Begin();

        if (m_elapse >= m_delay){
            m_elapse = 0;
            swprintf_s(m_buffer, L"FPS:%.2f", 1.f / elapsedTime);
        }

        m_elapse += elapsedTime;

        ffDrawer &drawer = ffDrawer::Get();

        drawer.SetColor(ffColors::White);
        drawer.DrawSolidRectangle(pGraph, fcyRect(48, 50, 135, 68));
        drawer.SetColor(ffColors::Black);
        drawer.DrawWString(pGraph, fcyVec2(50, 50), m_buffer);

        pGraph->End();
    }

private:
    fDouble m_delay;
    fDouble m_elapse;
    wchar_t m_buffer[24];
};

class SolidLayer : public ffLayer {
public:
    SolidLayer(fFloat beginScale, fcyColor color) {
        m_scale = beginScale;
        m_color = color;
    }

    void OnUpdate(fDouble elapsedTime) {
        m_scale -= elapsedTime / 10;
        if (m_scale <= 0) {
            m_scale = 1.2f;
            this->BringToFront();
        }
    }

    void OnRender(fDouble elapsedTime, ffGraphics *pGraph) {
        pGraph->Begin();

        ffDrawer &drawer = ffDrawer::Get();

        drawer.SetColor(m_color);

        fFloat scalePixelX = 400 * m_scale;
        fFloat scalePixelY = 300 * m_scale;

        drawer.DrawSolidRectangle(pGraph, 
            fcyRect(400 - scalePixelX, 300 - scalePixelY, 400 + scalePixelX, 300 + scalePixelY));

        pGraph->End();
    }

private:
    fFloat m_scale;
    fcyColor m_color;
};

class ExampleScene : public ffScene {
public:
    void OnCreate() {
        this->AddLayer(new SolidLayer(1.2f, ffColors::White));
        this->AddLayer(new SolidLayer(1.1f, ffColors::Black));
        this->AddLayer(new SolidLayer(1.0f, ffColors::White));
        this->AddLayer(new SolidLayer(0.9f, ffColors::Black));
        this->AddLayer(new SolidLayer(0.8f, ffColors::White));
        this->AddLayer(new SolidLayer(0.7f, ffColors::Black));
        this->AddLayer(new SolidLayer(0.6f, ffColors::White));
        this->AddLayer(new SolidLayer(0.5f, ffColors::Black));
        this->AddLayer(new SolidLayer(0.4f, ffColors::White));
        this->AddLayer(new SolidLayer(0.3f, ffColors::Black));
        this->AddLayer(new SolidLayer(0.2f, ffColors::White));
        this->AddLayer(new SolidLayer(0.1f, ffColors::Black));

        fInt newGroupIndex = this->AddLayerGroup();

        this->AddLayer(new FpsPrintLayer(), newGroupIndex);
    }
};

class ExampleApp : public ffAppEventListener {
public:
    ExampleApp() {
        ffApp::Run(this, 800, 600, L"FancyFramework " FF_VERSION_W);
    }

    void OnCreate(ffApp *pApp) {
        pApp->SetBackgroundColor(ffColors::White);
        pApp->AddScene(new ExampleScene);
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
            break;
        }
        return false;
    }
};

int main() {
    ExampleApp app;
}