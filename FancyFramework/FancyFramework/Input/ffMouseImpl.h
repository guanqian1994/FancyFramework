////////////////////////////////////////////////////////////////////////////////
/// Copyright(c) 2013, frimin
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
///        file :   ffMouseImpl.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <fcyRefObj.h>
#include <f2d.h>
#include "..\ffInput.h"

class ffAppImpl;
////////////////////////////////////////////////////////////////////////////////
/// @brief 鼠标操作接口实现
////////////////////////////////////////////////////////////////////////////////
class ffMouseImpl 
    : public fcyRefObjImpl<ffMouse> {
public:
    static ffMouseImpl &Get();

    ffMouseImpl(ffAppImpl *pApp);
    ~ffMouseImpl();

    virtual const fcyVec2 &GetPos() const;

    virtual fFloat GetSensitivity() const;

    virtual fBool IsLimit() const;

    virtual fBool IsLeftDown();

    virtual fBool IsRightDown();

    virtual fBool IsMiddleDown();

    virtual void Limit(Mode mode, fFloat sensitivity = -1.f);

    void Update();

    void UpdateLimit(f2dMsg &msg);

private:
    static ffMouseImpl *s_pSingleton;

    HWND m_windowHandle;

    ffAppImpl *m_pAppImpl;

    f2dEngine *m_pEngine;

    /// 当前模式
    Mode m_mouseMode;

    /// 定鼠灵敏度（启用锁定鼠标时）
    fFloat m_sensitivity;

    fcyVec2 m_mousePosition;

    fcyRefPointer<f2dInputMouse> m_pInputMouse;
};