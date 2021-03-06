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

#include <map>
#include <vector>
#include <f2dRenderer.h>
#include <fcyRefObj.h>
#include "ffRes.h"
#include "ffConstants.h"
#include "ffAssert.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief 贴图动画
////////////////////////////////////////////////////////////////////////////////
class ffAnimation : public fcyRefObjImpl<ffSprite> {
public:
    struct Frame {
        fInt xPos, yPos, width, height;
    };

    ffAnimation(ffSprite *pSprite);

    ffAnimation(ffSprite *pSprite, fDouble frameRate, const fcyVec2 &hotSpotPos, const fcyVec2 &hotSpotOffset);

    virtual f2dSprite *Get()                { return m_pSprite->Get(); }

    virtual fcStrW GetType() const          { return L"ffAnimation"; };

    virtual fcStrW GetPath() const          { return ffNull::WCStr; };

    /// @brief 更新显示
    void Update(fDouble elapsedTime);

    /// @brief 添加帧
    void AddFrame(fInt xPos, fInt yPos, fInt width, fInt height);

    /// @brief 添加帧
    void AddFrame(Frame frame);

    /// @brief 设置循环
    void SetLoop(fBool b)                   { m_loop = b; }

    /// @brief 是否循环
    fBool IsLoop() const                    { return m_loop; }

    /// @brief 获得总帧数
    fuInt GetFrameNums() const              { return m_frames.size(); }

    /// @brief 设置起始帧
    void SetBeginFrame(fuInt frameIndex)    { m_beginFrame = frameIndex; }

    /// @brief 设置结束帧
    void SetEndFrame(fuInt frameIndex)      { m_endFrame = frameIndex; }

    /// @brief 设置帧率
    void SetFrameRate(fDouble rate)         { m_frameRate = rate; m_delayTime = 1.f / m_frameRate; }

    /// @brief 获得帧率
    fDouble GetFrameRate() const            { return m_frameRate; }

    /// @brief 设置热点位置
    void SetHotSpot(const fcyVec2 &pos, const fcyVec2 &offset) { m_hotSpotPos = pos; m_hotSpotOffset = offset; }

private:
    ~ffAnimation();

    fBool m_loop = true;

    fDouble m_elapseTime = 0.f;

    fDouble m_delayTime = 1.f / 23.f;

    fDouble m_frameRate = 23.f;

    fuInt m_curFrame = 0;

    fuInt m_beginFrame = 0;

    fuInt m_endFrame = 1;

    ffSprite *m_pSprite = nullptr;

    fcyVec2 m_hotSpotPos = fcyVec2(0.5f, 0.5f);

    fcyVec2 m_hotSpotOffset = fcyVec2(0.f, 0.f);

    std::vector<Frame> m_frames;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 贴图集
////////////////////////////////////////////////////////////////////////////////
class ffImageset : public fcyRefObjImpl<fcyRefObj> {
public:

    /// @brief 创建一个贴图集
    static ffImageset *Create(fcStrW resPath);

    /// @brief 创建一个贴图集
    static ffImageset *Create(fcStrW textureResPath, fcStrW imagesetInfoPath);

    /// @brief 从贴图集里创建贴图精灵
    ffSprite *CreateSprite(fcStrW name);

    /// @brief 从贴图集里创建动画
    ffAnimation *CreateAnimation(fcStrW name);

private:
    ~ffImageset();

    struct Image {
        fInt xPos, yPos, width, height;

        std::wstring name;
    };

    struct Animation {
        fDouble frameRate = 23;
        fcyVec2 hotSpotPos = fcyVec2(0.5f, 0.5f);
        fcyVec2 hotSpotOffset = fcyVec2(0.f, 0.f);

        std::vector<ffAnimation::Frame> frames;
    };

    static fBool UpdateList(ffImageset *pImageset, fcStrW resPath);

    ffImageset(fcStrW resPath);

    ffImageset(fcStrW textureResPath, fcStrW imagesetInfoPath);

    std::wstring m_textureResPath;

    Animation *m_curHandleAnimation = nullptr;

    ffXml::Ref m_imagesetDoc;

    std::map<std::wstring, Image*> m_images;

    std::map<std::wstring, Animation*> m_animationList;
};