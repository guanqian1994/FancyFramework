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
/// @brief ���Ӷ����б�
////////////////////////////////////////////////////////////////////////////////
class ffViewList {
public:
    void Add(ffUIView *pView);

    fInt Size() const;

    ffUIView *GetView(fInt index);

    const ffUIView *GetView(fInt index) const;

    /// @brief �Ƿ����ָ�����Ӷ���
    fBool Contain(ffUIView *pView) const;

    /// @brief �Ƴ�ָ������
    void Remove(ffUIView *pView);

    void Remove(fInt index);

    void Remove(fcStrW name);

    /// @brief �Ƴ����ж���
    void RemoveAll();
    
private:
    std::vector<ffUIView*> m_list;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ���Ӷ���
////////////////////////////////////////////////////////////////////////////////
class ffUIView {
    friend class ffViewList;
    friend class ffUILayer;
public:
    /// �¼�

    /// @brief ��ѡ���¼�
    ffEventHandler Enter;

    /// @brief ��ȡ��ѡ���¼�
    ffEventHandler Leave;

    /// @brief �������¼�
    ffEventHandler MouseEnter;

    /// @brief ����뿪�¼�
    ffEventHandler MouseLeave;

    /// @brief ��갴�������¼�
    ffEventHandler MouseDown;

    /// @brief ��갴���ſ��¼�
    ffEventHandler MouseUp;

    /// @brief ���˫���¼�
    ffEventHandler MouseDoubleClick;

    /// @brief ����ƶ��¼�
    ffEventHandler MouseMove;

    /// @brief �����ֹ����¼�
    ffEventHandler MouseWheel;

    /// @brief ���̰��������¼�
    ffEventHandler KeyDown;

    /// @brief ���̰����ſ��¼�
    ffEventHandler KeyUp;

    /// @brief �����¼�
    ffEventHandler Update;

    /// @brief ��Ⱦ�¼�
    ffEventHandler Render;

public:
    /// ����

    /// @brief λ��
    ffUIProperty::Value<ffPoint> Location;

    /// @brief �ߴ�
    ffUIProperty::Value<ffSize> Size;

    /// @brief ����
    ffUIProperty::Value<fBool> Enabled;

    /// @brief ����
    ffUIProperty::Value<fBool> Visible;

public:
    static unsigned int GetViewCount();

    ffUIView(ffUIView *pParent);

    virtual ~ffUIView();

    /// @brief ����Ӷ���
    void Add(ffUIView *pView);

    /// @brief ��ø�����
    ffUIView *GetParentView();

    /// @brief ����Ӷ����б�
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