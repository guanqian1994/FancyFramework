#include "ffAppImpl.h"

#include <cassert>
#include "ffDrawerImpl.h"
#include "fcyException.h"
#include "..\ffScene.h"

#define BUFFERSIZE 4096

ffApp &ffApp::Get() {
    return ffAppImpl::Get();
}

ffAppImpl *ffAppImpl::s_pSingleton = NULL;

ffAppImpl &ffAppImpl::Get() {
    return *s_pSingleton;
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
    assert(!s_pSingleton);

    if (FCYFAILED(CreateF2DEngineAndInit
        (F2DVERSION, fcyRect(50, 50, 50 + width, 50 + height),
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

    s_pSingleton = this;

    m_eventListener = pListener;

    m_pBuffer = new char[BUFFERSIZE];

    m_eventListener->OnCreate(this);
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

    m_eventListener->OnDestroy(this);

    FCYSAFEKILL(m_pDrawer);
    FCYSAFEKILL(m_pInputKeyboard);
    FCYSAFEKILL(m_pGraph);
    FCYSAFEKILL(m_pEngine);

    delete m_pBuffer;

    s_pSingleton = NULL;
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

fcyVec2 ffAppImpl::GetWindowSize() {
    return fcyVec2(m_pDev->GetBufferWidth(), m_pDev->GetBufferHeight());
}

char *ffAppImpl::GetBuffer() {
    return m_pBuffer;
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

fBool ffAppImpl::OnUpdate(fDouble elapsedTime, f2dFPSController *pFPSController, f2dMsgPump *pMsgPump) {
    f2dMsg tMsg;

    /// 处理废弃的场景列表
    while (!m_removeSceneList.empty()) {
        m_eventListener->OnRemoveScene(m_removeSceneList.back());
        m_removeSceneList.pop_back();
    }

    /// 检查当前场景是否已经初始化
    if (!m_sceneList.empty() && m_sceneList.front()->IsCreated()) {
        m_sceneList.front()->OnCreate();
        m_sceneList.front()->SetCreated();
    }

    while (FCYOK(pMsgPump->GetMsg(&tMsg)))
    {
        /// 尝试让场景来处理这个消息
        if (!m_sceneList.empty()&& m_sceneList.front()->HandleMsg(tMsg))
            continue;

        /// 尝试让用户来处理这个消息
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

    if (!m_sceneList.empty())
        m_sceneList.front()->OnUpdate(elapsedTime);

    return true;
}

fBool ffAppImpl::OnRender(fDouble elapsedTime, f2dFPSController *pFPSController) {

    this->ScreenClear();

    m_pGraph->Begin();

    m_eventListener->OnRender(elapsedTime, m_pGraph);

    if (!m_sceneList.empty())
        m_sceneList.front()->OnRender(elapsedTime, m_pGraph);

    m_pGraph->End();

    return true;
}