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
///        file :   ffUIView.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffUIView.h"
#include "ffUILayer.h"
////////////////////////////////////////////////////////////////////////////////
/// @brief 可视对象列表
////////////////////////////////////////////////////////////////////////////////
void ffViewList::Add(ffUIView *pView) {
    if (pView != NULL)
        m_list.push_back(pView);
}

fInt ffViewList::Size() const {
    return m_list.size();
}

ffUIView *ffViewList::GetView(fInt index) {
    return m_list[index];
}

const ffUIView *ffViewList::GetView(fInt index) const {
    return m_list[index];
}

fBool ffViewList::Contain(ffUIView *pView) const {
    for (auto iter = m_list.begin(); iter != m_list.end(); ++iter) {
        if ((*iter) == pView) {
            return true;
        }
    }
    return false;
}

fBool ffViewList::Contain(fcStrW name) const {
    for (auto iter = m_list.begin(); iter != m_list.end(); ++iter) {
        if (wcscmp((*iter)->GetName(), name) == 0) {
            return true;
        }
    }
    return false;
}

void ffViewList::Remove(ffUIView *pView) {
    for (auto iter = m_list.begin(); iter != m_list.end(); ++iter) {
        if ((*iter) == pView) {
            delete *iter;
            m_list.erase(iter);
            return;
        }
    }
}

void ffViewList::Remove(fInt index) {
    delete GetView(index);
    m_list.erase(m_list.begin() += index);
}

void ffViewList::RemoveAll() {
    for (auto iter = m_list.begin(); iter != m_list.end(); ++iter) {
        delete *iter;
    }
    m_list.clear();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief 可视对象
////////////////////////////////////////////////////////////////////////////////

ffUIView::ffUIView(ffUIView *pParent)
    : m_pParent(NULL), 
      m_enabled(true), 
      m_visible(true) {
    if (pParent != NULL) {
        this->SetParentView(pParent);
        pParent->Add(this);
    }
}

ffUIView::~ffUIView() {
    
}

void ffUIView::Add(ffUIView *pView) {
    m_childs.Add(pView);
}

void ffUIView::Remove() {

}

fcStrW ffUIView::GetName() const {
    return m_name.c_str();
}

void ffUIView::SetName(fcStrW name) {
    m_name = name;
}

ffPoint ffUIView::GetLocation() const {
    return m_location;
}

void ffUIView::SetLocation(ffPoint p) {
    m_location = p;
}

ffSize ffUIView::GetSize() const {
    return m_size;
}

void ffUIView::SetSize(ffSize size) {
    m_size = size;
}

fBool ffUIView::IsEnabled() const {
    return m_enabled;
}

void ffUIView::SetEnabled(fBool b) {
    m_enabled = b;
}

fBool ffUIView::IsVisible() const {
    return m_visible;
}

void ffUIView::SetVisible(fBool b) {
    m_visible = b;
}

ffUIView *ffUIView::GetParentView() {
    return m_pParent;
}

ffViewList &ffUIView::GetChilds() {
    return m_childs;
}

const ffViewList &ffUIView::GetChilds() const {
    return m_childs;
}

fBool ffUIView::TryHandleMouseMsg(ffPoint mousePos, ffPoint clientLocal, ffUILayer *pUILayer, const ffMsg &msg) {
    if (false == fcyRect(clientLocal + GetLocation(),
        clientLocal + GetLocation() + GetSize()).Contain(mousePos)) {
        return false;
    }

    for (fInt i = m_childs.Size() - 1; i != -1; --i) {
        if (m_childs.GetView(i)->TryHandleMouseMsg(mousePos, clientLocal + m_location, pUILayer, msg)) {
            return true;
        }
    }

    switch (msg.GetType()) {
    case F2DMSG_WINDOW_ONMOUSEMOVE:
        return OnMouseMove(NULL) ? (pUILayer->SetMouseOn(this), true) : false;
    case F2DMSG_WINDOW_ONMOUSELUP: {
        ffUIMouseEvent event(ffMouseButton::Left, msg[0].ToInt(), msg[1].ToInt(), 0);
        return OnMouseUp(NULL) ? (pUILayer->SetSelected(this), true) : false;
    }
    }

    return OnMsg(msg);
}

fBool ffUIView::OnMsg(const ffMsg &msg) {
    if (m_enabled == false || m_visible == false) {
        return false;
    }

    switch (msg.GetType())
    {
    case F2DMSG_WINDOW_ONMOUSELDOWN: {
        ffUIMouseEvent event(ffMouseButton::Left, msg[0].ToInt(), msg[1].ToInt(), 0);
        return OnMouseDown(&event);
    }
    case F2DMSG_WINDOW_ONMOUSELDOUBLE: {
        ffUIMouseEvent event(ffMouseButton::Left, msg[0].ToInt(), msg[1].ToInt(), 0);
        return OnMouseDoubleClick(&event);
    }
    case F2DMSG_WINDOW_ONMOUSERUP: {
        ffUIMouseEvent event(ffMouseButton::Right, msg[0].ToInt(), msg[1].ToInt(), 0);
        return OnMouseUp(&event);
    }
    case F2DMSG_WINDOW_ONMOUSERDOWN: {
        ffUIMouseEvent event(ffMouseButton::Right, msg[0].ToInt(), msg[1].ToInt(), 0);
        return OnMouseDown(&event);
    }
    case F2DMSG_WINDOW_ONMOUSERDOUBLE: {
        ffUIMouseEvent event(ffMouseButton::Right, msg[0].ToInt(), msg[1].ToInt(), 0);
        return OnMouseDoubleClick(&event);
    }
    case F2DMSG_WINDOW_ONMOUSEMUP: {
        ffUIMouseEvent event(ffMouseButton::Middle, msg[0].ToInt(), msg[1].ToInt(), 0);
        return OnMouseUp(&event);
    }
    case F2DMSG_WINDOW_ONMOUSEMDOWN: {
        ffUIMouseEvent event(ffMouseButton::Middle, msg[0].ToInt(), msg[1].ToInt(), 0);
        return OnMouseDown(&event);
    }
    case F2DMSG_WINDOW_ONMOUSEMDOUBLE: {
        ffUIMouseEvent event(ffMouseButton::Middle, msg[0].ToInt(), msg[1].ToInt(), 0);
        return OnMouseDoubleClick(&event);
    }
    case F2DMSG_WINDOW_ONMOUSEWHEEL: {
        ffUIMouseEvent event(ffMouseButton::None, msg[0].ToInt(), msg[1].ToInt(), msg[2].ToDouble());
        return OnMouseWheel(&event);
    }
    }

    return false; 
}

void ffUIView::SetParentView(ffUIView *pView) {
    m_pParent = pView;
}

fBool ffUIView::OnEnter(ffUIEvent *pEvent) {
    Enter.Do(this, pEvent);
    return true; 
}

fBool ffUIView::OnLeave(ffUIEvent *pEvent) {
    Enter.Do(this, pEvent);
    return true;
}

fBool ffUIView::OnMouseEnter(ffUIEvent *pEvent) {
    MouseEnter.Do(this, pEvent);
    return true;
}

fBool ffUIView::OnMouseLeave(ffUIEvent *pEvent) {
    MouseLeave.Do(this, pEvent);
    return true;
}

fBool ffUIView::OnMouseDown(ffUIMouseEvent *pEvent) {
    MouseDown.Do(this, pEvent);
    return true;
}

fBool ffUIView::OnMouseUp(ffUIMouseEvent *pEvent) {
    MouseUp.Do(this, pEvent);
    return true;
}

fBool ffUIView::OnMouseDoubleClick(ffUIEvent *pEvent) {
    MouseDoubleClick.Do(this, pEvent);
    return true;
}

fBool ffUIView::OnMouseMove(ffUIEvent *pEvent) {
    MouseMove.Do(this, pEvent);
    return true;
}

fBool ffUIView::OnMouseWheel(ffUIMouseEvent *pEvent) {
    MouseWheel.Do(this, pEvent);
    return true;
}
fBool ffUIView::OnKeyDown(ffUIKeyEvent *pEvent) {
    KeyDown.Do(this, pEvent);
    return true;
}

fBool ffUIView::OnKeyUp(ffUIKeyEvent *pEvent) {
    KeyUp.Do(this, pEvent);
    return true;
}

fBool ffUIView::OnUpdate(ffUpdateEvent *pEvent) {
    Update.Do(this, pEvent);
    return true;
}

fBool ffUIView::OnRender(ffRenderEvent *pEvent) {
    Render.Do(this, pEvent);
    return true;
}