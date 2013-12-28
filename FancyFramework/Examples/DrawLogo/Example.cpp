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

        m_pSprite = ffSprite::Create(L"Res\\logo.png");
    }

    void OnDestroy(ffApp *pApp) {
        m_pSprite->Release();
    }

    bool OnMsg(const f2dMsg &pMsg) {
        switch (pMsg.Type) {
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

    void OnRender(fDouble elapsedTime, ffGraphics *pGraph) {
        pGraph->Begin();

        if (m_pSprite) {
            (*m_pSprite)->Draw(pGraph, fcyVec2(400, 300), fcyVec2(m_curScale, m_curScale), m_curRotation);
        }

        ffDrawer &drawer = ffDrawer::Get();

        drawer.SetColor(ffColors::Black);
        drawer.DrawWString(pGraph, fcyVec2(50, 50), L"Press SPACE to play again.");

        pGraph->End();
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