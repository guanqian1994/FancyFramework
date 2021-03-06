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
///        file :   ffUILabel.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "..\ffUIView.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief 标签
////////////////////////////////////////////////////////////////////////////////
class ffUILabel : public ffUIView {
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
        ValignMode_Top,
        ValignMode_Center,
        ValignMode_Bottom,
    };

    /// 属性

    /// @brief 水平对齐模式
    ffUIProperty::Value<HalignMode> Halign;

    /// @brief 水平对齐模式
    ffUIProperty::Value<ValignMode> Valign;

    /// @brief 文本颜色
    ffUIProperty::Value<fcyColor> Color;

    /// @brief 文本
    ffUIProperty::Value<std::wstring> Text;

    /// @brief 文本字体
    /// @warning 字体对象需要用户管理内存
    ffUIProperty::Ptr<ffFont> Font;

public:
    /// @brief 创建一个标签
    static ffUILabel *Create(ffUIView *pParent, ffPoint local, ffSize size, fcStrW text);

    ffUILabel(ffUIView *pParent);

protected:
    virtual fBool OnMouseDown(ffUIMouseEvent *pEvent) { return false; }

    virtual fBool OnMouseUp(ffUIMouseEvent *pEvent) { return false; }

    virtual fBool OnMouseDoubleClick(ffUIMouseEvent *pEvent) { return false; }

    virtual fBool OnMouseMove(ffUIMouseEvent *pEvent) { return false; }

    virtual fBool OnMouseWheel(ffUIMouseEvent *pEvent) { return false; }

    virtual fBool OnRender(ffRenderEvent *pEvent);

    void OnRenderOriginal(ffRenderEvent *pEvent);

private:

    ffFont *m_pFont;

    fFloat m_textHeight;

    fcyColor m_color;

    HalignMode m_hAlign;   // 水平对齐

    ValignMode m_vAlign;   // 垂直对齐

    std::wstring m_text;

    std::vector<std::wstring> m_lines;

    std::vector<float> m_lineWidth;
};