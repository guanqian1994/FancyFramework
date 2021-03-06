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

#include <fcyRefObj.h>
#include <fcyMath.h>
#include <string>
#include <f2dRenderer.h>

class fcyJson;
class fcyIni;
class fcyXmlDocument;
struct f2dSprite;
struct f2dSoundBuffer;
struct f2dVideo;
struct f2dStream;
struct f2dFontRenderer;

////////////////////////////////////////////////////////////////////////////////
/// @brief 资源对象公共接口
////////////////////////////////////////////////////////////////////////////////
struct ffResObj : public fcyRefObj {

    /// @brief 获取当前资源类型
    virtual fcStrW GetType() const = 0;

    /// @brief 获取当前资源路径
    virtual fcStrW GetPath() const = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 资源引用模板
////////////////////////////////////////////////////////////////////////////////
template<typename T, typename SrcT> class ffResRef {
public:
    ffResRef() { m_ptr = nullptr; }

    ffResRef(T *ptr) { m_ptr = ptr; }

    ~ffResRef() { Release(); }

    fBool Valid() const { return m_ptr != nullptr; }

    T *GetPtr() { return m_ptr; }

    ffResRef &operator =(T *ptr) {
        if (m_ptr != nullptr) {
            Release();
        }
        m_ptr = ptr; 
        return *this; 
    }

    SrcT *operator ->() { return m_ptr->Get(); }

    void Release() {
        if (m_ptr != nullptr) {
            m_ptr->Release();
            m_ptr = nullptr;
        }
    }

private:
    T *m_ptr;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 贴图精灵
/// @note 资源管理器会维护同一资源路径的贴图资源，无论存在多少个加载同一路径贴图的 ffSprite
/// 对象，引用的都是同一个贴图资源实例对象。
////////////////////////////////////////////////////////////////////////////////
struct ffSprite : public ffResObj {
    typedef ffResRef<ffSprite, f2dSprite> Ref;

    static fcStrW TypeName;

    /// @brief 创建一个贴图精灵
    static ffSprite *Create(fcStrW resPath);

    /// @brief 获得 f2d 贴图精灵接口
    virtual f2dSprite *Get() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 字体资源
////////////////////////////////////////////////////////////////////////////////
struct ffFont : public ffResObj {
    typedef ffResRef<ffFont, f2dFontRenderer> Ref;

    static fcStrW TypeName;
    
    /// @brief 从文件创建字体
    static ffFont *CreateFromFile(fcStrW resPath, fuInt faceIndex, const fcyVec2 &fontSize, F2DFONTFLAG flag);

    /// @brief 从系统字体库创建字体
    static ffFont *CreateFromSystem(fcStrW faceName, fuInt faceIndex, const fcyVec2 &fontSize, F2DFONTFLAG flag);

    /// @brief 获得 f2d 字体渲染接口
    virtual f2dFontRenderer *Get() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 音频对象
/// @note 资源管理器会维护同一资源路径的音频资源。请勿将已经被加载的静态/动态音效以其他的方式再
/// 次尝试加载并播放，其效果恐怕不是你想要的。
////////////////////////////////////////////////////////////////////////////////
struct ffSound : public ffResObj {
    typedef ffResRef<ffSound, f2dSoundBuffer> Ref;

    enum Option {
        None            = 0,

        Static          = 1 << 0,   ///< @brief 静态音效
        Dynamic         = 1 << 1,   ///< @brief 动态音效

        WaveFormat      = 1 << 2,   ///< @brief wave格式
        OGGFormat       = 1 << 3,   ///< @brief ogg格式

        GlobalFocus     = 1 << 4,   ///< @brief 当窗口未被激活时依然可以播放
    };

    static fcStrW TypeName;

    /// @brief 创建音频资源
    static ffSound *Create(fcStrW resPath, fInt options);

    /// @brief 获得 f2d 音频对象接口
    virtual f2dSoundBuffer *Get() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 视频对象
////////////////////////////////////////////////////////////////////////////////
struct ffVideo : public ffResObj {
    typedef ffResRef<ffVideo, f2dVideo> Ref;

    static fcStrW TypeName;

    /// @brief 创建一个视频资源
    static ffVideo *Create(fcStrW resPath, fInt options);

    /// @brief 获得 f2d 视频对象接口
    virtual f2dVideo *Get() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Json对象
////////////////////////////////////////////////////////////////////////////////
struct ffJson : public ffResObj  {
    typedef ffResRef<ffJson, fcyJson> Ref;

    static fcStrW TypeName;

    /// @brief 创建一个 Json 对象
    static ffJson *Create(fcStrW resPath);

    /// @brief 获得 f2d Json对象
    virtual fcyJson *Get() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Ini对象
////////////////////////////////////////////////////////////////////////////////
struct ffIni : public ffResObj  {
    typedef ffResRef<ffIni, fcyIni> Ref;

    static fcStrW TypeName;

    /// @brief 创建一个 Ini 对象
    static ffIni *Create(fcStrW resPath);

    /// @brief 获得 f2d Ini对象
    virtual fcyIni *Get() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Xml文档对象
////////////////////////////////////////////////////////////////////////////////
struct ffXml : public ffResObj {
    typedef ffResRef<ffXml, fcyXmlDocument> Ref;

    static fcStrW TypeName;

    /// @brief 创建一个 Xml 对象
    static ffXml *Create(fcStrW resPath);

    /// @brief 获得 f2d Xml文档对象
    virtual fcyXmlDocument *Get() = 0;
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

    /// @brief 从字体文件加载字体
    /// @param[in]  resPath   字体文件资料路径
    /// @param[in]  faceIndex 若有多个Face，可以指定索引。0总是有效值。
    /// @param[in]  fontSize  字体大小
    /// @param[in]  flag      额外选项
    /// @return     返回字体，创建失败返回 NULL
    virtual ffFont *CreateFontFromFile(fcStrW resPath, fuInt faceIndex, const fcyVec2 &fontSize, F2DFONTFLAG flag) = 0;

    /// @brief 从系统加载字体
    /// @param[in]  faceName  字体在注册表中的名称
    /// @param[in]  faceIndex 若有多个Face，可以指定索引。0总是有效值。
    /// @param[in]  fontSize  字体大小
    /// @param[in]  flag      额外选项
    /// @return     返回字体，创建失败返回 NULL
    virtual ffFont *CreateFontFromSystem(fcStrW faceName, fuInt faceIndex, const fcyVec2 &fontSize, F2DFONTFLAG flag) = 0;

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