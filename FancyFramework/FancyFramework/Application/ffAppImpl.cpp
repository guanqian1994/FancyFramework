#include "ffAppImpl.h"

#include <cassert>
#include "ffDrawerImpl.h"
#include "fcyException.h"

ffApp &ffApp::Get() {
    return ffAppImpl::Get();
}

ffAppImpl *ffAppImpl::s_singleton = NULL;

ffAppImpl &ffAppImpl::Get() {
    return *s_singleton;
}

ffApp *ffApp::Create(ffAppEventListener *pListener, fFloat width, fFloat height, fcStrW title, fBool windowed, fBool vsync, F2DAALEVEL aa) {
    ffApp *pApp = NULL;
    try {
        pApp = new ffAppImpl(pListener, width, height, title, windowed, vsync, aa);
    }
    catch (const fcyException &exc) {
        MessageBoxA(NULL, exc.GetSrc(), "exception", 0);
        pApp = NULL;
    }
    return pApp;
}

ffAppImpl::ffAppImpl(ffAppEventListener *pListener, fFloat width, fFloat height, fcStrW title, fBool windowed, fBool vsync, F2DAALEVEL aa) {
    assert(!s_singleton);
    if (FCYFAILED(CreateF2DEngineAndInit
        (F2DVERSION, fcyRect(50, 50, width, height),
        title, windowed, vsync, aa, this, &m_pEngine))) {
        throw fcyException("Application Failed to Initialize", "");
    }
    /// 初始化 f2d 引擎
    m_pDev = m_pEngine->GetRenderer()->GetDevice();

    m_pDev->CreateGraphics2D(0, 0, &m_pGraph);
    /// 设置资源目录
    //m_pEngine->GetFileSys()->LoadRealPath(L"Res", L"data");
    m_pDev->AttachListener(this);
    m_pEngine->GetInputSys()->CreateKeyboard(-1, false, &m_pInputKeyboard);

    m_pDrawer = new ffDrawerImpl(m_pEngine->GetRenderer(), m_pGraph);

    s_singleton = this;

    m_eventListener = pListener;
    m_eventListener->OnCreate(*this);
}

ffAppImpl::~ffAppImpl() {
    m_eventListener->OnDestroy(*this);

    FCYSAFEKILL(m_pDrawer);
    FCYSAFEKILL(m_pInputKeyboard);
    FCYSAFEKILL(m_pGraph);
    FCYSAFEKILL(m_pEngine);

    s_singleton = NULL;
}

f2dEngine *ffAppImpl::GetEngine() {
    return m_pEngine;
}

f2dRenderDevice *ffAppImpl::GetRenderDevice() {
    return m_pDev;
}

f2dGraphics2D *ffAppImpl::GetRenderGraphics2D() {
    return m_pGraph;
}

fcyVec2 ffAppImpl::GetScreenSize() {
    return fcyVec2(m_pDev->GetBufferWidth(), m_pDev->GetBufferHeight());
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

fBool ffAppImpl::OnUpdate(fDouble elapsedTime, f2dFPSController *pFPSController, f2dMsgPump *pMsgPump) {
    f2dMsg tMsg;
    while (FCYOK(pMsgPump->GetMsg(&tMsg)))
    {
        /// 调用回调，如果返回 true 则不再对此消息做处理
        if (m_eventListener->OnMsg(tMsg))
            continue;
        switch (tMsg.Type)
        {
        case F2DMSG_WINDOW_ONCLOSE:
            m_pEngine->Abort();
            break;
        default:
            break;
        }
    }

    m_eventListener->OnUpdate(elapsedTime);

    return true;
}

fBool ffAppImpl::OnRender(fDouble elapsedTime, f2dFPSController *pFPSController) {
    m_eventListener->OnRender(elapsedTime, m_pGraph);
    return true;
}