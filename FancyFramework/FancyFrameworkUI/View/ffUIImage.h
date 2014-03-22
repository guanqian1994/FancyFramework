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
///        file :   ffUIImage.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "..\ffUIView.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief 图片
////////////////////////////////////////////////////////////////////////////////
class ffUIImage : public ffUIView {
public:
    /// @brief 创建一个图片
    static ffUIImage *Create(ffUIView *pParent, ffPoint local, fcStrW imageResPath);

    static ffUIImage *Create(ffUIView *pParent, ffPoint local, ffSprite *pSprite);

    /// @brief 设置图片
    void SetImage(ffSprite *pSprite);

    /// @brief 获得图片
    ffSprite *GetImage();

protected:
    virtual fBool OnMouseDown(ffUIMouseEvent *pEvent) { return false; }

    virtual fBool OnMouseUp(ffUIMouseEvent *pEvent) { return false; }

    virtual fBool OnMouseDoubleClick(ffUIEvent *pEvent) { return false; }

    virtual fBool OnMouseMove(ffUIMouseEvent *pEvent) { return false; }

    virtual fBool OnMouseWheel(ffUIMouseEvent *pEvent) { return false; }

    virtual fBool OnRender(ffRenderEvent *pEvent);

    void OnRenderOriginal(ffRenderEvent *pEvent);

private:
    ffUIImage(ffUIView *pParent, ffSprite *pSprite);

    ffSprite::Ref m_image;
};