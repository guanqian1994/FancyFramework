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
///        file :   ffMouseImpl.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffMouseImpl.h"

#include <cassert>
#include "..\App\ffAppImpl.h"

ffMouse &ffMouse::Get() {
    return ffMouseImpl::Get();
}

ffMouseImpl *ffMouseImpl::s_pSingleton = NULL;

ffMouseImpl &ffMouseImpl::Get() {
    return *s_pSingleton;
}

ffMouseImpl::ffMouseImpl(ffAppImpl *pApp)
      : m_mouseMode(Mode::Disable),
        m_sensitivity(1.f){

    assert(!s_pSingleton);

    m_pAppImpl = pApp;
    m_pEngine = pApp->GetEngine();
    m_windowHandle = (HWND)m_pEngine->GetMainWindow()->GetHandle();
    m_pEngine->GetInputSys()->CreateMouse(-1, false, &m_pInputMouse);
    s_pSingleton = this;
}

ffMouseImpl::~ffMouseImpl() {
    s_pSingleton = NULL;
}

const fcyVec2 &ffMouseImpl::GetPos() const {
    return m_mousePosition;
}

fFloat ffMouseImpl::GetSensitivity() const {
    return m_sensitivity;
}

fBool ffMouseImpl::IsLimit() const {
    return m_mouseMode == Mode::Enable;
}

fBool ffMouseImpl::IsLeftDown() {
    return m_pInputMouse->IsLeftBtnDown();
}

fBool ffMouseImpl::IsRightDown() {
    return m_pInputMouse->IsRightBtnDown();
}

fBool ffMouseImpl::IsMiddleDown() {
    return m_pInputMouse->IsMiddleBtnDown();
}

void ffMouseImpl::Limit(Mode mode, fFloat sensitivity) {
    if (mode == Mode::Enable && m_mouseMode != Mode::Enable) {
        /// 当由未开启设置为开启时立即更新鼠标位置
        RECT rect;
        GetWindowRect((HWND)m_pEngine->GetMainWindow()->GetHandle(), &rect);

        fcyVec2 windowCenter(
            rect.left + (fFloat)(rect.right - rect.left) / 2,
            rect.top + (fFloat)(rect.bottom - rect.top) / 2);

        SetCursorPos(windowCenter.x, windowCenter.y);
    }

    /// 暂时未找到获取边框宽度的api，此处暂时不写
    /* if (enable == false && m_mouseLocked != enable) {
    /// 当由开启设置为未开启时立即更新鼠标位置
    } */

    m_mouseMode = mode;

    if (sensitivity > 0)
        m_sensitivity = sensitivity;
}

void ffMouseImpl::Update(){
    m_pInputMouse->UpdateState();
}

void ffMouseImpl::UpdateLimit(f2dMsg &msg) {
    if (msg.Type == F2DMSG_WINDOW_ONMOUSEMOVE) {
        if (m_mouseMode == Mode::Enable) {
            RECT rect;
            GetWindowRect(m_windowHandle, &rect);

            /// 窗口中心位置(系统屏幕坐标)
            fcyVec2 windowCenter(
                rect.left + (rect.right - rect.left) / 2,
                rect.top + (rect.bottom - rect.top) / 2);

            /// 鼠标位置(系统屏幕坐标)
            POINT mousePos;
            GetCursorPos(&mousePos);

            m_mousePosition.x += ((fFloat)mousePos.x - windowCenter.x) * m_sensitivity;
            m_mousePosition.y += ((fFloat)mousePos.y - windowCenter.y) * m_sensitivity;

            /// 限制位置在屏幕内
            fcyVec2 windowSize = m_pAppImpl->GetBufferSize();

            m_mousePosition.x = min(m_mousePosition.x, windowSize.x);
            m_mousePosition.x = max(m_mousePosition.x, 0);

            m_mousePosition.y = min(m_mousePosition.y, windowSize.y);
            m_mousePosition.y = max(m_mousePosition.y, 0);

            msg.Param1 = (fInt)m_mousePosition.x;
            msg.Param2 = (fInt)m_mousePosition.y;

            SetCursorPos(windowCenter.x, windowCenter.y);
        } else {
            m_mousePosition.x = (fInt)msg.Param1;
            m_mousePosition.y = (fInt)msg.Param2;
        }
    }

    if (F2DMSG_WINDOW_ONMOUSELUP <= msg.Type && msg.Type <= F2DMSG_WINDOW_ONMOUSEWHEEL) {
        msg.Param1 = m_mousePosition.x;
        msg.Param2 = m_mousePosition.y;
    }
}