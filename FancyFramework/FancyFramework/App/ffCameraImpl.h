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
///        file :   ffCameraImpl.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <fcyRefObj.h>
#include <f2d.h>
#include "..\ffApp.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief 相机接口实现
////////////////////////////////////////////////////////////////////////////////
class ffCameraImpl 
    : public fcyRefObjImpl<ffCamera> {
public:
    static ffCameraImpl &Get();

    ffCameraImpl(f2dGraphics2D *pGraph);

    ~ffCameraImpl();

    virtual void SetStatus(const ffCameraStatus &status);

    virtual void SetScale(fFloat scale);

    virtual void SetPosition(const fcyVec2 &pos);

    virtual ffCameraStatus &GetStatus();

    virtual const ffCameraStatus &GetStatus() const;

    virtual fFloat &GetScale();

    virtual fFloat GetScale() const;

    virtual const fcyVec2 &GetPosition();

    virtual const fcyVec2 &GetPosition() const;

    fcyMatrix4 GetCameraView() const;

    fcyMatrix4 GetScreenView() const;

    void UpDateMatrix();

private:
    static ffCameraImpl *s_pSingleton;

    fcyMatrix4 m_mat;

    f2dGraphics2D *m_pGraph = NULL;

    /// 当前状态
    ffCameraStatus m_currentStatus;

    /// 目标状态
    /// ffCameraStatus m_targetStatus;
};