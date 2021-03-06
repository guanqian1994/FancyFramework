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
///        file :   ffScreenGraphics2DImpl.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////

#include "ffGraphicsImpl.h"

#include "ffCameraImpl.h"
#include "..\ffApp.h"
#include "..\ffAssert.h"

ffGraphicsImpl::ffGraphicsImpl(f2dGraphics2D *pGraph, ffCameraImpl *pCamera)
    : m_pGraph(pGraph), m_pCamera(pCamera) {
    m_prevView = Invalid;
}

fResult ffGraphicsImpl::Begin(ffGraphics::View viewType) {

    if (viewType != m_prevView) {
        switch (viewType) {
        case ffGraphics::Camera:
            m_pGraph->SetViewTransform(ffCameraImpl::Get().GetCameraView());
            break;
        case ffGraphics::Screen:
            m_pGraph->SetViewTransform(ffCameraImpl::Get().GetScreenView());
            break;
        default:
            ffAssertPrint(0, "Invalid value");
            return -1;
        }
        m_prevView = viewType;
    }

    return m_pGraph->Begin();
}