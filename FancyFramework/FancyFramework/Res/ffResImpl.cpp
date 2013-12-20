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
///        file :   ffResImpl.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffResImpl.h"
#include "ffResTypesImpl.h"
#include "..\App\ffAppImpl.h"

fcStrW ffTextureSrc::TypeName = L"ffTextureSrc";

ffRes &ffRes::Get() {
    return ffResImpl::Get();
}

ffResImpl *ffResImpl::s_pSingleton = NULL;

ffResImpl &ffResImpl::Get() {
    return *s_pSingleton;
}

ffResImpl::ffResImpl() {
    ffAssert(!s_pSingleton);
    s_pSingleton = this;
}

ffResImpl::~ffResImpl() {
    ffResSrcRef::iterator iter = m_resSrcRef.begin();

    for (iter; iter != m_resSrcRef.end(); ++iter) {
        /// 存在未释放资源
        ffAssertPrint(iter->second == NULL, "存在未释放的资源");
    }

    s_pSingleton = NULL;
}

fBool ffResImpl::LoadPackage(fcStrW path, fcStrW filePath) {
    return FCYFAILED(!ffAppImpl::Get().GetEngine()->GetFileSys()->LoadResPackage(path, filePath));
}

fBool ffResImpl::LoadPath(fcStrW path, fcStrW dirPath) {
    return FCYFAILED(!ffAppImpl::Get().GetEngine()->GetFileSys()->LoadRealPath(path, dirPath));
}

ffSprite *ffResImpl::CreateSprite(fcStrW resPath) {
    ffTextureSrc *pSrc = CreateTexture(resPath);
    if (pSrc == NULL)
        return NULL;
    return new ffSpriteImpl(pSrc);
}

ffSound *ffResImpl::CreateSound(fcStrW resPath) {
    return 0;
}

ffVideo *ffResImpl::CreateVideo(fcStrW resPath) {
    return 0;
}

ffJson *ffResImpl::CreateJson(fcStrW resPath) {
    return 0;
}

ffIni *ffResImpl::CreateIni(fcStrW resPath) {
    return 0;
}

ffXml *ffResImpl::CreateXml(fcStrW resPath) {
    return 0;
}

ffTextureSrc *ffResImpl::CreateTexture(const std::wstring &path) {
    ffAppImpl &pAppImpl = ffAppImpl::Get();

    ffResSrcRef::iterator result = m_resSrcRef.find(path);

    if (result != m_resSrcRef.end() && result->second != NULL) {
        /// 已经载入了这个贴图

        ffAssert(result->second->Type() == ffTextureSrc::TypeName);

        ffTextureSrc *pffTex = static_cast<ffTextureSrc*>(result->second);

        pffTex->AddRef();

        return pffTex;
    } 
    else {
        /// 没有载入这个贴图，则创建
        f2dTexture2D *pTex = NULL;

        f2dStream *pTexStream = this->GetStream(path);

        if (pTexStream == NULL)
            return NULL;

        pAppImpl.GetRenderDevice()->CreateTextureFromStream(
            pTexStream, 0, 0, false, true, &pTex);
        
        ffTextureSrc *pffTex = new ffTextureSrc(pTex);

        if (result != m_resSrcRef.end()) {
            result->second = pffTex;
            pffTex->SetListPos(&result->second);
        } else {
            result = m_resSrcRef.insert(std::make_pair(path, pffTex)).first;
            pffTex->SetListPos(&result->second);
        }

        pffTex->AddRef();

        return pffTex;
    }
}

f2dStream *ffResImpl::GetStream(const std::wstring &path) {
    f2dStream *pStream;

    pStream = ffAppImpl::Get().GetEngine()->GetFileSys()->GetStream(path.c_str());

    if (pStream != NULL) {
        pStream->SetPosition(F2DSEEKORIGIN_BEG, 0);
    }

    return pStream;
}