#include "ffAppImpl.h"
#include "fcyException.h"

// create in public method
ffApp *ffApp::Create(fFloat width, fFloat height, fcStrW title, fBool windowed, fBool vsync, F2DAALEVEL aa) {
    ffApp *pApp = NULL;
    try {
        pApp = new ffAppImpl(width, height, title, windowed, vsync, aa);
    }
    catch (const fcyException &exc) {
        MessageBoxA(NULL, exc.GetSrc(), "exception", 0);
        pApp = NULL;
    }
    return pApp;
}

void ffApp::Destroy(ffApp *pffApp) {
    delete pffApp;
}

ffAppImpl::ffAppImpl(fFloat width, fFloat height, fcStrW title, fBool windowed, fBool vsync, F2DAALEVEL aa) {
    if (FCYFAILED(CreateF2DEngineAndInit
        (F2DVERSION, fcyRect(50, 50, width, height),
        title, windowed, vsync, aa, this, &m_pEngine))) {
        throw fcyException("Application Failed to Initialize", "");
    }

    m_pDev = m_pEngine->GetRenderer()->GetDevice();

    m_pDev->CreateGraphics2D(0, 0, &m_pGraph);
    // load resources path
    //m_pEngine->GetFileSys()->LoadRealPath(L"Res", L"data");
    m_pDev->AttachListener(this);
    m_pEngine->GetInputSys()->CreateKeyboard(-1, false, &m_pInputKeyboard);

    m_pEngine->GetMainWindow()->SetVisiable(true);

    m_pEngine->Run(F2DENGTHREADMODE_MULTITHREAD);
}

fBool ffAppImpl::OnUpdate(fDouble ElapsedTime, f2dFPSController *pFPSController, f2dMsgPump *pMsgPump) {
    f2dMsg tMsg;
    while (FCYOK(pMsgPump->GetMsg(&tMsg)))
    {
        switch (tMsg.Type)
        {
        case F2DMSG_WINDOW_ONMOUSEMOVE:
            break;
        case F2DMSG_WINDOW_ONKEYUP:
            break;
        case F2DMSG_WINDOW_ONKEYDOWN:
            break;
        case F2DMSG_WINDOW_ONMOUSELUP:
            break;
        case F2DMSG_WINDOW_ONMOUSELDOWN:
            break;
        case F2DMSG_WINDOW_ONMOUSELDOUBLE:
            break;
        case F2DMSG_WINDOW_ONMOUSERUP:
            break;
        case F2DMSG_WINDOW_ONMOUSERDOWN:
            break;
        case F2DMSG_WINDOW_ONMOUSERDOUBLE:
            break;
        case F2DMSG_WINDOW_ONMOUSEMUP:
            break;
        case F2DMSG_WINDOW_ONMOUSEMDOWN:
            break;
        case F2DMSG_WINDOW_ONMOUSEMDOUBLE:
            break;
        case F2DMSG_WINDOW_ONMOUSEWHEEL:
            break;
        case F2DMSG_WINDOW_ONCHARINPUT:
            break;
        case F2DMSG_RENDER_ONDEVLOST:
            break;
        case F2DMSG_RENDER_ONDEVRESET:
            break;
        case F2DMSG_WINDOW_ONCLOSE:
            m_pEngine->Abort();
            break;
        case F2DMSG_WINDOW_ONGETFOCUS:
            break;
        case F2DMSG_WINDOW_ONLOSTFOCUS:
            break;
        default:
            break;
        }
    }
    return true;
}

fBool ffAppImpl::OnRender(fDouble ElapsedTime, f2dFPSController *pFPSController) {
    m_pDev->Clear();
    return true;
}