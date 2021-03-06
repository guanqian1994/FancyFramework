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
ffSpriteImpl::ffSpriteImpl(ffTextureSrc *pSrc, fcStrW path) : m_pSprite(NULL) {
    m_pSrc = pSrc;
    m_path = path;

    ffAppImpl::Get().GetEngine()->GetRenderer()->CreateSprite2D(pSrc->pTexture, &m_pSprite);

    ffAssert(m_pSprite);
}

ffSpriteImpl::~ffSpriteImpl() {
    FCYSAFEKILL(m_pSprite);
    FCYSAFEKILL(m_pSrc);
}

fcStrW ffSpriteImpl::GetType() const {
    return ffSprite::TypeName;
}

f2dSprite *ffSpriteImpl::Get() {
    return m_pSprite;
}

////////////////////////////////////////////////////////////////////////////////
/// ffFontImpl
////////////////////////////////////////////////////////////////////////////////
ffFontImpl::ffFontImpl(f2dFontProvider *pFontProvider, fcStrW path) : m_pFontRenderer(NULL) {
    m_pFontProvider = pFontProvider;
    m_path = path;

    ffAppImpl::Get().GetEngine()->GetRenderer()->CreateFontRenderer(pFontProvider, &m_pFontRenderer);

    ffAssert(m_pFontRenderer);
}

ffFontImpl::~ffFontImpl() {
    FCYSAFEKILL(m_pFontRenderer);
    FCYSAFEKILL(m_pFontProvider);
}

fcStrW ffFontImpl::GetType() const{
    return ffFont::TypeName;
}

f2dFontRenderer *ffFontImpl::Get() {
    return m_pFontRenderer;
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
}

ffSoundImpl::~ffSoundImpl() {
    FCYSAFEKILL(m_pSoundbuf);
    FCYSAFEKILL(m_pSrc);
}

fcStrW ffSoundImpl::GetType() const {
    return ffSound::TypeName;
}

f2dSoundBuffer *ffSoundImpl::Get() {
    return m_pSoundbuf;
}

////////////////////////////////////////////////////////////////////////////////
/// ffVideoImpl
////////////////////////////////////////////////////////////////////////////////
ffVideoImpl::ffVideoImpl(f2dStream *pStream, fcStrW path, fInt options) : m_pVideo(NULL) {
    m_path = path;

    ffAppImpl::Get().GetEngine()->GetVideoSys()->CreateVideo(pStream, options, &m_pVideo);

    ffAssert(m_pVideo);
}

ffVideoImpl::~ffVideoImpl() {
    FCYSAFEKILL(m_pVideo);
}

fcStrW ffVideoImpl::GetType() const {
    return ffVideo::TypeName;
}

f2dVideo *ffVideoImpl::Get() {
    return m_pVideo;
}

////////////////////////////////////////////////////////////////////////////////
/// ffJsonImpl
////////////////////////////////////////////////////////////////////////////////
ffJsonImpl::ffJsonImpl(f2dStream *pStream, fcStrW path) : m_pJson(NULL) {
    m_pJson = new fcyJson((fcyStream*)pStream);
    m_path = path;
}

ffJsonImpl::~ffJsonImpl() {
    delete m_pJson;
}

fcStrW ffJsonImpl::GetType() const {
    return ffJson::TypeName;
}

fcyJson *ffJsonImpl::Get() {
    return m_pJson;
}

////////////////////////////////////////////////////////////////////////////////
/// ffIniImpl
////////////////////////////////////////////////////////////////////////////////
ffIniImpl::ffIniImpl(f2dStream *pStream, fcStrW path) : m_pIni(NULL) {
    m_pIni = new fcyIni((fcyStream*)pStream);
    m_path = path;
}

ffIniImpl::~ffIniImpl(){
    delete m_pIni;
}

fcStrW ffIniImpl::GetType() const {
    return ffIni::TypeName;
}

fcyIni *ffIniImpl::Get() {
    return m_pIni;
}

////////////////////////////////////////////////////////////////////////////////
/// ffXmlImpl
////////////////////////////////////////////////////////////////////////////////

ffXmlImpl::ffXmlImpl(f2dStream *pStream, fcStrW path) : m_pXmlDoc(NULL) {
    m_pXmlDoc = new fcyXmlDocument((fcyStream*)pStream);
    m_path = path;
}

ffXmlImpl::~ffXmlImpl() {
    delete m_pXmlDoc;
}

fcStrW ffXmlImpl::GetType() const {
    return ffXml::TypeName;
}

fcyXmlDocument *ffXmlImpl::Get() {
    return m_pXmlDoc;
}