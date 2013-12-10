#pragma once

#include <windows.h>
#include <algorithm>

#include <fcyIO/fcyStream.h>
#include <f2d.h>

enum ffMsgType {

};

// if pReceiver is NULL, mean anybody can handle this message
struct ffMsg {
    bool handled;
    fLong param1;
    fLong param2;
    fLong param3;
    fLong param4;
    ffObject *pSender;
    ffObject *pReceiver;    
};

struct ffObject {
    virtual void OnMsg(ffMsg *pMsg);
};