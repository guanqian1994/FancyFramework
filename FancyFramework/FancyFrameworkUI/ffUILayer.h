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
///        file :   ffUILayer.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ffLayer.h"
#include "ffUIView.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief UI层
/// @note 实例化该层并且加入到当前场景中来显示UI内容
////////////////////////////////////////////////////////////////////////////////
class ffUILayer : public ffLayer, public ffUIView {
    friend class ffUIView;
public:
    static ffUILayer *Create();

    ffUILayer();

    virtual ~ffUILayer();

    /// @brief 设置光标图片
    /// @note 图片热点位置会被设置为图片左上角
    void SetCursorImage(ffSprite *pSprite);

    /// @brief 调试绘制UI对象
    void DebugRender(ffGraphics *pGraph);

    /// @brief 获得当前被选中的对象
    ffUIView *GetSelected();

    /// @brief 设置当前被选中的对象
    void SetSelected(ffUIView *pView);

    /// @brief 设置鼠标位置所在的对象
    void SetMouseOn(ffUIView *pView);

    /// @brief 设置正在被拖动的对象
    void SetDragView(ffUIView *pView);

    /// @brief 获得正在被拖动的对象
    ffUIView *GetDragView();

protected:
    ffUIView *GetMouseOn();

    fBool OnMsg(const ffMsg &msg);

    void OnUpdate(fDouble elapsedTime);

    void OnRender(fDouble elapsedTime, ffGraphics *pGraph);

private:

    ffSprite::Ref m_cursor;

    ffPoint m_cursorPos;

    ffUIView *m_pSelected = nullptr;

    ffUIView *m_pMouseOn = nullptr;

    ffUIView *m_pDragView = nullptr;
};