////////////////////////////////////////////////
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
///        file :   ffUIButton.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffUILable.h"
#include "fcyMisc\fcyStringHelper.h"

ffUILable *ffUILable::Create(ffUIView *pParent, ffPoint local, ffSize size, fcStrW text) {
    if (pParent) {
        ffUILable *pLable = new ffUILable(pParent);

        pLable->Location = local;
        pLable->Size = size;
        pLable->Text = text;

        return pLable;
    }
    return NULL;
}

fBool ffUILable::OnRender(ffRenderEvent *pEvent) {
    OnRenderOriginal(pEvent);
    Render.Do(this, pEvent);
    return true;
}

void ffUILable::OnRenderOriginal(ffRenderEvent *pEvent) {
    ffFont *pFont =
        m_pFont ? m_pFont : ffDrawer::Get().GetFont();

    pFont->Get()->SetColor(m_color);

    // 一行行绘制
    f2dFontProvider *pFontProvider = pFont->Get()->GetFontProvider();

    float tAscender = pFontProvider->GetAscender();
    float tDescender = pFontProvider->GetDescender();
    float tLineHeight = pFontProvider->GetLineHeight();

    for (fuInt i = 0; i < m_lines.size(); ++i) {
        fcyVec2 tPos;

        // 横向位置
        switch (m_hAlign) {
        case HalignMode_Left:
            tPos.x = 0.f;
            break;
        case HalignMode_Center:
            tPos.x = Size.Get().x / 2.f - m_lineWidth[i] / 2.f;
            break;
        case HalignMode_Right:
            tPos.x = Size.Get().x - m_lineWidth[i];
            break;
        }

        // 纵向位置
        switch (m_vAlign) {
        case ValignMode_Left:
            tPos.y = tAscender + tLineHeight * i;
            break;
        case ValignMode_Center:
            tPos.y = Size.Get().y / 2.f - m_textHeight / 2.f + tAscender;
            break;
        case ValignMode_Right:
            tPos.y = Size.Get().y + tDescender - tLineHeight * i;
            break;
        }

        pFont->Get()->DrawTextW(pEvent->pGraph, m_lines[i].c_str(), pEvent->Dest.a + tPos);
    }
}

ffUILable::ffUILable(ffUIView *pParent) 
    : ffUIView(pParent), 
      m_color(ffColors::Black), 
      m_pFont(NULL),
      m_hAlign(HalignMode_Center),
      m_vAlign(ValignMode_Left),

    Halign(
    [&](const HalignMode &p)->void { m_hAlign = p; },
    [&]()->const HalignMode &{ return m_hAlign; }),

    Valign(
    [&](const ValignMode &p)->void { m_vAlign = p; },
    [&]()->const ValignMode &{ return m_vAlign; }),

    Color(
    [&](const fcyColor &p)->void { m_color = p; },
    [&]()->const fcyColor &{ return m_color; }),

    Text(
    [&](const std::wstring &p)->void { 
        m_text = p;
        m_lines.clear();
        m_lineWidth.resize(fcyStringHelper::StringSplit(m_text, L"\n", false, m_lines));
        // 度量每行的宽度
        ffFont *pFont =
            m_pFont ? m_pFont : ffDrawer::Get().GetFont();

        for (fuInt i = 0; i < m_lines.size(); ++i) {
            m_lineWidth[i] = pFont->Get()->MeasureStringWidth(m_lines[i].c_str()) + 2.f;
        }

        m_textHeight = m_lines.size() * pFont->Get()->GetFontProvider()->GetLineHeight();
    },
    [&]()->const std::wstring &{ return m_text; }),

    Font(
    [&](ffFont *p)->void { m_pFont = p; },
    [&]()->ffFont *{ return m_pFont; })
{
    
}