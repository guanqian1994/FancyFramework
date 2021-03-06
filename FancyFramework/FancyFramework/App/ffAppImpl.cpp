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
///        file :   ffAppImpl.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffAppImpl.h"

#include "fcyException.h"
#include "ffCameraImpl.h"
#include "ffDrawerImpl.h"
#include "ffGraphicsImpl.h"
#include "..\ffScene.h"
#include "..\ffAssert.h"
#include "..\Res\ffResImpl.h"
#include "..\Input\ffMouseImpl.h"
#include "..\Input\ffKeyboardImpl.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief 框架主类接口实现
////////////////////////////////////////////////////////////////////////////////
ffApp &ffApp::Get() {
    return ffAppImpl::Get();
}

ffAppImpl *ffAppImpl::s_pSingleton = NULL;

ffAppImpl &ffAppImpl::Get() {
    return *s_pSingleton;
}

void ffApp::Run(ffAppEventListener *pListener, fFloat width, fFloat height, fcStrW title, fBool windowed, fBool vsync, F2DAALEVEL aa) {
    ffAppImpl(pListener, width, height, title, windowed, vsync, aa).Run();
}

ffAppImpl::ffAppImpl(ffAppEventListener *pListener, fFloat width, fFloat height, fcStrW title, fBool windowed, fBool vsync, F2DAALEVEL aa) {

    ffAssert(!s_pSingleton);

    if (FCYFAILED(CreateF2DEngineAndInit
        (F2DVERSION, fcyRect(50, 50, 50 + width, 50 + height),
        title, windowed, vsync, aa, this, &m_pEngine))) {
        throw fcyException("Application Failed to Initialize", "");
    }

    /// 初始化 f2d 引擎
    m_pDev = m_pEngine->GetRenderer()->GetDevice();

    m_pDev->CreateGraphics2D(0, 0, &m_pF2dGraph);
    /// 设置资源目录
    m_pEngine->GetFileSys()->LoadRealPath(L"Res", L"data");
    m_pDev->AttachListener(this);

    s_pSingleton = this;

    m_pRes = new ffResImpl();

    m_pCamera = new ffCameraImpl(m_pF2dGraph);

    m_pGraph = new ffGraphicsImpl(m_pF2dGraph, m_pCamera);

    m_pDrawer = new ffDrawerImpl(m_pEngine->GetRenderer(), m_pF2dGraph);

    m_pMouse = new ffMouseImpl(this);

    m_pKeyboard = new ffKeyboardImpl(this);

    m_eventListener = pListener;

    m_eventListener->OnCreate(*this);
}

ffAppImpl::~ffAppImpl() {
    
    while (!m_sceneList.empty()) {
        m_eventListener->OnRemoveScene(m_sceneList.front());
        m_sceneList.pop_front();
    }

    while (!m_removeSceneList.empty()) {
        m_eventListener->OnRemoveScene(m_removeSceneList.front());
        m_removeSceneList.pop_front();
    }

    m_eventListener->OnDestroy(*this);

    FCYSAFEKILL(m_pKeyboard);
    FCYSAFEKILL(m_pMouse);
    FCYSAFEKILL(m_pDrawer);
    FCYSAFEKILL(m_pCamera);
    FCYSAFEKILL(m_pGraph);
    FCYSAFEKILL(m_pRes);
    FCYSAFEKILL(m_pF2dGraph);
    m_pDev->RemoveListener(this);
    FCYSAFEKILL(m_pEngine);
    
    s_pSingleton = NULL;
}

f2dEngine *ffAppImpl::GetEngine() {
    return m_pEngine;
}

f2dRenderDevice *ffAppImpl::GetRenderDevice() {
    return m_pDev;
}

ffGraphics *ffAppImpl::GetGraphics2D() {
    return m_pGraph;
}

fcyVec2 ffAppImpl::GetBufferSize() {
    return fcyVec2(m_pDev->GetBufferWidth(), m_pDev->GetBufferHeight());
}

void ffAppImpl::SetWindow(fFloat width, fFloat height, fBool windowed, fBool vsync, F2DAALEVEL aa) {
    if (windowed) {
        m_pDev->SetBufferSize(width, height, true, vsync, aa);
        m_pEngine->GetMainWindow()->SetBorderType(F2DWINBORDERTYPE_FIXED);
        m_pEngine->GetMainWindow()->SetClientRect(fcyRect(50, 50, 50 + width, 50 + height));

        m_pEngine->GetMainWindow()->SetTopMost(false);
        m_pEngine->GetMainWindow()->SetVisiable(true);
    }
    else {
        m_pDev->SetBufferSize(width, height, false, vsync, aa);
        m_pEngine->GetMainWindow()->SetClientRect(fcyRect(0, 0, width, height));
    }
}

void ffAppImpl::SetBackgroundColor(const fcyColor &color) {
    m_backgroundColor = color;
}

void ffAppImpl::Run() {
    m_pEngine->GetMainWindow()->SetVisiable(true);
    m_pEngine->Run(F2DENGTHREADMODE_MULTITHREAD);
}

void ffAppImpl::ScreenClear() {
    m_pDev->Clear(m_backgroundColor);
}

void ffAppImpl::AddScene(ffScene *pScene) {
    m_sceneList.push_back(pScene);
}

size_t ffAppImpl::GetSceneCount() const {
    return m_sceneList.size();
}

ffScene *ffAppImpl::GetCurrentScene() {
    if (m_sceneList.empty())
        return NULL;
    return m_sceneList.front();
}

void ffAppImpl::NextScene() {
    if (!m_sceneList.empty()) {
        m_removeSceneList.push_back(m_sceneList.front());
        m_sceneList.pop_front();
    }
}

void ffAppImpl::RemoveScene(ffScene *pScene) {
    ffSceneList::iterator result =
        std::find(m_sceneList.begin(), m_sceneList.end(), pScene);
    if (result != m_sceneList.end()) {
        m_removeSceneList.push_back(*result);
        m_sceneList.erase(result);
    }
}

void ffAppImpl::ClearScene() {
    while (!m_sceneList.empty()) {
        m_removeSceneList.push_back(m_sceneList.back());
        m_sceneList.pop_back();
    }
}

fDouble ffAppImpl::GetUpdateTime() {
    return m_updateTime;
}

fDouble ffAppImpl::GetRenderTime() {
    return m_renderTime;
}

fBool ffAppImpl::OnUpdate(fDouble elapsedTime, f2dFPSController *pFPSController, f2dMsgPump *pMsgPump) {

    m_watch.Reset();

    elapsedTime = m_fpsStabilizer.GetFps(elapsedTime);

    f2dMsg tMsg;

    /// 处理废弃的场景列表
    if (!m_removeSceneList.empty()) {
        m_eventListener->OnRemoveScene(m_removeSceneList.back());
        m_removeSceneList.pop_back();

        ffResImpl::Get().ResPathGC();
    }

    /// 检查当前场景是否已经初始化
    if (!m_sceneList.empty() && !m_sceneList.front()->IsCreated()) {
        m_sceneList.front()->OnCreate();
        m_sceneList.front()->SetCreated();
    }

    while (FCYOK(pMsgPump->GetMsg(&tMsg)))
    {
        /// 预先处理鼠标信息
        m_pMouse->UpdateLimit(tMsg);

        /// 尝试让场景来处理这个消息
        if (!m_sceneList.empty()&& m_sceneList.front()->HandleMsg(tMsg))
            continue;

        /// 尝试让用户来处理这个消息
        if (m_eventListener->OnMsg(tMsg)) // 隐式转换为 ffMsg
            continue;

        switch (tMsg.Type)
        {
        case F2DMSG_APP_ONEXIT:
            delete this;
            return true;
        case F2DMSG_WINDOW_ONCLOSE:
            return false;
        default:
            break;
        }
    }

    m_pMouse->Update();

    m_pKeyboard->Update();

    m_eventListener->OnUpdate(elapsedTime);

    if (!m_sceneList.empty())
        m_sceneList.front()->HandleUpdate(elapsedTime);

    m_pCamera->UpDateMatrix();

    m_updateTime = m_watch.GetElpased();

    if (m_runing == false) {
        return false;
    } else {
        return true;
    }
}

fBool ffAppImpl::OnRender(fDouble elapsedTime, f2dFPSController *pFPSController) {

    m_watch.Reset();

    this->ScreenClear();

    m_eventListener->OnRender(elapsedTime, m_pGraph);

    if (!m_sceneList.empty())
        m_sceneList.front()->HandleRender(elapsedTime, m_pGraph);

    m_eventListener->OnLastRender(elapsedTime, m_pGraph);

    m_renderTime = m_watch.GetElpased();

    return true;
}


void ffAppImpl::Exit() {
    m_runing = false;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief 帧数稳定器
////////////////////////////////////////////////////////////////////////////////

ffFpsStabilizer::ffFpsStabilizer() {
    for (size_t i = 0; i != 5; ++i) {
        m_pFpsRecords[i] = 0.0166f;
    }
}

ffFpsStabilizer::~ffFpsStabilizer() {
}

fDouble ffFpsStabilizer::GetFps(fDouble elapsedTime) {
    if (elapsedTime > 0.1 /*100ms*/) {
        return GetAvg();
    }

    m_pFpsRecords[4] = m_pFpsRecords[3];
    m_pFpsRecords[3] = m_pFpsRecords[2];
    m_pFpsRecords[2] = m_pFpsRecords[1];
    m_pFpsRecords[1] = m_pFpsRecords[0];
    m_pFpsRecords[0] = elapsedTime;

    return GetAvg();
}

fDouble ffFpsStabilizer::GetAvg() const {
    return (m_pFpsRecords[0] +
        m_pFpsRecords[1] +
        m_pFpsRecords[2] +
        m_pFpsRecords[3] +
        m_pFpsRecords[4]) / 5.f;
}
