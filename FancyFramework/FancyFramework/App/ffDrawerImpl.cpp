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
///        file :   ffDrawerImpl.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffDrawerImpl.h"
#include "..\ffAssert.h"
#include "..\ffRes.h"

#define FONTFACENAME L"Microsoft YaHei"

ffDrawer &ffDrawer::Get() {
    return ffDrawerImpl::Get();
}

ffDrawerImpl *ffDrawerImpl::s_pSingleton = NULL;

ffDrawerImpl &ffDrawerImpl::Get() {
    return *s_pSingleton;
}

ffDrawerImpl::ffDrawerImpl(f2dRenderer *pRenderer, f2dGraphics2D *pGraph) {
    ffAssert(!s_pSingleton);
    ffAssert(!FCYFAILED(pRenderer->CreateGeometryRenderer(&m_pGeometryRenderer)));
    ffAssert(m_pFont = ffFont::CreateFromSystem(FONTFACENAME, 0, fcyVec2(16, 16), F2DFONTFLAG_NONE));

    m_pGeometryRenderer->SetPenSize(1.f);

    SetColor(fcyColor(0, 0, 0));

    s_pSingleton = this;
}

ffDrawerImpl::~ffDrawerImpl() {
    FCYSAFEKILL(m_pGeometryRenderer);
    FCYSAFEKILL(m_pFont);

    s_pSingleton = NULL;
}

void ffDrawerImpl::DrawPolygon(f2dGraphics2D *pGraph, const fcyVec2 *pVertices, fInt vertexCount) {
    for (fInt i = 0; i < vertexCount; ++i) {
        if (i == (vertexCount - 1))
            m_pGeometryRenderer->DrawLine(pGraph, pVertices[0], pVertices[i]);
        else
            m_pGeometryRenderer->DrawLine(pGraph, pVertices[i], pVertices[i + 1]);
    }
}

void ffDrawerImpl::DrawCircle(f2dGraphics2D *pGraph, const fcyVec2 &center, fFloat radius) {
    m_pGeometryRenderer->DrawCircle(pGraph, center, radius);
}

void ffDrawerImpl::DrawSolidCircle(f2dGraphics2D *pGraph, const fcyVec2 &center, fFloat radius) {
    m_pGeometryRenderer->FillCircle(pGraph, center, radius, m_color[0], m_color[0]);
}

void ffDrawerImpl::DrawLine(f2dGraphics2D *pGraph, const fcyVec2 &p1, const fcyVec2 &p2) {
    m_pGeometryRenderer->DrawLine(pGraph, p1, p2);
}

void ffDrawerImpl::DrawWString(f2dGraphics2D *pGraph, fcyVec2 pos, const wchar_t *pString) {
    m_pFont->Get()->DrawTextW(pGraph, pString, pos + fcyVec2(0, m_pFont->Get()->GetFontProvider()->GetAscender()));
}

void ffDrawerImpl::DrawRectangle(f2dGraphics2D *pGraph, const fcyRect &rect) {
    //m_pGeometryRenderer->DrawRectangle(pGraph, rect);
    fcyVec2 p2(rect.b.x, rect.a.y);
    fcyVec2 p3(rect.a.x, rect.b.y);
    m_pGeometryRenderer->DrawLine(pGraph, rect.a, p2);
    m_pGeometryRenderer->DrawLine(pGraph, p2, rect.b);
    m_pGeometryRenderer->DrawLine(pGraph, rect.b, p3);
    m_pGeometryRenderer->DrawLine(pGraph, p3, rect.a);
}

void ffDrawerImpl::DrawSolidRectangle(f2dGraphics2D *pGraph, const fcyRect &rect) {
    m_pGeometryRenderer->FillRectangle(pGraph, rect, m_color);
}

void ffDrawerImpl::SetColor(const fcyColor &color) {
    m_color[0] = color;
    m_color[1] = color;
    m_color[2] = color;
    m_color[3] = color;
    m_pGeometryRenderer->SetPenColor(0, color);
    m_pGeometryRenderer->SetPenColor(1, color);
    m_pGeometryRenderer->SetPenColor(2, color);
    m_pFont->Get()->SetColor(color);
}

void ffDrawerImpl::SetPenSize(fFloat size) {
    m_pGeometryRenderer->SetPenSize(size);
}

ffFont *ffDrawerImpl::GetFont() {
    return m_pFont;
}