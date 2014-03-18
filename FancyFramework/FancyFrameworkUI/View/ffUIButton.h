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
#include "ffUILable.h"

class ffUIButton : public ffUILable {
public:
    static ffUIButton *Create(ffUIView *pParent, ffPoint local, ffSize size);

    enum Status {
        Normal = 0, ///< @brief 默认显示的图片
        Activate = 1,  ///< @brief 当光标进入时显示的图片
        Push = 2,   ///< @brief 按下时的图片
        Num = 3,
    };

    void SetImage(Status status, ffSprite *pSprite);

    ffSprite *GetImage(Status status);

    Status GetState() {
        return m_curState;
    }

protected:
    virtual fBool OnMouseEnter(ffUIEvent *pEvent);

    virtual fBool OnMouseLeave(ffUIEvent *pEvent);

    virtual fBool OnMouseDown(ffUIMouseEvent *pEvent);

    virtual fBool OnMouseUp(ffUIMouseEvent *pEvent);

    virtual fBool OnMouseDoubleClick(ffUIEvent *pEvent);

    virtual fBool OnMouseMove(ffUIMouseEvent *pEvent);

    virtual fBool OnMouseWheel(ffUIMouseEvent *pEvent);

    virtual fBool OnRender(ffRenderEvent *pEvent);

    void OnRenderOriginal(ffRenderEvent *pEvent);

private:
    ffUIButton(ffUIView *pParent);

    Status m_curState;

    ffSprite::Ref m_sprite[Status::Num];
};