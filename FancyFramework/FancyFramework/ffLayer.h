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
///        file :   ffLayer.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ffScene.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief 场景层类
////////////////////////////////////////////////////////////////////////////////
class ffLayer {
    friend ffScene;
public:
    ffLayer() { }

    virtual ~ffLayer() { }

    virtual void Release() { delete this; }

    /// @brief 获得父场景
    ffScene *GetParent() { return m_pParent; }

    /// @brief 获得层所在的组
    fInt GetGroup() { return m_group; }

    /// @brief 移除场景层
    void Remove() { m_pParent->RemoveLayer(this, m_group); }

    /// @brief 将场景层移至最前
    void BringToFront() { m_pParent->BringLayerToFront(this, m_group); }

    /// @brief 将场景层移至最后
    void BringToBack() { m_pParent->BringLayerToBack(this, m_group); }

    /// @brief 执行更新
    void DoUpdate(fDouble elapsedTime) { OnUpdate(elapsedTime); }

    /// @brief 执行渲染
    void DoRender(fDouble elapsedTime, ffGraphics *pGraph) { OnRender(elapsedTime, pGraph); }

protected:
    /// @brief 有消息需要处理时被调用
    virtual fBool OnMsg(const ffMsg &msg) { return false; }

    /// @brief 更新时被调用
    virtual void OnUpdate(fDouble elapsedTime) { }

    /// @brief 画面更新时被调用
    virtual void OnRender(fDouble elapsedTime, ffGraphics *pGraph) { }

private:
    void SetParent(ffScene *pParent, fInt group) { m_pParent = pParent; m_group = group; }

    fInt m_group;

    ffScene *m_pParent;
};