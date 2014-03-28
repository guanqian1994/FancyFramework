////////////////////////////////////////////////////////////////////////////////
/// Copyright(c) 2014, frimin
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
///        file :   ffUIView.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <string>
#include <ff.h>

typedef fcyVec2 ffSize;

typedef fcyVec2 ffPoint;

#include "ffUIBind.h"
#include "ffUIEvent.h"
#include "ffUIProperty.h"

class ffUIView;

////////////////////////////////////////////////////////////////////////////////
/// @brief 可视对象列表
////////////////////////////////////////////////////////////////////////////////
class ffViewList {
public:
    void Add(ffUIView *pView);

    fInt Size() const;

    ffUIView *GetView(fInt index);

    const ffUIView *GetView(fInt index) const;

    /// @brief 是否包含指定可视对象
    fBool Contain(ffUIView *pView) const;

    /// @brief 移除指定对象
    void Remove(ffUIView *pView);

    void Remove(fInt index);

    void Remove(fcStrW name);

    /// @brief 移除所有对象
    void RemoveAll();
    
private:
    std::vector<ffUIView*> m_list;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 可视对象
////////////////////////////////////////////////////////////////////////////////
class ffUIView {
    friend class ffViewList;
    friend class ffUILayer;
public:
    /// 事件

    /// @brief 被选中事件
    ffEventHandler Enter;

    /// @brief 被取消选中事件
    ffEventHandler Leave;

    /// @brief 鼠标进入事件
    ffEventHandler MouseEnter;

    /// @brief 鼠标离开事件
    ffEventHandler MouseLeave;

    /// @brief 鼠标按键按下事件
    ffEventHandler MouseDown;

    /// @brief 鼠标按键放开事件
    ffEventHandler MouseUp;

    /// @brief 鼠标双击事件
    ffEventHandler MouseDoubleClick;

    /// @brief 鼠标移动事件
    ffEventHandler MouseMove;

    /// @brief 鼠标滚轮滚动事件
    ffEventHandler MouseWheel;

    /// @brief 键盘按键按下事件
    ffEventHandler KeyDown;

    /// @brief 键盘按键放开事件
    ffEventHandler KeyUp;

    /// @brief 更新事件
    ffEventHandler Update;

    /// @brief 渲染事件
    ffEventHandler Render;

public:
    /// 属性

    /// @brief 位置
    ffUIProperty::Value<ffPoint> Location;

    /// @brief 尺寸
    ffUIProperty::Value<ffSize> Size;

    /// @brief 启用
    ffUIProperty::Value<fBool> Enabled;

    /// @brief 可视
    ffUIProperty::Value<fBool> Visible;

public:
    static unsigned int GetViewCount();

    ffUIView(ffUIView *pParent);

    virtual ~ffUIView();

    /// @brief 添加子对象
    void Add(ffUIView *pView);

    /// @brief 获得父对象
    ffUIView *GetParentView();

    /// @brief 获得子对象列表
    ffViewList &GetChilds();

    const ffViewList &GetChilds() const;

protected:
    virtual fBool OnEnter(ffUIEvent *pEvent);

    virtual fBool OnLeave(ffUIEvent *pEvent);

    virtual fBool OnMouseEnter(ffUIEvent *pEvent);

    virtual fBool OnMouseLeave(ffUIEvent *pEvent);

    virtual fBool OnMouseDown(ffUIMouseEvent *pEvent);

    virtual fBool OnMouseUp(ffUIMouseEvent *pEvent);

    virtual fBool OnMouseDoubleClick(ffUIEvent *pEvent);

    virtual fBool OnMouseMove(ffUIMouseEvent *pEvent);

    virtual fBool OnMouseWheel(ffUIMouseEvent *pEvent);

    virtual fBool OnKeyDown(ffUIKeyEvent *pEvent);

    virtual fBool OnKeyUp(ffUIKeyEvent *pEvent);

    virtual fBool OnUpdate(ffUpdateEvent *pEvent);

    virtual fBool OnRender(ffRenderEvent *pEvent);

    fBool TryHandleMouseMsg(ffPoint mousePos, ffPoint parentGlobalLocal, const ffMsg &msg);

    fBool OnMsg(const ffMsg &msg);

    void SetParentView(ffUIView *pView);

    ffUILayer *GetUILayer() { return m_pUILayer; };

    void SetUILayer(ffUILayer *pLayer) { m_pUILayer = pLayer; };

private:
    static unsigned int s_viewCount;

    ffUILayer *m_pUILayer;

    ffViewList m_childs;

    ffPoint m_location;

    ffUIView *m_pParent;

    ffSize m_size;

    fBool m_enabled;

    fBool m_visible;
};