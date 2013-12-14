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
///        file :   ffScene.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffApp.h"
#include "ffScene.h"

/// 一些非接口的实现

void ffAppEventListener::OnCreate(ffApp *pApp) { 
}

void ffAppEventListener::OnDestroy(ffApp *pApp) { 
}

void ffAppEventListener::OnRemoveScene(ffScene *pScene) {
    delete pScene;
}

bool ffAppEventListener::OnMsg(const f2dMsg &pMsg) { 
    return false; 
}

void ffAppEventListener::OnUpdate(fDouble elapsedTime) { 
}

void ffAppEventListener::OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph) {
}

#define SETCOLORS(name, r, g, b) fcyColor ffColors::name = fcyColor(r, g, b)

SETCOLORS(Black, 0, 0, 0);
SETCOLORS(Blue, 0, 0, 255);
SETCOLORS(Brown, 165, 42, 42);
SETCOLORS(Gold, 255, 215, 0);
SETCOLORS(Gray, 128, 128, 128);
SETCOLORS(Green, 0, 128, 0);
SETCOLORS(Orange, 255, 165, 0);
SETCOLORS(Pink, 255, 192, 203);
SETCOLORS(Purple, 128, 0, 128);
SETCOLORS(Red, 255, 0, 0);
SETCOLORS(Violet, 238, 130, 238);
SETCOLORS(White, 255, 255, 255);
SETCOLORS(Yellow, 255, 255, 0);