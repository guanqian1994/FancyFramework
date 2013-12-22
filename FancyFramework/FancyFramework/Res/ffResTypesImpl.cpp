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
#include "fcyIO\fcyStream.h"
#include "fcyParser\fcyIni.h"
#include "fcyParser\fcyXml.h"
#include "fcyParser\fcyJson.h"

fcStrW ffSprite::TypeName = L"ffSprite";
fcStrW ffFont::TypeName = L"ffFont";
fcStrW ffSound::TypeName = L"ffSound";
fcStrW ffVideo::TypeName = L"ffVideo";
fcStrW ffJson::TypeName = L"ffJson";
fcStrW ffIni::TypeName = L"ffIni";
fcStrW ffXml::TypeName = L"ffXml";

ffSprite *ffSprite::Create(fcStrW resPath) {
    return ffResImpl::Get().CreateSprite(resPath);
}

ffFont *ffFont::CreateFromFile(fcStrW resPath, fuInt faceIndex, const fcyVec2 &fontSize, F2DFONTFLAG flag) {
    return ffResImpl::Get().CreateFontFromFile(resPath, faceIndex, fontSize, flag);
}

ffFont *ffFont::CreateFromSystem(fcStrW faceName, fuInt faceIndex, const fcyVec2 &fontSize, F2DFONTFLAG flag) {
    return ffResImpl::Get().CreateFontFromSystem(faceName, faceIndex, fontSize, flag);
}

ffSound *ffSound::Create(fcStrW resPath, fInt options) {
    return ffResImpl::Get().CreateSound(resPath, options);
}

ffVideo *ffVideo::Create(fcStrW resPath, fInt options) {
    return ffResImpl::Get().CreateVideo(resPath, options);
}

ffJson *ffJson::Create(fcStrW resPath) {
    return ffResImpl::Get().CreateJson(resPath);
}

ffIni *ffIni::Create(fcStrW resPath) {
    return ffResImpl::Get().CreateIni(resPath);
}

ffXml *ffXml::Create(fcStrW resPath) {
    return ffResImpl::Get().CreateXml(resPath);
}

////////////////////////////////////////////////////////////////////////////////
/// ffSpriteImpl
////////////////////////////////////////////////////////////////////////////////
ffSpriteImpl::ffSpriteImpl(ffTextureSrc *pSrc, fcStrW path) : m_pSprit(NULL) {
    m_pSrc = pSrc;
    m_path = path;

    ffAppImpl::Get().GetEngine()->GetRenderer()->CreateSprite2D(pSrc->pTexture, &m_pSprit);
    
    ffAssert(m_pSprit);

    ffResImpl::AddResCount();
}

ffSpriteImpl::~ffSpriteImpl() {
    FCYSAFEKILL(m_pSprit);
    FCYSAFEKILL(m_pSrc);

    ffResImpl::MinusResCount();
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
/// ffFontImpl
////////////////////////////////////////////////////////////////////////////////
ffFontImpl::ffFontImpl(f2dFontProvider *pFontProvider, fcStrW path) : m_pFontRenderer(NULL) {
    m_pFontProvider = pFontProvider;
    m_path = path;

    ffAppImpl::Get().GetEngine()->GetRenderer()->CreateFontRenderer(pFontProvider, &m_pFontRenderer);

    ffAssert(m_pFontRenderer);

    ffResImpl::AddResCount();
}

ffFontImpl::~ffFontImpl() {
    FCYSAFEKILL(m_pFontRenderer);
    FCYSAFEKILL(m_pFontProvider);

    ffResImpl::MinusResCount();
}

fcStrW ffFontImpl::GetType() const{
    return ffFont::TypeName;
}

f2dFontRenderer *ffFontImpl::operator ->() {
    return m_pFontRenderer;
}

f2dFontRenderer &ffFontImpl::operator *() {
    return *m_pFontRenderer;
}

////////////////////////////////////////////////////////////////////////////////
/// ffSoundImpl
////////////////////////////////////////////////////////////////////////////////

ffSoundImpl::ffSoundImpl(ffSoundSrc *pSrc, fcStrW path, fInt options) : m_pSoundbuf(NULL) {
    m_pSrc = pSrc;
    m_path = path;
    
    if (options & ffSound::Option::Dynamic) {
        ffAppImpl::Get().GetEngine()->GetSoundSys()->CreateDynamicBuffer(
            pSrc->pDecoder, options & ffSound::Option::GlobalFocus, &m_pSoundbuf);
    } else if (options & ffSound::Option::Static) {
        ffAppImpl::Get().GetEngine()->GetSoundSys()->CreateStaticBuffer(
            pSrc->pDecoder, options & ffSound::Option::GlobalFocus, &m_pSoundbuf);
    }

    ffAssert(m_pSoundbuf);

    ffResImpl::AddResCount();
}

ffSoundImpl::~ffSoundImpl() {
    FCYSAFEKILL(m_pSoundbuf);
    FCYSAFEKILL(m_pSrc);

    ffResImpl::MinusResCount();
}

fcStrW ffSoundImpl::GetType() const {
    return ffSound::TypeName;
}

f2dSoundBuffer *ffSoundImpl::operator ->() {
    return m_pSoundbuf;
}

f2dSoundBuffer &ffSoundImpl::operator *() {
    return *m_pSoundbuf;
}

////////////////////////////////////////////////////////////////////////////////
/// ffVideoImpl
////////////////////////////////////////////////////////////////////////////////
ffVideoImpl::ffVideoImpl(f2dStream *pStream, fcStrW path, fInt options) : m_pVideo(NULL) {
    m_path = path;

    ffAppImpl::Get().GetEngine()->GetVideoSys()->CreateVideo(pStream, options, &m_pVideo);

    ffAssert(m_pVideo);

    ffResImpl::AddResCount();
}

ffVideoImpl::~ffVideoImpl() {
    FCYSAFEKILL(m_pVideo);

    ffResImpl::MinusResCount();
}

fcStrW ffVideoImpl::GetType() const {
    return ffVideo::TypeName;
}

f2dVideo *ffVideoImpl::operator ->() {
    return m_pVideo;
}

f2dVideo &ffVideoImpl::operator *() {
    return *m_pVideo;
}

////////////////////////////////////////////////////////////////////////////////
/// ffJsonImpl
////////////////////////////////////////////////////////////////////////////////
ffJsonImpl::ffJsonImpl(f2dStream *pStream, fcStrW path) : m_pJson(NULL) {
    m_pJson = new fcyJson((fcyStream*)pStream);
    m_path = path;

    ffResImpl::AddResCount();
}

ffJsonImpl::~ffJsonImpl() {
    delete m_pJson;

    ffResImpl::MinusResCount();
}

fcStrW ffJsonImpl::GetType() const {
    return ffJson::TypeName;
}

fcyJson *ffJsonImpl::operator ->() {
    return m_pJson;
}

fcyJson &ffJsonImpl::operator *() {
    return *m_pJson;
}

////////////////////////////////////////////////////////////////////////////////
/// ffIniImpl
////////////////////////////////////////////////////////////////////////////////
ffIniImpl::ffIniImpl(f2dStream *pStream, fcStrW path) : m_pIni(NULL) {
    m_pIni = new fcyIni((fcyStream*)pStream);
    m_path = path;

    ffResImpl::AddResCount();
}

ffIniImpl::~ffIniImpl(){
    delete m_pIni;

    ffResImpl::MinusResCount();
}

fcStrW ffIniImpl::GetType() const {
    return ffIni::TypeName;
}

fcyIni *ffIniImpl::operator ->() {
    return m_pIni;
}

fcyIni &ffIniImpl::operator *() {
    return *m_pIni;
}

////////////////////////////////////////////////////////////////////////////////
/// ffXmlImpl
////////////////////////////////////////////////////////////////////////////////

ffXmlImpl::ffXmlImpl(f2dStream *pStream, fcStrW path) : m_pXmlDoc(NULL) {
    m_pXmlDoc = new fcyXmlDocument((fcyStream*)pStream);
    m_path = path;

    ffResImpl::AddResCount();
}

ffXmlImpl::~ffXmlImpl() {
    delete m_pXmlDoc;

    ffResImpl::MinusResCount();
}

fcStrW ffXmlImpl::GetType() const {
    return ffXml::TypeName;
}

fcyXmlDocument *ffXmlImpl::operator ->() {
    return m_pXmlDoc;
}

fcyXmlDocument &ffXmlImpl::operator *() {
    return *m_pXmlDoc;
}