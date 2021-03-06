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
///        file :   ffResTypesImpl.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "..\ffRes.h"

#include <f2d.h>

struct ffTextureSrc;
struct ffSoundSrc;

////////////////////////////////////////////////////////////////////////////////
/// @brief 资源基类
////////////////////////////////////////////////////////////////////////////////
template<class T>
class ffResObjImpl : public fcyRefObjImpl<T> {
public:
    /// @brief 获取当前资源路径
    virtual fcStrW GetPath() const { return m_path.c_str(); };

protected:
    std::wstring m_path;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 贴图精灵接口实现
////////////////////////////////////////////////////////////////////////////////
class ffSpriteImpl : public ffResObjImpl<ffSprite> {
public:
    ffSpriteImpl(ffTextureSrc *pSrc, fcStrW path);
    ~ffSpriteImpl();

    virtual fcStrW GetType() const;

    /// @brief 获得 f2d 贴图精灵接口
    virtual f2dSprite *Get();

private:
    f2dSprite *m_pSprite;
    ffTextureSrc *m_pSrc;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 字体资源接口实现
////////////////////////////////////////////////////////////////////////////////
class ffFontImpl : public ffResObjImpl<ffFont> {
public:
    ffFontImpl(f2dFontProvider *pFontProvider, fcStrW path);
    ~ffFontImpl();

    virtual fcStrW GetType() const;

    /// @brief 获得 f2d 贴图精灵接口
    virtual f2dFontRenderer *Get();

private:
    f2dFontRenderer *m_pFontRenderer;
    f2dFontProvider *m_pFontProvider;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 音频对象接口实现
////////////////////////////////////////////////////////////////////////////////
struct ffSoundImpl : public ffResObjImpl<ffSound> {
public:
    ffSoundImpl(ffSoundSrc *pSrc, fcStrW path, fInt options);
    ~ffSoundImpl();

    virtual fcStrW GetType() const;

    /// @brief 获得 f2d 音频对象接口
    virtual f2dSoundBuffer *Get();

private:
    f2dSoundBuffer *m_pSoundbuf;
    ffSoundSrc *m_pSrc;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 视频对象接口实现
////////////////////////////////////////////////////////////////////////////////
struct ffVideoImpl : public ffResObjImpl<ffVideo> {
public:
    ffVideoImpl(f2dStream *pStream, fcStrW path, fInt options);
    ~ffVideoImpl();

    virtual fcStrW GetType() const;

    /// @brief 获得 f2d 视频对象接口
    virtual f2dVideo *Get();

private:
    f2dVideo *m_pVideo;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Json对象接口实现
////////////////////////////////////////////////////////////////////////////////
struct ffJsonImpl : public ffResObjImpl<ffJson> {
public:
    ffJsonImpl(f2dStream *pStream, fcStrW path);

    ~ffJsonImpl();

    virtual fcStrW GetType() const;

    /// @brief 获得 f2d Json对象
    virtual fcyJson *Get();

private:
    fcyJson *m_pJson;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Ini对象接口实现
////////////////////////////////////////////////////////////////////////////////
struct ffIniImpl : public ffResObjImpl<ffIni> {
public:
    ffIniImpl(f2dStream *pStream, fcStrW path);

    ~ffIniImpl();

    virtual fcStrW GetType() const;

    /// @brief 获得 f2d Ini对象
    virtual fcyIni *Get();

private:
    fcyIni *m_pIni;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Xml文档对象接口实现
////////////////////////////////////////////////////////////////////////////////
struct ffXmlImpl : public ffResObjImpl<ffXml> {
public:
    ffXmlImpl(f2dStream *pStream, fcStrW path);

    ~ffXmlImpl();

    virtual fcStrW GetType() const;

    /// @brief 获得 f2d Xml文档对象
    virtual fcyXmlDocument *Get();

private:
    fcyXmlDocument *m_pXmlDoc;
};