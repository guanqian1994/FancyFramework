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

////////////////////////////////////////////////////////////////////////////////
/// @brief 资源基类
////////////////////////////////////////////////////////////////////////////////
struct ffRes {
    enum Status{
        Valid,      ///< @brief 有效的
        Invalid,    ///< @brief 无效的
        Loading,    ///< @brief 正在载入
    };

    /// @brief 增加接口的引用计数
    virtual void AddRef() = 0;

    /// @brief 减少接口的引用计数
    virtual void Release() = 0;

    /// @brief 以当前资源的种类尝试加载
    virtual void Load(fcStrW path) = 0;

    /// @brief 获取当前资源状态
    virtual Status GetStatus() const = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 贴图精灵
////////////////////////////////////////////////////////////////////////////////
struct ffSprite : public ffRes {
    /// @brief 绘制
    virtual fResult Draw(f2dGraphics2D *pGraph, const fcyRect &dest) = 0;

    virtual fResult Draw(f2dGraphics2D *pGraph, const fcyRect &dest, const fcyRect &subTex) = 0;

    virtual fResult Draw(f2dGraphics2D *pGraph, const fcyVec2 &center) = 0;

    virtual fResult Draw(f2dGraphics2D *pGraph, const fcyVec2 &center, const fcyVec2 &scale) = 0;

    virtual fResult Draw(f2dGraphics2D *pGraph, const fcyVec2 &center, const fcyVec2 &scale, const fcyRect &subTex) = 0;
    
    virtual fResult Draw(f2dGraphics2D *pGraph, const fcyVec2 &center, const fcyVec2 &scale, fFloat rotation) = 0;
    
    virtual fResult Draw(f2dGraphics2D *pGraph, const fcyVec2 &center, const fcyVec2 &scale, fFloat rotation, const fcyRect &subTex) = 0;
    
    /// @brief 获得 f2d 精灵对象接口
    virtual f2dSprite *Get() = 0;
   
    /// @brief 获得热点
    virtual fcyVec2 GetHotSpot() = 0;
    
    /// @brief 获得Z值
    virtual fFloat GetZ() = 0;
    
    /// @brief 设置顶点颜色
    virtual fResult SetColor(fcyColor color) = 0;
    
    /// @brief 设置热点
    virtual void SetHotSpot(fcyVec2 point) = 0;

    /// @brief 设置Z值
    virtual void SetZ(fFloat value) = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 资源载入方式
////////////////////////////////////////////////////////////////////////////////
enum FFRESOURCELOADTYPE {
    DIRECT,     ///< @brief 直接载入
    FRAME,      ///< @brief 分帧载入
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