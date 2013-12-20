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
///        file :   ffResTypesImpl.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffResTypesImpl.h"
#include "ffResImpl.h"
#include "..\App\ffAppImpl.h"

fcStrW ffSprite::TypeName = L"ffSprite";
fcStrW ffSound::TypeName = L"ffSound";
fcStrW ffVideo::TypeName = L"ffVideo";
fcStrW ffJson::TypeName = L"ffJson";
fcStrW ffIni::TypeName = L"ffIni";
fcStrW ffXml::TypeName = L"ffXml";

ffSprite *ffSprite::Create(fcStrW resPath) {
    return ffResImpl::Get().CreateSprite(resPath);
}

////////////////////////////////////////////////////////////////////////////////
/// ffSpriteImpl
////////////////////////////////////////////////////////////////////////////////
ffSpriteImpl::ffSpriteImpl(ffTextureSrc *pSrc) {
    m_pSrc = pSrc;
    ffAppImpl::Get().GetEngine()->GetRenderer()->CreateSprite2D(pSrc->pTexture, &m_pSprit);
    assert(m_pSprit);
}

ffSpriteImpl::~ffSpriteImpl() {
    FCYSAFEKILL(m_pSprit);
    m_pSrc->Release();
}

fcStrW ffSpriteImpl::GetType() const {
    return ffSprite::TypeName;
}

/// @brief 获得 f2d 贴图精灵接口
f2dSprite *ffSpriteImpl::operator ->() {
    return m_pSprit;
}

f2dSprite &ffSpriteImpl::operator *() {
    return *m_pSprit;
}

////////////////////////////////////////////////////////////////////////////////
/// ffSoundImpl
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// ffVideoImpl
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// ffJsonImpl
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// ffIniImpl
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// ffXmlImpl
////////////////////////////////////////////////////////////////////////////////