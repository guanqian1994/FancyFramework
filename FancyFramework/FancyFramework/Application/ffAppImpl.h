#pragma once

#include <fcyRefObj.h>
#include <f2d.h>
#include <list>
#include "..\ffApp.h"

class ffDrawerImpl;

typedef std::list<ffScene*> ffSceneList;

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

    virtual f2dGraphics2D *GetRenderGraphics2D();

    virtual fcyVec2 GetWindowSize();

    virtual char *GetBuffer();

    virtual void SetWindow(fFloat width, fFloat height, fBool windowed, fBool vsync, F2DAALEVEL aa);

    virtual void SetBackgroundColor(const fcyColor &color);

    virtual void Run();

    virtual void ScreenClear();

    virtual void AddScene(ffScene *pScene);

    virtual size_t GetSceneCount() const;

    virtual ffScene *GetCurrentScene();

    virtual void NextScene();

    virtual void RemoveScene(ffScene *pScene);

    virtual void ClearScene();
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
    char *m_pBuffer;

    fcyColor m_backgroundColor;

    ffSceneList         m_sceneList;

    /// 将要移除的列表
    ffSceneList         m_removeSceneList;

    ffDrawerImpl        *m_pDrawer;

    ffAppEventListener  *m_eventListener;

    f2dEngine       *m_pEngine;

    f2dRenderDevice *m_pDev;

    f2dGraphics2D   *m_pGraph;

    f2dInputKeyboard*m_pInputKeyboard;
};