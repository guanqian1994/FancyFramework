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
///        file :   ffCameraImpl.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffCameraImpl.h"
#include "..\ffAssert.h"

ffCamera &ffCamera::Get() {
    return ffCameraImpl::Get();
}

ffCameraImpl *ffCameraImpl::s_pSingleton = NULL;

ffCameraImpl &ffCameraImpl::Get() {
    return *s_pSingleton;
}

ffCameraImpl::ffCameraImpl(f2dGraphics2D *pGraph) : m_pGraph(pGraph) {
    ffAssert(!s_pSingleton);

    m_currentStatus.position.Set(0.f, 0.f);
    m_currentStatus.scale = 1.f;
    s_pSingleton = this;
}

ffCameraImpl::~ffCameraImpl() {
    s_pSingleton = NULL;
}

void ffCameraImpl::SetStatus(const ffCameraStatus &status) {
    m_currentStatus = status;
}

void ffCameraImpl::SetScale(fFloat scale) {
    m_currentStatus.scale = scale;
}

void ffCameraImpl::SetPosition(const fcyVec2 &pos) {
    m_currentStatus.position = pos;
}

ffCameraStatus &ffCameraImpl::GetStatus() {
    return m_currentStatus;
}

const ffCameraStatus &ffCameraImpl::GetStatus() const {
    return m_currentStatus;
}

fFloat &ffCameraImpl::GetScale() {
    return m_currentStatus.scale;
}

fFloat ffCameraImpl::GetScale() const {
    return m_currentStatus.scale;
}

const fcyVec2 &ffCameraImpl::GetPosition() {
    return m_currentStatus.position;
}

const fcyVec2 &ffCameraImpl::GetPosition() const {
    return m_currentStatus.position;
}

fcyMatrix4 ffCameraImpl::GetCameraView() const {
    return m_mat;
}

fcyMatrix4 ffCameraImpl::GetScreenView() const {
    return fcyMatrix4::GetIdentity();
}

void ffCameraImpl::UpDateMatrix() {
    fcyVec2 winSize = ffApp::Get().GetBufferSize();
    fcyVec3 offset(-m_currentStatus.position.x * m_currentStatus.scale + winSize.x / 2, 
        -m_currentStatus.position.y * m_currentStatus.scale + winSize.y / 2, 0.f);
    m_mat =
        fcyMatrix4::GetScaleMatrix(m_currentStatus.scale)*
        fcyMatrix4::GetTranslateMatrix(offset)
        ;
}