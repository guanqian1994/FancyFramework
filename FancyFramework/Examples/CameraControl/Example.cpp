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

#include "ff.h"

#define PI 3.1415926

class CameraStatusPrintLayer : public ffLayer {
public:
    CameraStatusPrintLayer() {
        m_delay = 0.1;
        m_elapse = 0;

        m_pScaleSprite = ffSprite::Create(L"Res\\scale.png");
        m_pMoveSprite = ffSprite::Create(L"Res\\move.png");

        targetStatus = ffCamera::Get().GetStatus();
    }

    ~CameraStatusPrintLayer() {
        m_pScaleSprite.Release();
        m_pMoveSprite.Release();
    }

protected:
    bool OnMsg(const ffMsg &msg) {
        switch (msg.GetType()) {
        case F2DMSG_WINDOW_ONMOUSEWHEEL: {
            if (msg[2].ToDouble() > 0) {
                targetStatus.scale += 0.3;
            } else {
                targetStatus.scale -= 0.3;
            }
        }
        return true;
        case F2DMSG_WINDOW_ONKEYUP:
            if (msg[0].ToChar() == 'R') {
                targetStatus.scale = 1.0;
                targetStatus.position.x = 0;
                targetStatus.position.y = 0;
                return true;
            }
            break;
        default:
            break;
        }
        return false;
    }

    void OnUpdate(fDouble elapsedTime) {
        ffCamera &camera = ffCamera::Get();
        ffMouse &mouse = ffMouse::Get();

        if (mouse.IsLeftDown()) {
            fFloat xCenter = ffApp::Get().GetBufferSize().x / 2.f;
            fFloat yCenter = ffApp::Get().GetBufferSize().y / 2.f;
            targetStatus.position.x += (mouse.GetPos().x - xCenter) * elapsedTime;
            targetStatus.position.y += (mouse.GetPos().y - yCenter) * elapsedTime;
        }

        targetStatus.scale = LimitValue(0.5f, 3.f, targetStatus.scale);
        targetStatus.position.x = LimitValue(-300, 300, targetStatus.position.x);
        targetStatus.position.y = LimitValue(-300, 300, targetStatus.position.y);

        camera.SetScale(camera.GetScale() + (targetStatus.scale - camera.GetScale()) * elapsedTime * 3);
        camera.SetPosition(camera.GetPosition() + (targetStatus.position - camera.GetPosition()) * elapsedTime * 3);
    }

    void OnRender(fDouble elapsedTime, ffGraphics *pGraph) {
        pGraph->Begin();

        if (m_elapse >= m_delay){
            m_elapse = 0;
            ffCameraStatus &status = ffCamera::Get().GetStatus();
            swprintf_s(m_buffer, L"Camera status\n  Scale %.2f\n  Position %.2f, %.2f",
                status.scale, status.position.x, status.position.y);
        }

        m_elapse += elapsedTime;

        ffDrawer &drawer = ffDrawer::Get();

        drawer.SetColor(ffColors::Black);

        drawer.DrawWString(pGraph, fcyVec2(50, 50), m_buffer);

        if (m_pScaleSprite.Valid())
            m_pScaleSprite->Draw(pGraph, fcyVec2(66, 291));

        drawer.DrawWString(pGraph, fcyVec2(102, 271), L"Scale\nWheel");

        if (m_pMoveSprite.Valid())
            m_pMoveSprite->Draw(pGraph, fcyVec2(66, 337));

        drawer.DrawWString(pGraph, fcyVec2(102, 317), L"Rotate\nLeft mouse button & move");

        drawer.DrawWString(pGraph, fcyVec2(102, 363), L"Press R key to reset camera");

        pGraph->End();
    }

private:
    static fFloat LimitValue(fFloat min, fFloat max, fFloat value) {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }

    fDouble m_delay;
    fDouble m_elapse;
    ffSprite::Ref m_pScaleSprite;
    ffSprite::Ref m_pMoveSprite;
    ffCameraStatus targetStatus;
    wchar_t m_buffer[128];
};

class CameraViewScene : public ffScene {
public:
    void OnCreate() {
        this->AddLayer(new CameraStatusPrintLayer);
    }

protected:
    void OnRender(fDouble elapsedTime, ffGraphics *pGraph) {
        pGraph->Begin(ffGraphics::Camera);

        ffDrawer &drawer = ffDrawer::Get();

        drawer.SetColor(ffColors::Black);
        drawer.DrawRectangle(pGraph, fcyRect(-25, -25, 25, 25));
        drawer.DrawCircle(pGraph, fcyVec2(50, 0), 25);

        drawer.SetColor(ffColors::Gray);
        drawer.DrawRectangle(pGraph, fcyRect(-300, -300, 300, 300));

        pGraph->End();
    }
};

class ExampleApp : public ffAppEventListener {
public:
    ExampleApp() {
        ffApp::Run(this, 800, 600, L"CameraControl - FancyFramework " FF_VERSION_W, true, false, F2DAALEVEL_4);
    }

    void OnCreate(ffApp &app) {
        app.SetBackgroundColor(ffColors::White);
        app.AddScene(new CameraViewScene);
    }

    bool OnMsg(const ffMsg &msg) {
        switch (msg.GetType()) {
        case F2DMSG_WINDOW_ONCLOSE:
            if (IDYES == MessageBoxW(NULL, L"Are you sure to exit the program ?", L"Exit",
                MB_YESNO | MB_ICONQUESTION))
                return false;
            else
                return true;
        default:
            break;
        }
        return false;
    }
};

int main() {
    ExampleApp app;
}