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
///        file :   SceneA.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include "f2d.h"
#include "ff.h"
#include "SceneA.h"
#include "SceneB.h"

bool SceneA::OnMsg(const ffMsg &msg) {
    ffApp &app = ffApp::Get();
    ffMouse &mouse = ffMouse::Get();

    switch (msg.GetType()) {
    case F2DMSG_WINDOW_ONKEYUP:
        switch (msg[0].ToChar()) {
        case 'C':
            app.AddScene(new SceneB);
            app.NextScene();
            break;
        case 'M':
            if (mouse.IsLimit()) {
                mouse.Limit(ffMouse::Disable);
            } else {
                mouse.Limit(ffMouse::Enable);
            }
            
            break;
        default:
            return false;
        }
        return true;
    default:
        return false;
    }
}

void SceneA::OnRender(fDouble elapsedTime, ffGraphics *pGraph) {
    pGraph->Begin();

    ffDrawer &drawer = ffDrawer::Get();

    drawer.SetColor(ffColors::Black);
    drawer.DrawWString(pGraph, fcyVec2(70, 70),
        L"This is scene A.\n"
        L"Press M key , enable/disable mouse limit\n\n"
        L"Press C key , go to scene B");

    pGraph->End();
}
