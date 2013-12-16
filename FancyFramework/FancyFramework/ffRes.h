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
///        file :   ffResource.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <fcyMath.h>

struct ffTexture;
class fcyJson;
class fcyIni;
class fcyXmlDocument;

////////////////////////////////////////////////////////////////////////////////
/// @brief 资源基类
////////////////////////////////////////////////////////////////////////////////
struct ffRes {
    enum Status{
        Invalid = 0,    ///< @brief 无效的
        Valid   = 1,    ///< @brief 有效的
        Loading = 2,    ///< @brief 正在载入
    };

    /// @brief 增加接口的引用计数
    virtual void AddRef() = 0;

    /// @brief 减少接口的引用计数
    virtual void Release() = 0;

    /// @brief 获取当前资源状态
    virtual Status GetStatus() const = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 文件流
/// @warning 不能够同时创建多个同一个文件的流
////////////////////////////////////////////////////////////////////////////////
struct ffStream : public ffRes {
    /// @brief 获得 f2d 文件流接口
    virtual f2dStream *operator ->();
    virtual f2dStream &operator *();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 贴图精灵
////////////////////////////////////////////////////////////////////////////////
struct ffSprite : public ffRes {
    /// @brief 获得 f2d 贴图精灵接口
    virtual f2dSprite *operator ->();
    virtual f2dSprite &operator *();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 音频对象
////////////////////////////////////////////////////////////////////////////////
struct ffSound : public ffRes {
    /// @brief 获得 f2d 音频对象接口
    virtual f2dSoundBuffer *operator ->();
    virtual f2dSoundBuffer &operator *();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 视频对象
////////////////////////////////////////////////////////////////////////////////
struct ffVideo : public ffRes {
    /// @brief 获得 f2d 视频对象接口
    virtual f2dVideo *operator ->();
    virtual f2dVideo &operator *();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Json对象
////////////////////////////////////////////////////////////////////////////////
struct ffJson : public ffRes {
    /// @brief 获得 f2d Json对象
    virtual fcyJson *operator ->();
    virtual fcyJson &operator *();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Ini对象
////////////////////////////////////////////////////////////////////////////////
struct ffIni : public ffRes {
    /// @brief 获得 f2d Ini对象
    virtual fcyIni *operator ->();
    virtual fcyIni &operator *();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Xml文档对象
////////////////////////////////////////////////////////////////////////////////
struct ffXml : public ffRes {
    /// @brief 获得 f2d Xml文档对象
    virtual fcyXmlDocument *operator ->();
    virtual fcyXmlDocument &operator *();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 资源管理器
////////////////////////////////////////////////////////////////////////////////
struct ffResManager {
    /// @brief 获得单例对象
    static ffResManager &Get();

    /// @brief 启用垃圾回收的模式，当资源引用为0时也不会被销毁，直到主动调用 ffResManager::GC
    virtual void SetEnableGC(bool b);

    /// @brief 垃圾回收
    virtual void GC();
};