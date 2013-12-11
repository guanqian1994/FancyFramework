#pragma once

#include <fcyRefObj.h>
#include <fcyMath.h>
#include <f2dRenderer.h>
#include "..\ffApp.h"

struct f2dRenderer;

/// 提供便捷的渲染功能
class ffDrawerImpl : 
    public fcyRefObjImpl<ffDrawer> {
public:
    static ffDrawerImpl &Get();

    ffDrawerImpl(f2dRenderer *pRenderer, f2dGraphics2D *pGraph);
    ~ffDrawerImpl();
    virtual void DrawCircle(const fcyVec2 &center, fFloat radius);
    virtual void DrawLine(const fcyVec2 &p1, const fcyVec2 &p2);
    virtual void DrawPolygon(const fcyVec2 *pVertices, fInt vertexCount);
    virtual void DrawRectangle(const fcyRect &rect);
    virtual void DrawSolidCircle(const fcyVec2 &center, fFloat radius);
    virtual void DrawSolidRectangle(const fcyRect &rect);
    virtual void DrawWString(fcyVec2 pos, const wchar_t *pString);
    virtual void SetColor(const fcyColor &color);
private:
    static ffDrawerImpl *s_singleton;

    fcyColor m_color[4];
    f2dGraphics2D *m_pGraph;
    fcyRefPointer<f2dFontRenderer> m_pFontRenderer;
    fcyRefPointer<f2dFontProvider> m_pFontProvider;
    fcyRefPointer<f2dGeometryRenderer> m_pGeometryRenderer;
};