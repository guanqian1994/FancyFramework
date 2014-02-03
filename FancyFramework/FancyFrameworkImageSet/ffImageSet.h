////////////////////////////////////////////////////////////////////////////////
/// Copyright(c) 2014, frimin
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
///        file :   ffImageSet.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#define FF_IMAGESET_VERSION "0.1.0"
#define FF_IMAGESET_VERSION_W L"0.1.0"
#define FF_VERNUM 0x0100

#define FF_IMAGESET_VER_MAJOR 0
#define FF_IMAGESET_VER_MINOR 1
#define FF_IMAGESET_VER_REVISION 0
#define FF_IMAGESET_VER_SUBREVISION 0

#include <ffRes.h>
#include <f2dRenderer.h>

////////////////////////////////////////////////////////////////////////////////
/// @brief 贴图动画
////////////////////////////////////////////////////////////////////////////////
struct ffSpriteAnimation : public f2dSprite {
    /// @brief 获得精灵绑定的纹理
    virtual f2dTexture2D *GetTexture() = 0;

    /// @brief 设置一个新的纹理
    virtual fResult SetTexture(f2dTexture2D* pTex) = 0;

    /// @brief 返回对应纹理的矩形
    virtual const fcyRect &GetTexRect() const = 0;

    /// @brief 设置对应纹理的矩形
    virtual fResult SetTexRect(const fcyRect& rect) = 0;

    /// @brief 返回热点
    virtual const fcyVec2 &GetHotSpot() const = 0;

    /// @brief 设置热点
    virtual fResult SetHotSpot(const fcyVec2& point) = 0;

    /// @brief 返回翻转方式
    virtual F2DSPRITEFLIP GetFlipType() const = 0;

    /// @brief 设置翻转方式
    virtual fResult SetFlipType(F2DSPRITEFLIP type) = 0;

    /// @brief 返回Z值
    virtual fFloat GetZ() const = 0;

    /// @brief 设置Z值
    virtual fResult SetZ(fFloat value) = 0;

    /// @brief 返回顶点的颜色
    virtual fcyColor GetColor(fuInt index) const = 0;

    /// @brief 返回顶点的颜色
    virtual void GetColor(fcyColor* pOut) const = 0;

    /// @brief 设置所有顶点的颜色
    virtual fResult SetColor(fcyColor color) = 0;

    /// @brief 设置顶点颜色
    virtual fResult SetColor(fuInt index, fcyColor color) = 0;

    /// @brief 设置所有顶点的颜色
    virtual fResult SetColor(fcyColor* pArr) = 0;

    /// @brief 绘制精灵
    virtual fResult Draw(f2dGraphics2D* pGraph, const fcyRect& dest) = 0;

    /// @brief 绘制精灵
    virtual fResult Draw(f2dGraphics2D* pGraph, const fcyRect& dest, const fcyRect& subTex) = 0;

    /// @brief 绘制精灵
    virtual fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& center) = 0;

    /// @brief 绘制精灵
    virtual fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& center, const fcyVec2& scale) = 0;

    /// @brief 绘制精灵
    virtual fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& center, const fcyVec2& scale, const fcyRect& subTex) = 0;

    /// @brief 绘制精灵
    virtual fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& center, const fcyVec2& scale, fFloat rotation) = 0;

    /// @brief 绘制精灵
    virtual fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& center, const fcyVec2& scale, fFloat rotation, const fcyRect& subTex) = 0;

    /// @brief 更新画面
    virtual void Update(fDouble elapsedTime) = 0;

    /// @brief 返回帧对应的精灵
    virtual ffSprite* GetSprite(fuInt index) = 0;

    /// @brief 返回帧对应的时间
    virtual fInt GetFrameTime(fuInt index) const = 0;

    /// @brief 设置帧对应的精灵
    virtual fResult SetSprite(fuInt index, ffSprite *pSprite = 0);

    /// @brief 设置帧对应的时间
    virtual fResult SetFrameTime(fuInt index, fuInt time);

    /// @brief 获得动画段数量
    virtual fInt GetSectionCount() const = 0;

    /// @brief 获得指定动画段名称
    virtual fcStrW GetSectionName(fInt index) const = 0;

    /// @brief 设置当前动画段
    virtual void SetSection(fcStrW sectionName) const = 0;

    /// @brief 计算总帧数
    virtual fuInt GetFrameCount() const = 0;

    /// @brief 计算循环时间
    virtual fuInt GetLoopTime() const = 0;

    /// @brief 获得循环起点
    virtual fInt GetLoopStart() const = 0;

    /// @brief 设置循环起点
    virtual void SetLoopStart(fInt index) = 0;

    /// @brief 获得循环终点
    virtual fInt GetLoopEnd() const = 0;

    /// @brief 设置循环终点
    virtual void SetLoopEnd(fInt index) = 0;

    /// @brief 是否循环
    virtual fBool IsLoop() const = 0;

    /// @brief 设置循环
    virtual void SetLoop(fBool b) = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 贴图集
////////////////////////////////////////////////////////////////////////////////
class ffImageSet {
public:
    /// @brief 创建一个贴图集
    /// @note 子图集信息从 后戳为 "_imageset.xml" 尝试读取
    ffImageSet(fcStrW resPath);

    /// @brief 创建一个贴图集
    ffImageSet(fcStrW textureResPath, fcStrW imageSetInfoPath);

    /// @brief 从贴图集里创建贴图精灵
    ffSprite *CreateSprite(fcStrW name);

    /// @brief 从贴图集里创建贴图动画
    ffSpriteAnimation *CreateSpriteAnimation(fcStrW animationName);

    /// @brief 获得贴图数量
    fInt GetImageCount() const;

    /// @brief 获得指定索引的贴图名
    fcStrW GetImageName(fInt index) const;

    /// @brief 获得动画数量
    fInt GetAnimationCount() const;

    /// @brief 获得指定索引的动画名
    fcStrW GetAnimationName() const;

private:
    ffXmlRef m_imageInfo;
};