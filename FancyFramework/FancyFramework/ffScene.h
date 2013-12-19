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
///        file :   ffScene.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include "ffApp.h"

class ffLayer;
typedef std::vector<ffLayer*> ffLayers;

////////////////////////////////////////////////////////////////////////////////
/// @brief 场景类
////////////////////////////////////////////////////////////////////////////////
class ffScene {
public:
    ffScene();
    ~ffScene();

    /// @brief 被创建时调用
    virtual void OnCreate();

    /// @brief 被销毁时调用
    virtual void OnDestroy();

    /// @brief 有消息需要处理时被调用
    virtual bool OnMsg(const f2dMsg &pMsg);

    /// @brief 更新时被调用
    virtual void OnUpdate(fDouble elapsedTime);

    /// @brief 画面更新时被调用
    virtual void OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph);

    /// @brief 处理消息
    /// @note 不可重写，上层消息首先将消息发送给此方法，如果消息没有经过处理则调用 OnMsg 供场景
    /// 来处理。若场景没有处理则交给框架来处理这个消息。
    bool HandleMsg(const f2dMsg &pMsg);

    /// @brief 处理更新
    bool HandleUpdate(fDouble elapsedTime);

    /// @brief 处理渲染
    bool HandleRender(fDouble elapsedTime, f2dGraphics2D *pGraph);

    /// @brief 当前场景是否已经被创建
    bool IsCreated();

    /// @brief 设置当前场景已经被初始化
    void SetCreated();

    /// @brief 添加场景层
    void AddLayer(ffLayer *pLayer);

    /// @brief 移除场景层
    void RemoveLayer(ffLayer *pLayer);

    /// @brief 清楚所有场景层
    void ClearLayers();

    /// @brief 将场景层移至最前
    void BringLayerToFront(ffLayer *pLayer);

    /// @brief 将场景层移至最后
    void BringLayerToBack(ffLayer *pLayer);

    /// @brief 检查是否存在制定场景层
    fBool HasLayer(ffLayer *pLayer);

protected:

private:
    fBool m_created;
    ffLayers m_layers
};
