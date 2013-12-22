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
struct f2dSprite;
struct f2dSoundBuffer;
struct f2dVideo;
struct f2dStream;

////////////////////////////////////////////////////////////////////////////////
/// @brief 资源基类
////////////////////////////////////////////////////////////////////////////////
class ffResBase {
public:
    /// @brief 增加接口的引用计数
    virtual void AddRef() = 0;

    /// @brief 减少接口的引用计数
    virtual void Release() = 0;

    /// @brief 获取当前资源类型
    virtual fcStrW GetType() const = 0;

    /// @brief 获取当前资源路径
    fcStrW GetPath() const { return m_path.c_str(); }

protected:
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
    enum Option {
        None            = 0,

        Static          = 1 << 0,   ///< @brief 静态音效
        Dynamic         = 1 << 1,   ///< @brief 动态音效

        WaveFormat      = 1 << 2,   ///< @brief wave格式
        OGGFormat       = 1 << 3,   ///< @brief ogg格式

        GlobalFocus     = 1 << 4,   ///< @brief 当窗口未被激活时依然可以播放
    };

    static fcStrW TypeName;

    static ffSound *Create(fcStrW resPath, fInt options);

    /// @brief 获得 f2d 音频对象接口
    virtual f2dSoundBuffer *operator ->() = 0;

    virtual f2dSoundBuffer &operator *() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 视频对象
////////////////////////////////////////////////////////////////////////////////
struct ffVideo : public ffResBase {
    static fcStrW TypeName;

    /// @brief 创建一个贴图精灵，同 ffRes::CreateSound
    static ffVideo *Create(fcStrW resPath, fInt options);

    /// @brief 获得 f2d 视频对象接口
    virtual f2dVideo *operator ->() = 0;

    virtual f2dVideo &operator *() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Json对象
////////////////////////////////////////////////////////////////////////////////
struct ffJson : public ffResBase {
    static fcStrW TypeName;

    static ffJson *Create(fcStrW resPath);

    /// @brief 获得 f2d Json对象
    virtual fcyJson *operator ->() = 0;

    virtual fcyJson &operator *() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Ini对象
////////////////////////////////////////////////////////////////////////////////
struct ffIni : public ffResBase {
    static fcStrW TypeName;

    static ffIni *Create(fcStrW resPath);

    /// @brief 获得 f2d Ini对象
    virtual fcyIni *operator ->() = 0;

    virtual fcyIni &operator *() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Xml文档对象
////////////////////////////////////////////////////////////////////////////////
struct ffXml : public ffResBase {
    static fcStrW TypeName;

    static ffXml *Create(fcStrW resPath);

    /// @brief 获得 f2d Xml文档对象
    virtual fcyXmlDocument *operator ->() = 0;

    virtual fcyXmlDocument &operator *() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 流对象
/// @note 方便流的加载与关闭，在栈内实例化该类就可以不用管理流的关闭
////////////////////////////////////////////////////////////////////////////////
struct ffStream {
    ffStream(fcStrW resPath);

    ffStream(const std::wstring &resPath);

    ~ffStream();

    std::wstring pResPath;

    f2dStream *pStream;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 资源管理器
////////////////////////////////////////////////////////////////////////////////
struct ffRes {
    /// @brief 获得单例对象
    static ffRes &Get();

    /// @brief 获得流
    static f2dStream *GetStream(fcStrW resPath);

    /// @brief 关闭流
    /// @note 对流的操作结束后请关闭它
    static void CloseStream(fcStrW resPath);

    /// @brief 将一个资源包加载到节点中
    /// @param[in] Path        路径
    /// @param[in] PakFilePath 文件路径
    virtual fBool LoadPackage(fcStrW Path, fcStrW filePath) = 0;

    /// @brief 映射一个真实的文件夹到节点中
    /// @note      映射时会记录所有文件夹，对目录的任何操作将不会在映射后反映。
    /// @warning   真实目录节点不区分大小写
    /// @param[in] Path    路径
    /// @param[in] DirPath 文件夹路径
    virtual fBool LoadPath(fcStrW Path, fcStrW dirPath) = 0;

    /// @brief 载入一个贴图精灵资源
    /// @param[in] resPath 资源路径
    virtual ffSprite *CreateSprite(fcStrW resPath) = 0;

    /// @brief 载入一个声音
    /// @param[in] resPath 资源路径
    /// @param[in] options 创建选项，见 ffSound::Option，如果没有指定声音格式类型，则会
    /// 根据文件扩展名判断
    virtual ffSound *CreateSound(fcStrW resPath, fInt options) = 0;

    /// @brief 载入一个视频
    /// @param[in] resPath 资源路径
    /// @param[in] options 创建选项，见 F2DVIDEOFLAG
    virtual ffVideo *CreateVideo(fcStrW resPath, fInt options) = 0;

    /// @brief 载入一个 Json 对象
    virtual ffJson *CreateJson(fcStrW resPath) = 0;

    /// @brief 载入一个 Ini 对象
    virtual ffIni *CreateIni(fcStrW resPath) = 0;

    /// @brief 载入一个 Xml 对象
    virtual ffXml *CreateXml(fcStrW resPath) = 0;
};