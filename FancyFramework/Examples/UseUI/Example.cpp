////////////////////////////////////////////////////////////////////////////////
/// Copyright(c) 2014, frimin
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

class ExampleScene : public ffScene {
protected:
    void OnCreate() {
        AddLayer(pUI = ffUILayer::Create());

        pUI->SetCursorImage(ffSprite::Create(L"Res\\cursor.png"));

        m_debugRender = false;
        m_en = true;

        ffImageset *imageset = ffImageset::Create(L"Res\\button.xml");

        pDebugRenderButton = ffUIButton::Create(pUI, ffPoint(290, 265), ffSize(220, 70));

        pDebugRenderButton->ImageNormal = imageset->CreateSprite(L"Normal");
        pDebugRenderButton->ImagePush = imageset->CreateSprite(L"Push");
        pDebugRenderButton->Text = L"Debug render";
        pDebugRenderButton->Valign = ffUIButton::ValignMode_Center;
        pDebugRenderButton->Color = ffColors::White;
        pDebugRenderButton->MouseUp = ffBindWith(&ExampleScene::OnDebugRenderButtonMouseUp, this);

        pChangeLanguageButton = ffUIButton::Create(pUI, ffPoint(290, 320), ffSize(220, 70));

        pChangeLanguageButton->ImageNormal = imageset->CreateSprite(L"Normal");
        pChangeLanguageButton->ImagePush = imageset->CreateSprite(L"Push");
        pChangeLanguageButton->Text = L"Change the language";
        pChangeLanguageButton->Valign = ffUIButton::ValignMode_Center;
        pChangeLanguageButton->Color = ffColors::White;
        pChangeLanguageButton->MouseUp = ffBindWith(&ExampleScene::OnChangeLanguageButtonMouseUp, this);

        pLable = ffUILabel::Create(pUI, ffPoint(290, 250), ffSize(220, 24), L"hello world :)");
    }

    void OnDebugRenderButtonMouseUp(ffUIView *pSender, ffUIEvent *pEvent) {
        ffUIMouseEvent *pMouseEvent = static_cast<ffUIMouseEvent*>(pEvent);
        if (pMouseEvent->Button == ffMouseButton::Left) {
            pUI->SetDebugDraw(m_debugRender);
        }
    }

    void OnChangeLanguageButtonMouseUp(ffUIView *pSender, ffUIEvent *pEvent) {
        ffUIMouseEvent *pMouseEvent = static_cast<ffUIMouseEvent*>(pEvent);
        if (pMouseEvent->Button != ffMouseButton::Left) {
            return;
        }
        if (m_en) {
            pLable->Text = L"你好世界！";
            pDebugRenderButton->Text = L"调试绘制模式";
            pChangeLanguageButton->Text = L"变更语言";
        } else {
            pLable->Text = L"hello world :)";
            pDebugRenderButton->Text = L"Debug render";
            pChangeLanguageButton->Text = L"Change the language";
        }

        m_en = !m_en;
    }

private:
    fBool m_en;
    fBool m_debugRender;
    ffUILayer *pUI;
    ffUILabel *pLable;
    ffUIButton *pDebugRenderButton;
    ffUIButton *pChangeLanguageButton;
};

class ExampleApp : public ffAppEventListener {
public:
    ExampleApp() {
        ffApp::Run(this, 800, 600, L"UseUI - FancyFramework " FF_VERSION_W);
    }

    void OnCreate(ffApp &app) {
        ShowCursor(FALSE);
        app.SetBackgroundColor(ffColors::White);

        app.AddScene(new ExampleScene());
    }

    void OnDestroy(ffApp &app) {
    }

    bool OnMsg(const ffMsg &msg) {
        switch (msg.GetType()) {
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
};

int main() {
    ExampleApp app;
}