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
///        file :   ffResImpl.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "..\ffApp.h"
#include "..\ffRes.h"

#include <Windows.h>
#include <string>
#include <unordered_map>
#include <set>
#include <fcyRefObj.h>
#include <f2d.h>

#include "..\ffAssert.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief 源资源
/// @note 加载多个图片或者音频文件时无论顶层有多少个贴图精灵、解码对象，资源管理器只维护一个底层
/// 资源对象，并且对其计数。如果没有引用此源资源的情况下会立即释放。并且从源资源列表里的源资源指针
/// 置为0，但其键值对并没有从列表中移除。
////////////////////////////////////////////////////////////////////////////////
class ffResSrc {
public:
    ffResSrc() : ref(0), pResSrc(NULL) { }

    virtual ~ffResSrc() { ffAssert(ref == 0); }

    /// @brief AddRef实现
    virtual void AddRef()
    {
        InterlockedIncrement(&ref);
    }

    /// @brief Release实现
    virtual void Release()
    {
        fuInt tRet = InterlockedDecrement(&ref);
        if (tRet == 0) {
            ffAssert(*pResSrc == this); *pResSrc = NULL;
            delete this;
        }
    }

    virtual fcStrW Type() const = 0;

    /// 设置在列表中指向本对象的指针
    void SetListPos(ffResSrc **pSrc) {
        ffAssert(pSrc);
        ffAssert(*pSrc == this);

        pResSrc = pSrc;
    }

private:
    fuInt ref;
    ffResSrc **pResSrc;
};

struct ffTextureSrc : public ffResSrc {
    static fcStrW TypeName;

    ffTextureSrc(f2dTexture2D *pTex) : pTexture(pTex) { ffAssert(pTex); }

    ~ffTextureSrc() { pTexture->Release(); }

    virtual fcStrW Type() const { return TypeName; }

    f2dTexture2D *pTexture;
};

struct ffSoundSrc : public ffResSrc {
    static fcStrW TypeName;

    ffSoundSrc(f2dSoundDecoder *pDec) : pDecoder(pDec) { ffAssert(pDec); }

    ~ffSoundSrc() { pDecoder->Release(); }

    virtual fcStrW Type() const { return TypeName; }

    f2dSoundDecoder *pDecoder;
};

/// 资源源引用列表
typedef std::unordered_map<std::wstring, ffResSrc*> ffResSrcRef;

////////////////////////////////////////////////////////////////////////////////
/// @brief 资源管理器接口实现
////////////////////////////////////////////////////////////////////////////////
class ffResImpl : public fcyRefObjImpl<ffRes> {
public:
    /// @brief 获得单例对象
    static ffResImpl &Get();

    ffResImpl();

    ~ffResImpl();

    /// 对外接口
    virtual fBool LoadPackage(fcStrW path, fcStrW filePath);

    virtual fBool LoadPath(fcStrW path, fcStrW dirPath);

    virtual ffSprite *CreateSprite(fcStrW resPath);

    virtual ffFont *CreateFontFromFile(fcStrW resPath, fuInt faceIndex, const fcyVec2 &fontSize, F2DFONTFLAG flag);

    virtual ffFont *CreateFontFromSystem(fcStrW faceName, fuInt faceIndex, const fcyVec2 &fontSize, F2DFONTFLAG flag);

    virtual ffSound *CreateSound(fcStrW resPath, fInt options);

    virtual ffVideo *CreateVideo(fcStrW resPath, fInt options);

    virtual ffJson *CreateJson(fcStrW resPath);

    virtual ffIni *CreateIni(fcStrW resPath);

    virtual ffXml *CreateXml(fcStrW resPath);

    ffTextureSrc *CreateTexture(const std::wstring &path);

    ffSoundSrc *CreateDecoder(const std::wstring &path, fInt options);

    void ResPathGC();

private:
    static ffResImpl *s_pSingleton;

    ffMutexObj<ffResSrcRef> m_resSrcRef;
};