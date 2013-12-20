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
#include <string>

class fcyJson;
class fcyIni;
class fcyXmlDocument;

////////////////////////////////////////////////////////////////////////////////
/// @brief 资源基类
////////////////////////////////////////////////////////////////////////////////
class ffResBase {
public:
    enum Status{
        Invalid = 0,    ///< @brief 无效的
        Valid   = 1,    ///< @brief 有效的
    };

    /// @brief 增加接口的引用计数
    virtual void AddRef() = 0;

    /// @brief 减少接口的引用计数
    virtual void Release() = 0;

    /// @brief 获取当前资源类型
    virtual fcStrW GetType() const = 0;

    /// @brief 获取当前资源状态
    Status GetStatus() const { return m_status; }

    /// @brief 获取当前资源路径
    fcStrW GetPath() const { return m_path.c_str(); }

protected:
    Status m_status;
    std::wstring m_path;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 贴图精灵
////////////////////////////////////////////////////////////////////////////////
struct ffSprite : public ffResBase {
    static fcStrW TypeName;
    static ffSprite *Create(fcStrW resPath);

    /// @brief 获得 f2d 贴图精灵接口
    virtual f2dSprite *operator ->() = 0;
    virtual f2dSprite &operator *() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 音频对象
////////////////////////////////////////////////////////////////////////////////
struct ffSound : public ffResBase {
    static fcStrW TypeName;

    /// @brief 获得 f2d 音频对象接口
    virtual f2dSoundBuffer *operator ->() = 0;
    virtual f2dSoundBuffer &operator *() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 视频对象
////////////////////////////////////////////////////////////////////////////////
struct ffVideo : public ffResBase {
    static fcStrW TypeName;

    /// @brief 获得 f2d 视频对象接口
    virtual f2dVideo *operator ->() = 0;
    virtual f2dVideo &operator *() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Json对象
////////////////////////////////////////////////////////////////////////////////
struct ffJson : public ffResBase {
    static fcStrW TypeName;

    /// @brief 获得 f2d Json对象
    virtual fcyJson *operator ->() = 0;
    virtual fcyJson &operator *() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Ini对象
////////////////////////////////////////////////////////////////////////////////
struct ffIni : public ffResBase {
    static fcStrW TypeName;

    /// @brief 获得 f2d Ini对象
    virtual fcyIni *operator ->() = 0;
    virtual fcyIni &operator *() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Xml文档对象
////////////////////////////////////////////////////////////////////////////////
struct ffXml : public ffResBase {
    static fcStrW TypeName;

    /// @brief 获得 f2d Xml文档对象
    virtual fcyXmlDocument *operator ->() = 0;
    virtual fcyXmlDocument &operator *() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 资源管理器
////////////////////////////////////////////////////////////////////////////////
struct ffRes {
    /// @brief 获得单例对象
    static ffRes &Get();

    virtual fBool LoadPackage(fcStrW Path, fcStrW filePath) = 0;

    virtual fBool LoadPath(fcStrW Path, fcStrW dirPath) = 0;

    virtual ffSprite *CreateSprite(fcStrW resPath) = 0;

    virtual ffSound *CreateSound(fcStrW resPath) = 0;

    virtual ffVideo *CreateVideo(fcStrW resPath) = 0;

    virtual ffJson *CreateJson(fcStrW resPath) = 0;

    virtual ffIni *CreateIni(fcStrW resPath) = 0;

    virtual ffXml *CreateXml(fcStrW resPath) = 0;
};