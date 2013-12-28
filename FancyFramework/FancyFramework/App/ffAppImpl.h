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
///        file :   ffAppImpl.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <fcyRefObj.h>
#include <f2d.h>
#include <list>
#include "..\ffApp.h"

class ffDrawerImpl;
class ffMouseImpl;
class ffKeyboardImpl;
class ffResImpl;
class ffDrawerImpl;
class ffGraphicsImpl;
class ffCameraImpl;

typedef std::list<ffScene*> ffSceneList;

////////////////////////////////////////////////////////////////////////////////
/// @brief 框架主类接口实现
////////////////////////////////////////////////////////////////////////////////
class ffAppImpl :
    public f2dEngineEventListener,
    public f2dRenderDeviceEventListener,
    public fcyRefObjImpl<ffApp> {
public:
    static ffAppImpl &Get();

    ffAppImpl(ffAppEventListener *pListener, fFloat width, fFloat height, fcStrW title, fBool windowed, fBool vsync, F2DAALEVEL aa);

    ~ffAppImpl();

    virtual f2dEngine *GetEngine();

    virtual f2dRenderDevice *GetRenderDevice();

    virtual ffGraphics *GetGraphics2D();

    virtual fcyVec2 GetWindowSize();

    virtual void *GetBuffer();

    virtual void SetWindow(fFloat width, fFloat height, fBool windowed, fBool vsync, F2DAALEVEL aa);

    virtual void SetBackgroundColor(const fcyColor &color);

    virtual void ScreenClear();

    virtual void AddScene(ffScene *pScene);

    virtual size_t GetSceneCount() const;

    virtual ffScene *GetCurrentScene();

    virtual void NextScene();

    virtual void RemoveScene(ffScene *pScene);

    virtual void ClearScene();

    void Run();

/// 内部方法
private:
    /// 监听事件重写
    virtual fBool OnUpdate(fDouble elapsedTime, f2dFPSController *pFPSController, f2dMsgPump *pMsgPump);

    virtual fBool OnRender(fDouble elapsedTime, f2dFPSController *pFPSController);

    virtual void OnRenderDeviceLost() {}

    virtual void OnRenderDeviceReset(){}

private:
    static ffAppImpl *s_pSingleton;

    /// 全局缓冲区
    void *m_pBuffer;

    fcyColor m_backgroundColor;

    ffMouseImpl         *m_pMouse;

    ffKeyboardImpl      *m_pKeyboard;

    ffResImpl           *m_pRes;

    ffCameraImpl        *m_pCamera;

    ffDrawerImpl        *m_pDrawer;

    ffSceneList         m_sceneList;

    /// 将要移除的列表
    ffSceneList         m_removeSceneList;

    ffGraphicsImpl      *m_pGraph;

    f2dGraphics2D       *m_pF2dGraph;

    ffAppEventListener  *m_eventListener;

    f2dEngine           *m_pEngine;

    f2dRenderDevice     *m_pDev;
};