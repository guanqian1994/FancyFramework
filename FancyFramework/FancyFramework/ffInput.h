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
///        file :   ffInput.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <fcyMath.h>

////////////////////////////////////////////////////////////////////////////////
/// @brief 鼠标操作接口
/// @note 获取鼠标状态
////////////////////////////////////////////////////////////////////////////////
struct ffMouse {
    enum Mode {
        Enable,
        Disable,
    };

    /// @brief 获得单例对象
    static ffMouse &Get();

    /// @brief 获得当前鼠标的位置
    virtual const fcyVec2 &GetPos() const = 0;

    /// @brief 获得当前灵敏度
    virtual fFloat GetSensitivity() const = 0;

    /// @brief 是否已经启用限制鼠标
    virtual fBool IsLimit() const = 0;

    /// @brief 左键是否按下
    virtual fBool IsLeftDown() = 0;

    /// @brief 右键是否按下
    virtual fBool IsRightDown() = 0;

    /// @brief 滚轮是否按下
    virtual fBool IsMiddleDown() = 0;

    /// @brief 限制鼠标
    /// @node 将系统光标鼠标锁定在窗体区域的正中心，并且产生一个虚拟的鼠标位置。引擎发送
    /// F2DMSG_WINDOW_ONMOUSEMOVE 时都会接收消息并且时将虚拟鼠标位置重写到这个消息中
    /// @warning 重写消息的操作会在调用所有消息回调之前执行。启用这个功能并不会隐藏鼠标
    /// @param[in] mode         设置模式
    /// @param[in] sensitivity  灵敏度 (这个值必须大于0，否则设置失败，所以在你不需要重新设
    /// 置它时你可以传递一个非正数)
    virtual void Limit(Mode mode, fFloat sensitivity = -1.f) = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 键盘操作接口
/// @note 获取键盘状态
////////////////////////////////////////////////////////////////////////////////
struct ffKeyboard {
    /// @brief 获得单例对象
    static ffKeyboard &Get();

    /// @brief 判断按键是否按下
    virtual fBool IsKeyDown(F2DINPUTKEYCODE KeyCode) = 0; 
};