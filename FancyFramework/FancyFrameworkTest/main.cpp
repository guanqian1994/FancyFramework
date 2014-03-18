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

#include "ff.h"
#include "ffUI.h"

class MyScene : public ffScene {
protected:
    void OnCreate() {
        AddLayer(pUI = ffUILayer::Create());

        pForm = ffUIForm::Create(pUI, ffPoint(0, 0), ffSize(350, 350));

        for (int i = 0; i != 5; ++i)
            for (int y = 0; y != 5; ++y) {
                ffUIButton *pButton = ffUIButton::Create(pForm, ffPoint(i * 60 + 25, y * 60 + 25), ffSize(50, 50));
                pButton->MouseUp = ffBindWith(&MyScene::OnButtonUp, this);
            }

        ffUILable::Create(pForm, ffPoint(10, 10), ffSize(50, 20), L"xxx\nxxxxxxxxxx");

    }

    void OnButtonUp(ffUIView *pSender, ffUIEvent *pEvent) {
        
    }

    void OnRender(fDouble elapsedTime, ffGraphics *pGraph) {
        pGraph->Begin();
        
        pUI->DebugRender(pGraph);

        pGraph->End();
    }

private:
    ffUILayer *pUI;
    ffUIForm *pForm;
};

class ExampleApp : public ffAppEventListener {
public:
    ExampleApp() {
        ffApp::Run(this, 800, 600, L"FancyFramework " FF_VERSION_W);
    }

    void OnCreate(ffApp &app) {
        ShowCursor(FALSE);
        app.SetBackgroundColor(ffColors::White);

        app.AddScene(new MyScene());
    }

    void OnDestroy(ffApp &app) {
    }

    bool OnMsg(const ffMsg &msg) {
        switch (msg.GetType()) {
        case F2DMSG_WINDOW_ONMOUSEMOVE:
            m_mousePos.x = msg[0].ToInt();
            m_mousePos.y = msg[1].ToInt();
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

    void OnRender(fDouble elapsedTime, ffGraphics *pGraph) {
        pGraph->Begin();

        ffDrawer &drawer = ffDrawer::Get();

        drawer.SetColor(ffColors::Black);
        drawer.DrawSolidRectangle(pGraph, fcyRect(m_mousePos, m_mousePos + fcyVec2(20, 20)));

        pGraph->End();
    }

private:
    fcyVec2 m_mousePos;
};

int main() {
    ExampleApp app;
}