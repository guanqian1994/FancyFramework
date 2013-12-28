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

}

fResult ffGraphicsImpl::Begin(ffGraphics::View viewType) {

    switch (viewType)
    {
    case ffGraphics::Camera: {
            ffCameraStatus &status = m_pCamera->GetStatus();
            fcyVec2 winSize = ffApp::Get().GetWindowSize();
            fcyMatrix4 mat =
                fcyMatrix4::GetScaleMatrix(status.scale) *
                fcyMatrix4::GetRotateZ(-status.rotate) *
                fcyMatrix4::GetTranslateMatrix(fcyVec3(-status.position.x + winSize.x / 2, -status.position.y + winSize.y / 2, 0.f))
                ;
            m_pGraph->SetWorldTransform(mat);
        }

        break;
    case ffGraphics::Screen:
        m_pGraph->SetWorldTransform(fcyMatrix4::GetIdentity());
        break;
    default:
        ffAssertPrint(0, "Invalid value");
        return -1;
    }

    return m_pGraph->Begin();
}