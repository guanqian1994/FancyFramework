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
///        file :   ffDrawerImpl.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <fcyRefObj.h>
#include <fcyMath.h>
#include <f2dRenderer.h>
#include "..\ffApp.h"

struct ffFont;
struct f2dRenderer;

////////////////////////////////////////////////////////////////////////////////
/// @brief 绘制类接口实现
////////////////////////////////////////////////////////////////////////////////
class ffDrawerImpl : 
    public fcyRefObjImpl<ffDrawer> {
public:
    static ffDrawerImpl &Get();

    ffDrawerImpl(f2dRenderer *pRenderer, f2dGraphics2D *pGraph);

    ~ffDrawerImpl();

    virtual void DrawCircle(f2dGraphics2D *pGraph, const fcyVec2 &center, fFloat radius);

    virtual void DrawLine(f2dGraphics2D *pGraph, const fcyVec2 &p1, const fcyVec2 &p2);

    virtual void DrawPolygon(f2dGraphics2D *pGraph, const fcyVec2 *pVertices, fInt vertexCount);

    virtual void DrawRectangle(f2dGraphics2D *pGraph, const fcyRect &rect);

    virtual void DrawSolidCircle(f2dGraphics2D *pGraph, const fcyVec2 &center, fFloat radius);

    virtual void DrawSolidRectangle(f2dGraphics2D *pGraph, const fcyRect &rect);

    virtual void DrawWString(f2dGraphics2D *pGraph, fcyVec2 pos, const wchar_t *pString);

    virtual void SetColor(const fcyColor &color);

    virtual void SetPenSize(fFloat size);

    virtual ffFont *GetFont();

private:
    static ffDrawerImpl *s_pSingleton;

    fcyColor m_color[4];

    ffFont *m_pFont = NULL;

    f2dGeometryRenderer *m_pGeometryRenderer = NULL;
};