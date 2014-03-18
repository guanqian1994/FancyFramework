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
///        file :   ffUILable.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "..\ffUIView.h"

class ffUILable : public ffUIView {
    friend class ffUIButton;
public:
    /// @brief 水平对齐
    enum HalignMode
    {
        HalignMode_Left,
        HalignMode_Center,
        HalignMode_Right,
    };

    /// @brief 垂直对齐
    enum ValignMode
    {
        ValignMode_Left,
        ValignMode_Center,
        ValignMode_Right,
    };

    static ffUILable *Create(ffUIView *pParent, ffPoint local, ffSize size, fcStrW text);

    fcStrW GetText() const;

    void SetText(fcStrW text);

    ffFont *GetFont() const;

    void SetFont(ffFont *pFont);

    fcyColor GetColor() const;

    void SetColor(const fcyColor &color);

    void SetHalignMode(HalignMode mode);

    void SetValignMode(ValignMode mode);

protected:
    virtual fBool OnMouseDown(ffUIMouseEvent *pEvent) { return false; }

    virtual fBool OnMouseUp(ffUIMouseEvent *pEvent) { return false; }

    virtual fBool OnMouseDoubleClick(ffUIEvent *pEvent) { return false; }

    virtual fBool OnMouseMove(ffUIMouseEvent *pEvent) { return false; }

    virtual fBool OnMouseWheel(ffUIMouseEvent *pEvent) { return false; }

    virtual fBool OnRender(ffRenderEvent *pEvent);

    void OnRenderOriginal(ffRenderEvent *pEvent);

private:
    ffUILable(ffUIView *pParent);

    ffFont *m_pFont;

    fFloat m_textHeight;

    fcyColor m_color;

    HalignMode m_hAlign;   // 水平对齐

    ValignMode m_vAlign;   // 垂直对齐

    std::wstring m_text;

    std::vector<std::wstring> m_lines;

    std::vector<float> m_lineWidth;
};