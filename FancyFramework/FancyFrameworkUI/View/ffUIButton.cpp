////////////////////////////////////////////////
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
///        file :   ffUIButton.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffUIButton.h"

ffUIButton *ffUIButton::Create(ffUIView *pParent, ffPoint local, ffSize size) {
    if (pParent) {
        ffUIButton *pButton = new ffUIButton(pParent);

        pButton->Location = local;
        pButton->Size = size;

        return pButton;
    }
    return NULL;
}

fBool ffUIButton::OnMouseEnter(ffUIEvent *pEvent) {
    State.Set(Activate);
    MouseEnter.Do(this, pEvent);
    return true;
}

fBool ffUIButton::OnMouseLeave(ffUIEvent *pEvent) {
    State.Set(Normal);
    MouseLeave.Do(this, pEvent);
    return true;
}

fBool ffUIButton::OnMouseDown(ffUIMouseEvent *pEvent) {
    if (pEvent->Button == ffMouseButton::Left) {
        State.Set(Push);
    }

    MouseDown.Do(this, pEvent);
    return true;
}

fBool ffUIButton::OnMouseUp(ffUIMouseEvent *pEvent) {
    if (pEvent->Button == ffMouseButton::Left) {
        State.Set(Activate);
    }

    MouseUp.Do(this, pEvent);
    return true;
}

fBool ffUIButton::OnMouseDoubleClick(ffUIEvent *pEvent) {
    return ffUIView::OnMouseDoubleClick(pEvent);
}

fBool ffUIButton::OnMouseMove(ffUIMouseEvent *pEvent) {
    return ffUIView::OnMouseMove(pEvent);
}

fBool ffUIButton::OnMouseWheel(ffUIMouseEvent *pEvent) {
    return ffUIView::OnMouseWheel(pEvent);
}

fBool ffUIButton::OnRender(ffRenderEvent *pEvent) {
    ffUIButton::OnRenderOriginal(pEvent);
    ffUILable::OnRenderOriginal(pEvent);
    Render.Do(this, pEvent);
    return true;
}

void ffUIButton::OnRenderOriginal(ffRenderEvent *pEvent) {
    ffSprite::Ref *pSprite = &m_sprite[Normal];

    switch (State.Get())
    {
    case Activate:
        if (ImageActivate.Get() != nullptr) {
            pSprite = &m_sprite[Activate];
        }
        break;
    case Push:
        if (ImagePush.Get() != nullptr) {
            pSprite = &m_sprite[Push];
        }
        break;
    default:
        break;
    }

    if (pSprite->Valid())
        (*pSprite)->Draw(pEvent->pGraph, pEvent->Dest);
}

ffUIButton::ffUIButton(ffUIView *pParent) : ffUILable(pParent), m_curState(Status::Normal),

    ImageNormal(
    [&](ffSprite *p)->void { m_sprite[Normal] = p; },
    [&]()->ffSprite *{ return m_sprite[Normal].GetPtr(); }),

    ImageActivate(
    [&](ffSprite *p)->void { m_sprite[Activate] = p; },
    [&]()->ffSprite *{ return m_sprite[Activate].GetPtr(); }),

    ImagePush(
    [&](ffSprite *p)->void { m_sprite[Push] = p; },
    [&]()->ffSprite *{ return m_sprite[Push].GetPtr(); }),

    State(
    [&](const Status &p)->void { m_curState = p; },
    [&]()->const Status &{ return m_curState; })
{

}