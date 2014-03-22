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
///        file :   ffUIMsg.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <fcyMath.h>

/// @brief 鼠标按键
enum ffMouseButton {
    None = 0,
    Left = 1048576,
    Right = 2097152,
    Middle = 4194304,
};

/// @brief 事件
struct ffUIEvent { };

/// @brief 鼠标事件
struct ffUIMouseEvent : public ffUIEvent {
    ffUIMouseEvent(ffMouseButton button,
        fInt x, 
        fInt y,
        fDouble wheel) : Button(button), X(x), Y(y) , Wheel(wheel) { }
    /// @brief 按下的键
    ffMouseButton Button;
    /// @brief 按下的位置
    fInt X, Y;
    /// @brief 滚轮滚动的值
    fDouble Wheel;
};

/// @brief 键盘事件
struct ffUIKeyEvent : public ffUIEvent {
    ffUIKeyEvent(fInt key) : Key(key) { }
    /// @brief 按键的值
    fInt Key;
};

/// @brief 更新事件
struct ffUpdateEvent : public ffUIEvent {
    ffUpdateEvent(fDouble elapsedTime, const fcyRect &dest) : ElapsedTime(elapsedTime), Dest(dest), Handled(false) {}
    /// @brief 与上一帧的间隔时间
    fDouble ElapsedTime;
    /// @brief 当前可视对象所在的屏幕坐标矩形区域
    fcyRect Dest;
    /// @brief 是否已经处理
    /// @note 你总会获得一个为 true 的值， 在 ffUILayer 中 为了保证事件处理顺序的标记，请不要修改其值。
    fBool Handled;
};

/// @brief 渲染事件
struct ffRenderEvent : public ffUpdateEvent {
    ffRenderEvent(fDouble elapsedTime, const fcyRect &area, ffGraphics *pGraph_) 
        : ffUpdateEvent(elapsedTime, area), pGraph(pGraph_) { }
    /// @brief 渲染器
    ffGraphics *pGraph;
};