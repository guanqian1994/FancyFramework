#pragma once

#include <fcyRefObj.h>
#include <f2d.h>
#include "..\ffApp.h"

class ffDrawerImpl;

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
    virtual fcyVec2 GetScreenSize();

    virtual void SetBackgroundColor(const fcyColor &color);

    virtual void Run();
    virtual void ScreenClear();

    // events
    virtual fBool OnUpdate(fDouble elapsedTime, f2dFPSController *pFPSController, f2dMsgPump *pMsgPump);
    virtual fBool OnRender(fDouble elapsedTime, f2dFPSController *pFPSController);

    virtual void OnRenderDeviceLost() {}
    virtual void OnRenderDeviceReset(){}
private:
    static ffAppImpl *s_singleton;

    fcyColor m_backgroundColor;

    ffDrawerImpl        *m_pDrawer;
    ffAppEventListener  *m_eventListener;

    f2dEngine       *m_pEngine;
    f2dRenderDevice *m_pDev;
    f2dGraphics2D   *m_pGraph;
    f2dInputKeyboard*m_pInputKeyboard;
};