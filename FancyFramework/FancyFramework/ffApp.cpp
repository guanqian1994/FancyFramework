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
///        file :   ffApp.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffApp.h"
#include "ffScene.h"

#include "fcyMisc\fcyStringHelper.h"
////////////////////////////////////////////////////////////////////////////////
/// @brief 消息类
////////////////////////////////////////////////////////////////////////////////
ffMsg::ffMsgParam::ffMsgParam() {
    m_param = 0L;
};

ffMsg::ffMsgParam::ffMsgParam(fuLong value) {
    m_param = value;
};

fInt ffMsg::ffMsgParam::ToInt() const {
    return static_cast<fInt>(m_param);
}

fDouble ffMsg::ffMsgParam::ToDouble() const {
    return *(fDouble*)(&m_param);
}

fCharW ffMsg::ffMsgParam::ToChar() const {
    return static_cast<fChar>(m_param);
}

fCharW ffMsg::ffMsgParam::ToCharW() const {
    return static_cast<fCharW>(m_param);
}

fcStrW ffMsg::ffMsgParam::ToStrW() const {
    return (fcStrW)m_param;
}

void *ffMsg::ffMsgParam::ToPtr() const {
    return (void*)m_param;
}

void ffMsg::ffMsgParam::Set(fuLong value) {
    m_param = value;
}

fuLong ffMsg::ffMsgParam::Get() const {
    return m_param;
}

ffMsg::ffMsg() {
    
}

ffMsg::ffMsg(const f2dMsg &msg) {
    m_type = msg.Type;
    m_param[0].Set(msg.Param1);
    m_param[1].Set(msg.Param2);
    m_param[2].Set(msg.Param3);
    m_param[3].Set(msg.Param4);
}

F2DMSGTYPE ffMsg::GetType() const {
    return m_type;
}

ffMsg::ffMsgParam &ffMsg::operator[](fInt index) {
    return m_param[index];
}

const ffMsg::ffMsgParam &ffMsg::operator[](fInt index) const {
    return m_param[index];
}


////////////////////////////////////////////////////////////////////////////////
/// @brief 应用框架事件监听
////////////////////////////////////////////////////////////////////////////////
void ffAppEventListener::OnCreate(ffApp &app) { 
}

void ffAppEventListener::OnDestroy(ffApp &app) {
}

void ffAppEventListener::OnRemoveScene(ffScene *pScene) {
    pScene->Release();
}

fBool ffAppEventListener::OnMsg(const ffMsg &msg) { 
    return false; 
}

void ffAppEventListener::OnUpdate(fDouble elapsedTime) { 
}

void ffAppEventListener::OnRender(fDouble elapsedTime, ffGraphics *pGraph) {
}

void ffAppEventListener::OnLastRender(fDouble elapsedTime, ffGraphics *pGraph) {
}

////////////////////////////////////////////////////////////////////////////////
/// @brief 缓冲区
////////////////////////////////////////////////////////////////////////////////

ffBuffer::ffBuffer() : m_bufferSize(0), m_pBuffer(0) {
}

ffBuffer::~ffBuffer() {
    delete m_pBuffer;
}

char *ffBuffer::CheckBuffer(size_t needSize) {
    if (needSize > m_bufferSize) {
        /*首次申请*/
        if (m_pBuffer == 0) {
            m_bufferSize = 1024;
            m_pBuffer = new char[m_bufferSize];
            return CheckBuffer(needSize);
        }
        else {
            delete m_pBuffer;
            m_bufferSize *= 2;
            m_pBuffer = new char[m_bufferSize];
            return CheckBuffer(needSize);
        }
    }
    return m_pBuffer;
}

char *ffBuffer::GetBuffer() {
    return m_pBuffer;
}

size_t ffBuffer::GetSize() {
    return m_bufferSize;
}