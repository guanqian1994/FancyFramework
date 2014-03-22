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

unsigned int ffUIView::s_viewCount = 0;

unsigned int ffUIView::GetViewCount() {
    return s_viewCount;
}

ffUIView::ffUIView(ffUIView *pParent)
    : m_pParent(NULL), 
      m_enabled(true), 
      m_visible(true) {
    if (pParent != NULL) {
        this->SetParentView(pParent);
        pParent->Add(this);
        SetUILayer(pParent->GetUILayer());
    }
    ++s_viewCount;
}

ffUIView::~ffUIView() {
    m_childs.RemoveAll();
    --s_viewCount;
}

void ffUIView::Add(ffUIView *pView) {
    m_childs.Add(pView);
}

const ffPoint &ffUIView::GetLocation() const {
    return m_location;
}

void ffUIView::SetLocation(ffPoint p) {
    m_location = p;
}

fFloat ffUIView::GetWidth() const {
    return m_size.x;
}

fFloat ffUIView::GetHeight() const {
    return m_size.y;
}

const ffSize &ffUIView::GetSize() const {
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

fBool ffUIView::TryHandleMouseMsg(ffPoint mousePos, ffPoint parentGlobalLocal, const ffMsg &msg) {
    if (m_enabled == false || m_visible == false) {
        return false;
    }

    ffPoint curGlobalLocal = parentGlobalLocal + m_location;

    for (fInt i = m_childs.Size() - 1; i != -1; --i) {
        ffUIView *pChild = m_childs.GetView(i);
        if (false == fcyRect(curGlobalLocal + pChild->GetLocation(),
            curGlobalLocal + pChild->GetLocation() + pChild->GetSize()).Contain(mousePos)) {
            continue;
        }
        if (m_childs.GetView(i)->TryHandleMouseMsg(mousePos, curGlobalLocal, msg)) {
            return true;
        }
    }

    switch (msg.GetType()) {
    case F2DMSG_WINDOW_ONMOUSEMOVE: {
        ffUIMouseEvent event(ffMouseButton::None, msg[0].ToInt() - (fInt)parentGlobalLocal.x, msg[1].ToInt() - (fInt)parentGlobalLocal.y, 0);

        if (m_pUILayer->GetDragView() != NULL) {
            if (m_pUILayer->GetDragView() != this) {
                return false;
            }
        }

        return OnMouseMove(&event) ? (m_pUILayer->SetMouseOn(this), true) : false;
    }
    case F2DMSG_WINDOW_ONMOUSELUP: {
        ffUIMouseEvent event(ffMouseButton::Left, msg[0].ToInt() - (fInt)parentGlobalLocal.x, msg[1].ToInt() - (fInt)parentGlobalLocal.y, 0);
        return OnMouseUp(&event) ? (m_pUILayer->SetSelected(this), true) : false;
    }
    case F2DMSG_WINDOW_ONMOUSELDOWN: {
        ffUIMouseEvent event(ffMouseButton::Left, msg[0].ToInt() - (fInt)parentGlobalLocal.x, msg[1].ToInt() - (fInt)parentGlobalLocal.y, 0);
        return OnMouseDown(&event);
    }
    case F2DMSG_WINDOW_ONMOUSELDOUBLE: {
        ffUIMouseEvent event(ffMouseButton::Left, msg[0].ToInt() - (fInt)parentGlobalLocal.x, msg[1].ToInt() - (fInt)parentGlobalLocal.y, 0);
        return OnMouseDoubleClick(&event);
    }
    case F2DMSG_WINDOW_ONMOUSERUP: {
        ffUIMouseEvent event(ffMouseButton::Right, msg[0].ToInt() - (fInt)parentGlobalLocal.x, msg[1].ToInt() - (fInt)parentGlobalLocal.y, 0);
        return OnMouseUp(&event);
    }
    case F2DMSG_WINDOW_ONMOUSERDOWN: {
        ffUIMouseEvent event(ffMouseButton::Right, msg[0].ToInt() - (fInt)parentGlobalLocal.x, msg[1].ToInt() - (fInt)parentGlobalLocal.y, 0);
        return OnMouseDown(&event);
    }
    case F2DMSG_WINDOW_ONMOUSERDOUBLE: {
        ffUIMouseEvent event(ffMouseButton::Right, msg[0].ToInt() - (fInt)parentGlobalLocal.x, msg[1].ToInt() - (fInt)parentGlobalLocal.y, 0);
        return OnMouseDoubleClick(&event);
    }
    case F2DMSG_WINDOW_ONMOUSEMUP: {
        ffUIMouseEvent event(ffMouseButton::Middle, msg[0].ToInt() - (fInt)parentGlobalLocal.x, msg[1].ToInt() - (fInt)parentGlobalLocal.y, 0);
        return OnMouseUp(&event);
    }
    case F2DMSG_WINDOW_ONMOUSEMDOWN: {
        ffUIMouseEvent event(ffMouseButton::Middle, msg[0].ToInt() - (fInt)parentGlobalLocal.x, msg[1].ToInt() - (fInt)parentGlobalLocal.y, 0);
        return OnMouseDown(&event);
    }
    case F2DMSG_WINDOW_ONMOUSEMDOUBLE: {
        ffUIMouseEvent event(ffMouseButton::Middle, msg[0].ToInt() - (fInt)parentGlobalLocal.x, msg[1].ToInt() - (fInt)parentGlobalLocal.y, 0);
        return OnMouseDoubleClick(&event);
    }
    case F2DMSG_WINDOW_ONMOUSEWHEEL: {
        ffUIMouseEvent event(ffMouseButton::None, msg[0].ToInt() - (fInt)parentGlobalLocal.x, msg[1].ToInt() - (fInt)parentGlobalLocal.y, msg[2].ToDouble());
        return OnMouseWheel(&event);
    }
    }

    return OnMsg(msg);
}

fBool ffUIView::OnMsg(const ffMsg &msg) {
    /*
    switch (msg.GetType())
    {
    
    }
    */
    return false; 
}

void ffUIView::SetParentView(ffUIView *pView) {
    m_pParent = pView;
}

fBool ffUIView::OnEnter(ffUIEvent *pEvent) {
    return Enter.Do(this, pEvent);
}

fBool ffUIView::OnLeave(ffUIEvent *pEvent) {
    return Leave.Do(this, pEvent);
}

fBool ffUIView::OnMouseEnter(ffUIEvent *pEvent) {
    return MouseEnter.Do(this, pEvent);
}

fBool ffUIView::OnMouseLeave(ffUIEvent *pEvent) {
    return MouseLeave.Do(this, pEvent);
}

fBool ffUIView::OnMouseDown(ffUIMouseEvent *pEvent) {
    return MouseDown.Do(this, pEvent);
}

fBool ffUIView::OnMouseUp(ffUIMouseEvent *pEvent) {
    return MouseUp.Do(this, pEvent);
}

fBool ffUIView::OnMouseDoubleClick(ffUIEvent *pEvent) {
    return MouseDoubleClick.Do(this, pEvent);
}

fBool ffUIView::OnMouseMove(ffUIMouseEvent *pEvent) {
    MouseMove.Do(this, pEvent);
    return true;
}

fBool ffUIView::OnMouseWheel(ffUIMouseEvent *pEvent) {
    return MouseWheel.Do(this, pEvent);
}
fBool ffUIView::OnKeyDown(ffUIKeyEvent *pEvent) {
    return KeyDown.Do(this, pEvent);
}

fBool ffUIView::OnKeyUp(ffUIKeyEvent *pEvent) {
    return KeyUp.Do(this, pEvent);
}

fBool ffUIView::OnUpdate(ffUpdateEvent *pEvent) {
    return Update.Do(this, pEvent);
}

fBool ffUIView::OnRender(ffRenderEvent *pEvent) {
    return Render.Do(this, pEvent);
}