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
///        file :   SceneB.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include "f2d.h"
#include "ff.h"
#include "SceneA.h"
#include "SceneB.h"

bool SceneB::OnMsg(const f2dMsg &pMsg) {
    switch (pMsg.Type)
    {
    case F2DMSG_WINDOW_ONKEYUP:
        switch (pMsg.Param1)
        {
        case 'C':
            ffApp::Get().AddScene(new SceneA);
            ffApp::Get().NextScene();
            break;
        case 'W':
            ffApp::Get().SetWindow(800, 600, true);
            break;
        case 'F':
            ffApp::Get().SetWindow(800, 600, false);
            break;
        default:
            return false;
        }
        return true;
        return true;
    default:
        return false;
    }
}

void SceneB::OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph) {
    ffDrawer &drawer = ffDrawer::Get();

    drawer.SetColor(ffColors::Black);
    drawer.DrawWString(pGraph, fcyVec2(70, 70),
        L"This is scene B.\n\n"
        L"Press W key , set to window mode\n"
        L"Press F key , set to full screen mode\n\n"
        L"Press C key , go to scene A");
}
