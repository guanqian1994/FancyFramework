////////////////////////////////////////////////////////////////////////////////
/// @file  ffScene.h
/// @brief 
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ffApp.h"

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

    /// @brief 处理接收的消息
    /// @note 不可重写，上层消息首先将消息发送给此方法，如果消息没有经过处理则调用 OnMsg 供场景
    /// 来处理。若场景没有处理则交给框架来处理这个消息。
    bool HandleMsg(const f2dMsg &pMsg);

    /// @brief 当前场景是否已经被创建
    bool IsCreated();

    /// @brief 设置当前场景已经被初始化
    void SetCreated();
private:
    bool m_created;
};
