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
///        file :   ffUILayer.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffUILayer.h"
#include <stack>
#include "ffAssert.h"
#include "ffUIEvent.h"

ffUILayer *ffUILayer::Create() {
    return new ffUILayer;
}

/// 迭代访问子UI树结构
struct viewTraversalStackElement {
    ffUIView *pView;
    ffPoint ClientLocal;
    fInt Index;
    fBool Handled;
};

ffUILayer::ffUILayer() : ffUIView(NULL) {
    this->Size.Set(ffApp::Get().GetBufferSize());
    SetUILayer(this);
}

ffUILayer::~ffUILayer() {

}

void ffUILayer::SetCursorImage(ffSprite *pSprite)  {
    m_cursor = pSprite;
    m_cursor->SetHotSpot(m_cursor->GetTexRect().a);
}

void ffUILayer::DebugRender(ffGraphics *pGraph) {
    ffDrawer &drawer = ffDrawer::Get();

    std::stack<viewTraversalStackElement> viewListStack;

    viewListStack.push(viewTraversalStackElement 
    {this, ffPoint(0, 0), 0, false});

    while (!viewListStack.empty()) {
        viewTraversalStackElement *pStackElement =
            &viewListStack.top();

        if (pStackElement->Index == pStackElement->pView->GetChilds().Size()) {

            if (pStackElement->pView->Enabled() == false) {
                drawer.SetColor(ffColors::Gray);
            } else if (pStackElement->pView == m_pMouseOn) {
                drawer.SetColor(ffColors::Red);
            } else if (pStackElement->pView == m_pSelected) {
                drawer.SetColor(ffColors::Blue);
            } else {
                drawer.SetColor(ffColors::Black);
            }

            ffDrawer::Get().DrawRectangle(pGraph,
                fcyRect(pStackElement->ClientLocal + pStackElement->pView->Location.Get(),
                pStackElement->ClientLocal + pStackElement->pView->Location.Get() + pStackElement->pView->Size.Get()));

            viewListStack.pop();

            continue;
        }

        if (pStackElement->pView->GetChilds().Size() != 0) {
            ffUIView *childView = pStackElement->pView->GetChilds().GetView(pStackElement->Index);

            viewListStack.push(viewTraversalStackElement {
                childView,
                ffPoint(pStackElement->pView->Location.Get() + pStackElement->ClientLocal),
                0, false});
        }

        ++pStackElement->Index;
    }
}

fBool ffUILayer::OnMsg(const ffMsg &msg) {
    ffMouse &mouse = ffMouse::Get();
    
    // 标记当前消息已经被处理
    fBool handled = false;

    switch (msg.GetType())
    {
    case F2DMSG_WINDOW_ONMOUSEMOVE: {
        m_cursorPos.x = msg[0].ToInt();
        m_cursorPos.y = msg[1].ToInt();

        if (m_pDragView) {
            return m_pDragView->TryHandleMouseMsg(mouse.GetPos(), this->Location.Get(), msg);
        }
    }
    case F2DMSG_WINDOW_ONMOUSELUP:
    case F2DMSG_WINDOW_ONMOUSELDOWN:
    case F2DMSG_WINDOW_ONMOUSELDOUBLE:
    case F2DMSG_WINDOW_ONMOUSERUP:
    case F2DMSG_WINDOW_ONMOUSERDOWN:
    case F2DMSG_WINDOW_ONMOUSERDOUBLE:
    case F2DMSG_WINDOW_ONMOUSEMUP:
    case F2DMSG_WINDOW_ONMOUSEMDOWN:
    case F2DMSG_WINDOW_ONMOUSEMDOUBLE: {
        return TryHandleMouseMsg(mouse.GetPos(), this->Location.Get(), msg);
    }

    default: {
        if (m_pSelected) {
            return m_pSelected->OnMsg(msg);
        }
    }
    }
    return false;
}

void ffUILayer::OnUpdate(fDouble elapsedTime) {
    std::stack<viewTraversalStackElement> viewListStack;

    viewListStack.push(viewTraversalStackElement 
    { this, ffPoint(0, 0), 0, false });

    ffUpdateEvent event(elapsedTime, fcyRect());

    while (!viewListStack.empty()) {
        viewTraversalStackElement *pStackElement =
            &viewListStack.top();

        if (pStackElement->Handled == false) {
            if (pStackElement->pView->Enabled.Get()) {
                event.Dest.a = pStackElement->ClientLocal + pStackElement->pView->Location.Get();
                event.Dest.b = event.Dest.a + pStackElement->pView->Size.Get();
                pStackElement->pView->OnUpdate(&event);
            }
            pStackElement->Handled = true;
        }

        if (pStackElement->Index == pStackElement->pView->GetChilds().Size()) {
            viewListStack.pop();
            continue;
        }

        if (pStackElement->pView->GetChilds().Size() != 0) {
            ffUIView *childView = pStackElement->pView->GetChilds().GetView(pStackElement->Index);

            viewListStack.push(viewTraversalStackElement{
                childView,
                ffPoint(pStackElement->pView->Location.Get() + pStackElement->ClientLocal),
                0, false });

            ++pStackElement->Index;
        }
    }
}

void ffUILayer::OnRender(fDouble elapsedTime, ffGraphics *pGraph)
{
    pGraph->Begin();

    std::stack<viewTraversalStackElement> viewListStack;

    viewListStack.push(viewTraversalStackElement {
        this, ffPoint(0, 0), 0, false} );

    ffRenderEvent event(elapsedTime, fcyRect(), pGraph);

    while (!viewListStack.empty()) {
        viewTraversalStackElement *pStackElement =
            &viewListStack.top();

        if (pStackElement->Handled == false) {
            if (pStackElement->pView->Visible.Get()) {
                event.Dest.a = pStackElement->ClientLocal + pStackElement->pView->Location.Get();
                event.Dest.b = event.Dest.a + pStackElement->pView->Size.Get();
                pStackElement->pView->OnRender(&event);
            }
            pStackElement->Handled = true;
        }

        if (pStackElement->Index == pStackElement->pView->GetChilds().Size()) {
            viewListStack.pop();
            continue;
        }

        if (pStackElement->pView->GetChilds().Size() != 0) {
            ffUIView *childView = pStackElement->pView->GetChilds().GetView(pStackElement->Index);
            if (childView->Visible()) {
                viewListStack.push(viewTraversalStackElement {
                    childView,
                    ffPoint(pStackElement->pView->Location.Get() + pStackElement->ClientLocal),
                    0});
            }
            ++pStackElement->Index;
        }
    }

    if (m_cursor.Valid()) {
        m_cursor->Draw(pGraph, m_cursorPos);
    }

    if (m_debugDraw) {
        this->DebugRender(pGraph);
    }

    pGraph->End();
}

ffUIView *ffUILayer::GetSelected() {
    return m_pSelected;
}

void ffUILayer::SetSelected(ffUIView *pView) {
    if (m_pSelected == pView) {
        return;
    }

    if (m_pSelected == NULL) {
        m_pSelected = pView;

        if (m_pSelected) {
            m_pSelected->OnEnter(NULL);
        }
    }
    else {
        m_pSelected->OnLeave(NULL);
        m_pSelected = pView;

        if (m_pSelected) {
            m_pSelected->OnEnter(NULL);
        }
    }
}

ffUIView *ffUILayer::GetMouseOn() {
    return m_pMouseOn;
}

void ffUILayer::SetMouseOn(ffUIView *pView) {
    if (m_pMouseOn == pView) {
        return;
    }

    if (m_pMouseOn == NULL) {
        m_pMouseOn = pView;

        if (m_pMouseOn) {
            m_pMouseOn->OnMouseEnter(NULL);
        }
    } else {
        m_pMouseOn->OnMouseLeave(NULL);
        m_pMouseOn = pView;

        if (m_pMouseOn) {
            m_pMouseOn->OnMouseEnter(NULL);
        }
    }
}

void ffUILayer::SetDragView(ffUIView *pView) {
    m_pDragView = pView;
}

void ffUILayer::SetDebugDraw(fBool b) {
    m_debugDraw = b;
}

ffUIView *ffUILayer::GetDragView() {
    return m_pDragView;
}