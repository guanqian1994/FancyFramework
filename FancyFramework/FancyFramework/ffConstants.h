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
///        file :   ffApp.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <fcyMath.h>

////////////////////////////////////////////////////////////////////////////////
/// @brief 空值
/// @note 定义了一系列用于函数返回的有效的引用常量
////////////////////////////////////////////////////////////////////////////////
struct ffNull {
    static const fcyVec2 Vec2;
    static const fcyVec3 Vec3;
    static const fcyVec4 Vec4;
    static const fcyRect Rect;

    static const char *CStr;
    static const wchar_t *WCStr;
    static const std::string Str;
    static const std::wstring WStr;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 颜色集合
/// @note 预置了一些颜色值
////////////////////////////////////////////////////////////////////////////////
struct ffColors {
    static const fcyColor Black;  ///< @brief 黑色
    static const fcyColor Blue;   ///< @brief 蓝色
    static const fcyColor Brown;  ///< @brief 棕色
    static const fcyColor Gold;   ///< @brief 金黄
    static const fcyColor Gray;   ///< @brief 灰色
    static const fcyColor Green;  ///< @brief 绿色
    static const fcyColor Orange; ///< @brief 橘黄色
    static const fcyColor Pink;   ///< @brief 粉红色
    static const fcyColor Purple; ///< @brief 紫色
    static const fcyColor Red;    ///< @brief 红色
    static const fcyColor Violet; ///< @brief 紫罗兰
    static const fcyColor White;  ///< @brief 白色
    static const fcyColor Yellow; ///< @brief 黄色
};