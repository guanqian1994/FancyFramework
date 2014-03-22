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

////////////////////////////////////////////////////////////////////////////////
/// @brief 标签
////////////////////////////////////////////////////////////////////////////////
class ffUILable : public ffUIView {
    friend class ffUIButton;
public:
    /// @brief 水平对齐模式
    enum HalignMode
    {
        HalignMode_Left,
        HalignMode_Center,
        HalignMode_Right,
    };

    /// @brief 垂直对齐模式
    enum ValignMode
    {
        ValignMode_Left,
        ValignMode_Center,
        ValignMode_Right,
    };

    /// @brief 创建一个标签
    static ffUILable *Create(ffUIView *pParent, ffPoint local, ffSize size, fcStrW text);

    /// @brief 获得文本
    fcStrW GetText() const;

    /// @brief 设置文本
    void SetText(fcStrW text);

    /// @brief 获得字体
    ffFont *GetFont() const;

    /// @brief 设置字体
    /// @warning 字体对象需要手动释放
    void SetFont(ffFont *pFont);

    /// @brief 获得颜色
    fcyColor GetColor() const;

    /// @brief 设置颜色
    void SetColor(const fcyColor &color);

    /// @brief 设置水平对齐模式
    void SetHalignMode(HalignMode mode);

    /// @brief 设置垂直对齐模式
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