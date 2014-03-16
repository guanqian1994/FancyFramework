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
#include "ffUIForm.h"
#include "..\ffUILayer.h"

ffUIForm *ffUIForm::Create(ffUIView *pParent, ffPoint local, ffSize size) {
    if (pParent) {
        ffUIForm *pForm = new ffUIForm(pParent);

        pForm->SetLocation(local);
        pForm->SetSize(size);

        return pForm;
    }
    return NULL;
}

void ffUIForm::SetAllowDrag(fBool b) {
}

fBool ffUIForm::GetAllowDrag() const {
    return m_allowDrag;
}

fBool ffUIForm::OnMouseLeave(ffUIEvent *pEvent) {
    return true;
}

fBool ffUIForm::OnMouseDown(ffUIMouseEvent *pEvent) {
    if (m_isDrag == false) {
        m_isDrag = true;
        ffMouse &mouse = ffMouse::Get();

        m_moveOffset.x = pEvent->X - this->GetLocation().x;
        m_moveOffset.y = pEvent->Y - this->GetLocation().y;

        GetUILayer()->SetDragView(this);
    }
    return true;
}

fBool ffUIForm::OnMouseUp(ffUIMouseEvent *pEvent) {
    if (m_isDrag == true) {
        m_isDrag = false;
        GetUILayer()->SetDragView(NULL);
    }
    return true;
}

fBool ffUIForm::OnMouseMove(ffUIMouseEvent *pEvent) {
    if (m_isDrag == true) {
        this->SetLocation(ffPoint(pEvent->X, pEvent->Y) - m_moveOffset);
    }
    return true;
}

ffUIForm::ffUIForm(ffUIView *pParent) 
    : ffUIView(pParent), 
      m_allowDrag(true),
      m_isDrag(false) {
    
}