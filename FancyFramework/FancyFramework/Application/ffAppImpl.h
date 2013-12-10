#pragma once

#include <fcyRefObj.h>
#include <f2d.h>
#include "..\ffApp.h"

class ffAppImpl :
    public f2dEngineEventListener,
    public f2dRenderDeviceEventListener,
    public fcyRefObjImpl<ffApp> {
public:
    ffAppImpl(fFloat width, fFloat height, fcStrW title, fBool windowed, fBool vsync, F2DAALEVEL aa);

    // events
    virtual fBool OnUpdate(fDouble elapsedTime, f2dFPSController *pFPSController, f2dMsgPump *pMsgPump);
    virtual fBool OnRender(fDouble elapsedTime, f2dFPSController *pFPSController);
    virtual void OnRenderDeviceLost() {}
    virtual void OnRenderDeviceReset(){}
private:
    f2dEngine       *m_pEngine;
    f2dRenderDevice *m_pDev;
    f2dGraphics2D   *m_pGraph;
    f2dInputKeyboard*m_pInputKeyboard;
};