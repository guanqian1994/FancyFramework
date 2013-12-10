#pragma once

#include "..\ffBase.h"

class ffObjectImpl : public ffObject {
public:
    ffObjectImpl() { 
        m_isListener = false; 
    };
    
    ~ffObjectImpl() {

    }

    bool IsListener() {
        return m_isListener;
    }

    void SetListener(bool b) {
        m_isListener = b;
    }

    virtual void OnMsg(ffMsg *pMsg) {

    }
private:
    bool m_isListener;
};