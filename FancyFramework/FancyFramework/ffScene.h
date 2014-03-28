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
typedef std::vector<ffLayers> ffLayerGroup;

////////////////////////////////////////////////////////////////////////////////
/// @brief 场景类
////////////////////////////////////////////////////////////////////////////////
class ffScene {
    friend class ffAppImpl;
public:
    ffScene();

    virtual ~ffScene();

    virtual void Release();

    /// @brief 当前场景是否已经被创建
    bool IsCreated();

    /// @brief 添加场景层
    void AddLayer(ffLayer *pLayer, fInt group = 0);

    /// @brief 添加场景层到图层最后（渲染顺序最先）
    void AddLayerBack(ffLayer *pLayer, fInt group = 0);

    /// @brief 添加一个场景层组
    fInt AddLayerGroup();

    /// @brief 移除场景层
    void RemoveLayer(ffLayer *pLayer, fInt group = 0);

    /// @brief 移除场景层组
    /// @note 如果当场景层组只存在一个时效果与 ffScene::ClearLayers 效果相同
    void RemoveLayerGroup(fInt group = 0);

    /// @brief 清除指定场景层组
    void ClearLayerGroup(fInt group = 0);

    /// @brief 将场景层移至渲染队列最前
    /// @warning 渲染队列最前表示在整个绘制结果的“后面”
    void BringLayerToFront(ffLayer *pLayer, fInt group = 0);

    /// @brief 将场景层移至染队列最后
    void BringLayerToBack(ffLayer *pLayer, fInt group = 0);
    
    /// @brief 获得场景层数量
    fInt GetLayerCount(fInt group = 0) const;

    /// @brief 获得场景层组数量
    fInt GetLayerGroupCount() const;

    /// @brief 获得场景图层在组的索引
    /// @return 不在此组则返回 -1
    fInt GetLayerIndex(ffLayer *pLayer, fInt group = 0) const;

    /// @brief 从索引获得指定图层
    ffLayer *GetLayerOfIndex(fInt index, fInt group = 0);

    /// @brief 检查是否存在制定场景层
    fBool HasLayer(ffLayer *pLayer, fInt group = 0) const;

    /// @brief 执行更新
    void DoUpdate(fDouble elapsedTime) { OnUpdate(elapsedTime); }

    /// @brief 执行渲染
    void DoRender(fDouble elapsedTime, ffGraphics *pGraph) { OnRender(elapsedTime, pGraph); }

protected:
    /// @brief 被创建时调用
    virtual void OnCreate();

    /// @brief 被销毁时调用
    virtual void OnDestroy();

    /// @bridef 场景层被移除时调用
    virtual void OnRemoveLayer(ffLayer *pLayer);

    /// @brief 有消息需要处理时被调用
    virtual fBool OnMsg(const ffMsg &msg);

    /// @brief 更新时被调用
    virtual void OnUpdate(fDouble elapsedTime);

    /// @brief 画面更新时被调用
    virtual void OnRender(fDouble elapsedTime, ffGraphics *pGraph);

protected:
    /// @brief 处理消息
    /// @note 不可重写，上层消息首先将消息发送给此方法，如果消息没有经过处理则调用 OnMsg 供场景
    /// 来处理。若场景没有处理则交给框架来处理这个消息。
    bool HandleMsg(const ffMsg &msg);

    /// @brief 处理更新
    void HandleUpdate(fDouble elapsedTime);

    /// @brief 处理渲染
    void HandleRender(fDouble elapsedTime, ffGraphics *pGraph);

    /// @brief 设置当前场景已经被初始化
    void SetCreated();

private:
    fBool m_created;
    ffLayerGroup m_layerGroup;
};
