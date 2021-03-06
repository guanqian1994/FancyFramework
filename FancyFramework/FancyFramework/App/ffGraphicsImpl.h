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
///        file :   ffScreenGraphics2DImpl.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <fcyRefObj.h>
#include "..\ffApp.h"

struct ffGraphics;
class ffCameraImpl;

////////////////////////////////////////////////////////////////////////////////
/// @brief 2D屏幕坐标渲染器接口
////////////////////////////////////////////////////////////////////////////////
class ffGraphicsImpl
    : public fcyRefObjImpl<ffGraphics> {
public:
    ffGraphicsImpl(f2dGraphics2D *pGraph, ffCameraImpl *pCamera);

    /// 是否为3D渲染器，否则为2D渲染器
    virtual fBool IsGraphics3D()                                    { return m_pGraph->IsGraphics3D(); }

    /// 检查是否处于Begin/End区段
    virtual fBool IsInRender()                                      { return m_pGraph->IsInRender(); }

    /// 启动渲染器并完成状态同步
    virtual fResult Begin()                                         { return Begin(ffGraphics::Screen); }
    virtual fResult Begin(ffGraphics::View viewType);

    /// 立即递交渲染队列
    virtual fResult Flush()                                         { return m_pGraph->Flush(); }

    /// 结束渲染过程并递交渲染队列
    virtual fResult End()                                           { return m_pGraph->End(); }

    /// 对2D渲染器的所有矩阵操作都是无效的
    virtual const fcyMatrix4& GetWorldTransform()                   { return fcyMatrix4::GetIdentity(); }
    virtual const fcyMatrix4& GetViewTransform()                    { return fcyMatrix4::GetIdentity(); }
    virtual const fcyMatrix4& GetProjTransform()                    { return fcyMatrix4::GetIdentity(); }
    virtual void SetWorldTransform(const fcyMatrix4& Mat)           { }
    virtual void SetViewTransform(const fcyMatrix4& Mat)            { }
    virtual void SetProjTransform(const fcyMatrix4& Mat)            { }

    /// 返回像素混合参数
    virtual const f2dBlendState& GetBlendState()                    { return m_pGraph->GetBlendState(); }

    /// 设置像素混合参数
    virtual void SetBlendState(const f2dBlendState& State)          { return m_pGraph->SetBlendState(State); }

    /// 返回颜色混合状态
    virtual F2DGRAPH2DBLENDTYPE GetColorBlendType()                 { return m_pGraph->GetColorBlendType(); }

    /// 设置颜色混合状态
    virtual fResult SetColorBlendType(F2DGRAPH2DBLENDTYPE Type)     { return m_pGraph->SetColorBlendType(Type); }

    /// 绘制矩形
    virtual fResult DrawQuad(
        f2dTexture2D* pTex,
        const f2dGraphics2DVertex& v1,
        const f2dGraphics2DVertex& v2,
        const f2dGraphics2DVertex& v3,
        const f2dGraphics2DVertex& v4,
        fBool bAutoFixCoord = true
        ) {
        return m_pGraph->DrawQuad(pTex, v1, v2, v3, v4, bAutoFixCoord);
    }

    /// 绘制矩形
    virtual fResult DrawQuad(f2dTexture2D* pTex, const f2dGraphics2DVertex* arr, fBool bAutoFixCoord = true) {
        return m_pGraph->DrawQuad(pTex, arr, bAutoFixCoord);
    }

    /// 原始绘制函数
    virtual fResult DrawRaw(f2dTexture2D* pTex, fuInt VertCount, fuInt IndexCount, const f2dGraphics2DVertex* VertArr, const fuShort* IndexArr, fBool bAutoFixCoord = true) {
        return m_pGraph->DrawRaw(pTex, VertCount, IndexCount, VertArr, IndexArr, bAutoFixCoord);
    }

private:
    ffCameraImpl *m_pCamera;

    f2dGraphics2D *m_pGraph;

    View           m_prevView;
};