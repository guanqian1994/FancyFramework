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

#include "ffBind.h"
#include "ffUIEvent.h"

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

    fBool Contain(fcStrW name) const;

    /// @brief 移除指定对象
    void Remove(ffUIView *pView);

    void Remove(fInt index);

    void Remove(fcStrW name);

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
    // Events
    ffEventHandler Enter;

    ffEventHandler Leave;

    ffEventHandler MouseEnter;

    ffEventHandler MouseLeave;

    ffEventHandler MouseDown;

    ffEventHandler MouseUp;

    ffEventHandler MouseDoubleClick;

    ffEventHandler MouseMove;

    ffEventHandler MouseWheel;

    ffEventHandler KeyDown;

    ffEventHandler KeyUp;

    ffEventHandler Update;

    ffEventHandler Render;

public:
    ffUIView(ffUIView *pParent);

    virtual ~ffUIView();

    void Add(ffUIView *pView);

    /// @brief 移除当前可视对象，并且释放内存
    void Remove();

    /// @brief 获得名称
    fcStrW GetName() const;

    /// @brief 设置名称
    void SetName(fcStrW name);
    
    /// @brief 获得位置
    const ffPoint &GetLocation() const;

    /// @brief 设置位置
    void SetLocation(ffPoint p);

    /// @brief 获得尺寸
    const ffSize &GetSize() const;

    /// @brief 设置尺寸
    void SetSize(ffSize size);

    /// @brief 是否启用
    fBool IsEnabled() const;

    /// @brief 设置启用
    void SetEnabled(fBool b);

    /// @brief 是否可视
    fBool IsVisible() const;

    /// @brief 设置可视
    void SetVisible(fBool b);

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
    std::wstring m_name;

    ffUILayer *m_pUILayer;

    ffViewList m_childs;

    ffPoint m_location;

    ffUIView *m_pParent;

    ffSize m_size;

    fBool m_enabled;

    fBool m_visible;
};