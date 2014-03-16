////////////////////////////////////////////////////////////////////////////////
/// Copyright(c) 2014, frimin
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
///        file :   ffUIButton.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

class ffUIView;
struct ffUIEvent;

struct ffBind {
    virtual void Do(ffUIView *pSender, ffUIEvent *pEvent) = 0;
};

template<typename classT> class ffBindMethod : public ffBind {
public:
    typedef void (classT::*methodPtr)(ffUIView*, ffUIEvent*);

    ffBindMethod(methodPtr method, classT *pObj) : m_pMethod(method), m_pObj(pObj) { }

    virtual void Do(ffUIView *pSender, ffUIEvent *pEvent) {
        return (m_pObj->*m_pMethod)(pSender, pEvent);
    }
private:
    methodPtr m_pMethod;
    classT *m_pObj;
};

class ffBindFunction : public ffBind {
public:
    typedef void (funcPtr)(ffUIView*, ffUIEvent*);

    ffBindFunction(funcPtr func) : m_pFunc(func) { }

    virtual void Do(ffUIView *pSender, ffUIEvent *pEvent) {
        return m_pFunc(pSender, pEvent);
    }
private:
    funcPtr *m_pFunc;
};

class ffEventHandler {
public:
    ffEventHandler() : m_pBind(NULL){}

    ~ffEventHandler() {
        if (m_pBind != NULL) {
            delete m_pBind;
        }
    }

    void Do(ffUIView *pSender, ffUIEvent* pEvent) {
        if (m_pBind != NULL) {
            m_pBind->Do(pSender, pEvent);
        }
    }

    ffEventHandler *operator=(ffBind *pBind) {
        if (m_pBind != NULL) {
            delete m_pBind;
        }
        m_pBind = pBind;
        return this;
    }

private:
    ffBind *m_pBind;;
};

template<typename classT> ffBindMethod<classT> *ffBindWith(typename ffBindMethod<classT>::methodPtr method, classT *pObj) {
    return new ffBindMethod<classT>(method, pObj);
}

template<typename classT> ffBindFunction *ffBindWith(typename ffBindFunction::funcPtr func) {
    return new ffBindFunction(func);
}