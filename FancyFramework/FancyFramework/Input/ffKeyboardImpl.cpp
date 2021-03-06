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
///        file :   ffKeyboardImpl.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffKeyboardImpl.h"

#include <cassert>
#include "..\App\ffAppImpl.h"

ffKeyboard &ffKeyboard::Get() {
    return ffKeyboardImpl::Get();
}

ffKeyboardImpl *ffKeyboardImpl::s_pSingleton = NULL;

ffKeyboardImpl &ffKeyboardImpl::Get() {
    return *s_pSingleton;
}

ffKeyboardImpl::ffKeyboardImpl(ffAppImpl *pApp) {
    assert(!s_pSingleton);

    pApp->GetEngine()->GetInputSys()->CreateKeyboard(-1, false, &m_pInputKeyboard);

    s_pSingleton = this;
}

ffKeyboardImpl::~ffKeyboardImpl() {
    s_pSingleton = NULL;
}

fBool ffKeyboardImpl::IsKeyDown(F2DINPUTKEYCODE KeyCode) {
    return m_pInputKeyboard->IsKeyDown(KeyCode);
}

void ffKeyboardImpl::Update() {
    m_pInputKeyboard->UpdateState();
}