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
#include <windows.h>
#include "f2d.h"
#include "ff.h"

#define WINDOW_WIDTH 800
#define WINDOW_HWIGHT 600

class ExampleApp : public ffAppEventListener {
public:
    ExampleApp() {
        ffApp::Run(this, WINDOW_WIDTH, WINDOW_HWIGHT);
    }

    void OnCreate(ffApp *pApp) {
        m_pApp = pApp;

        ShowCursor(FALSE);
        pApp->SetBackgroundColor(ffColors::Brown);
    }

    void OnDestroy(ffApp *pApp) {

    }

    bool OnMsg(const f2dMsg &pMsg) {
        switch (pMsg.Type)
        {
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
                return true; /// �����˳�����Ϣ
        default:
            return false;
        }
    }

    void OnUpdate(fDouble elapsedTime) {

    }

    void OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph) {
        ffDrawer &drawer = ffDrawer::Get();
        ffMouse &mouse = ffMouse::Get();

        drawer.SetColor(ffColors::White);
        drawer.DrawSolidRectangle(pGraph, fcyRect(50, 50, 750, 550));
        drawer.SetColor(ffColors::Black);
        drawer.DrawSolidRectangle(pGraph, fcyRect(mouse.GetPos(), mouse.GetPos() + fcyVec2(20, 20)));

        drawer.DrawWString(pGraph, fcyVec2(70, 70),
            L"Hello, world!\n\nPress W key , set to window mode\nPress F key , set to full screen mode");
    }

private:
    ffApp *m_pApp;
};

int main() {
    ExampleApp app;
}