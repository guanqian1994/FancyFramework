#pragma once

#include "ffBase.h"

struct ffMsgManager {
    virtual void PushMsg(const ffMsg &pMsg);
    virtual bool Register(ffObject *pObj);
    virtual void UnRegister(ffObject *pObj);
};