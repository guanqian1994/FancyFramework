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

#include <fcyRefObj.h>
#include <f2d.h>
#include "..\ffRes.h"

struct ffTextureSrc;
struct ffSoundSrc;

////////////////////////////////////////////////////////////////////////////////
/// @brief 贴图精灵接口实现
////////////////////////////////////////////////////////////////////////////////
class ffSpriteImpl : public fcyRefObjImpl<ffSprite> {
public:
    ffSpriteImpl(ffTextureSrc *pSrc, fcStrW path);
    ~ffSpriteImpl();

    virtual fcStrW GetType() const;

    /// @brief 获得 f2d 贴图精灵接口
    virtual f2dSprite *operator ->();

    virtual f2dSprite &operator *();

private:
    f2dSprite *m_pSprit;
    ffTextureSrc *m_pSrc;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 音频对象接口实现
////////////////////////////////////////////////////////////////////////////////
struct ffSoundImpl : public fcyRefObjImpl<ffSound> {
public:
    ffSoundImpl(ffSoundSrc *pSrc, fcStrW path, fInt options);
    ~ffSoundImpl();

    virtual fcStrW GetType() const;

    /// @brief 获得 f2d 音频对象接口
    virtual f2dSoundBuffer *operator ->();

    virtual f2dSoundBuffer &operator *();

private:
    f2dSoundBuffer *m_pSoundbuf;
    ffSoundSrc *m_pSrc;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 视频对象接口实现
////////////////////////////////////////////////////////////////////////////////
struct ffVideoImpl : public ffVideo {
public:
    virtual fcStrW GetType() const;

    /// @brief 获得 f2d 视频对象接口
    virtual f2dVideo *operator ->();

    virtual f2dVideo &operator *();

private:
    fuInt m_ref;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Json对象接口实现
////////////////////////////////////////////////////////////////////////////////
struct ffJsonImpl : public ffJson {
public:
    virtual fcStrW GetType() const;
    /// @brief 获得 f2d Json对象
    virtual fcyJson *operator ->();

    virtual fcyJson &operator *();

private:
    fuInt m_ref;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Ini对象接口实现
////////////////////////////////////////////////////////////////////////////////
struct ffIniImpl : public ffIni {
public:
    virtual fcStrW GetType() const;
    /// @brief 获得 f2d Ini对象
    virtual fcyIni *operator ->();

    virtual fcyIni &operator *();

private:
    fuInt m_ref;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Xml文档对象接口实现
////////////////////////////////////////////////////////////////////////////////
struct ffXmlImpl : public ffXml {
public:
    virtual fcStrW GetType() const;

    /// @brief 获得 f2d Xml文档对象
    virtual fcyXmlDocument *operator ->();

    virtual fcyXmlDocument &operator *();

private:
    fuInt m_ref;
};