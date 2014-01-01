////////////////////////////////////////////////////////////////////////////////
/// Copyright(c) 2013, frimin
/// All rights reserved.
/// 
/// Redistribution and use in source and binary forms, with or without modification,
/// are permitted provided that the following conditions are met :
/// 
/// * Redistributions of source code must retain the above copyright notice, this
/// list of conditions and the following disclaimer.
/// 
/// * Redistributions in binary form must reproduce the above copyright notice, this
/// list of conditions and the following disclaimer in the documentation and / or
/// other materials provided with the distribution.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
/// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
/// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
/// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
/// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
/// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
/// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
/// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
/// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
/// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///        file :   Example.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
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
        ffApp::Run(this, 800, 600, L"SolidLayers - FancyFramework " FF_VERSION_W);
    }

    void OnCreate(ffApp *pApp) {
        pApp->SetBackgroundColor(ffColors::White);
        pApp->AddScene(new ExampleScene);
    }

    bool OnMsg(const f2dMsg &pMsg) {
        switch (pMsg.Type) {
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