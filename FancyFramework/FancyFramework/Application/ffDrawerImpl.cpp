#include "ffDrawerImpl.h"
#include <cassert>

#define FONTFACENAME L"Microsoft YaHei"

ffDrawer &ffDrawer::Get() {
    return ffDrawerImpl::Get();
}

ffDrawerImpl *ffDrawerImpl::s_singleton = NULL;

ffDrawerImpl &ffDrawerImpl::Get() {
    return *s_singleton;
}

ffDrawerImpl::ffDrawerImpl(f2dRenderer *pRenderer, f2dGraphics2D *pGraph)
: m_pGraph(pGraph) {
    assert(!s_singleton);
    assert(!FCYFAILED(pRenderer->CreateGeometryRenderer(&m_pGeometryRenderer)));
    assert(!FCYFAILED(pRenderer->CreateSystemFont(FONTFACENAME, 0, fcyVec2(15, 15), F2DFONTFLAG_NONE, &m_pFontProvider)));
    assert(!FCYFAILED(pRenderer->CreateFontRenderer(m_pFontProvider, &m_pFontRenderer)));

    m_pGeometryRenderer->SetPenSize(2.f);

    SetColor(fcyColor(0, 0, 0));

    s_singleton = this;
}

ffDrawerImpl::~ffDrawerImpl() {
    s_singleton = NULL;
}

void ffDrawerImpl::DrawPolygon(const fcyVec2 *pVertices, fInt vertexCount) {
    for (fInt i = 0; i < vertexCount; ++i) {
        if (i == (vertexCount - 1))
            m_pGeometryRenderer->DrawLine(m_pGraph, pVertices[0], pVertices[i]);
        else
            m_pGeometryRenderer->DrawLine(m_pGraph, pVertices[i], pVertices[i + 1]);
    }
}

void ffDrawerImpl::DrawCircle(const fcyVec2 &center, fFloat radius) {
    m_pGeometryRenderer->DrawCircle(m_pGraph, center, radius);
}

void ffDrawerImpl::DrawSolidCircle(const fcyVec2 &center, fFloat radius) {
    m_pGeometryRenderer->FillCircle(m_pGraph, center, radius, m_color[0], m_color[0]);
}

void ffDrawerImpl::DrawLine(const fcyVec2 &p1, const fcyVec2 &p2) {
    m_pGeometryRenderer->DrawLine(m_pGraph, p1, p2);
}

void ffDrawerImpl::DrawWString(fcyVec2 pos, const wchar_t *pString) {
    m_pFontRenderer->DrawTextW(m_pGraph, pString, pos);
}

void ffDrawerImpl::DrawRectangle(const fcyRect &rect) {
    m_pGeometryRenderer->DrawRectangle(m_pGraph, rect);
}

void ffDrawerImpl::DrawSolidRectangle(const fcyRect &rect) {
    m_pGeometryRenderer->FillRectangle(m_pGraph, rect, m_color);
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