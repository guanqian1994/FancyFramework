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
#include "..\ffReport.h"

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
    ffAssert(!FCYFAILED(pRenderer->CreateSystemFont(FONTFACENAME, 0, fcyVec2(13, 13), F2DFONTFLAG_NONE, &m_pFontProvider)));
    ffAssert(!FCYFAILED(pRenderer->CreateFontRenderer(m_pFontProvider, &m_pFontRenderer)));

    m_pGeometryRenderer->SetPenSize(2.f);

    SetColor(fcyColor(0, 0, 0));

    s_pSingleton = this;
}

ffDrawerImpl::~ffDrawerImpl() {
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
    m_pFontRenderer->DrawTextW(pGraph, pString, pos + fcyVec2(0, m_pFontProvider->GetAscender()));
}

void ffDrawerImpl::DrawRectangle(f2dGraphics2D *pGraph, const fcyRect &rect) {
    m_pGeometryRenderer->DrawRectangle(pGraph, rect);
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
    m_pFontRenderer->SetColor(color);
}