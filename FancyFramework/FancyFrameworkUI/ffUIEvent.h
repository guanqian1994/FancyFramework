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

/// @brief ��갴��
enum ffMouseButton {
    None = 0,
    Left = 1048576,
    Right = 2097152,
    Middle = 4194304,
};

/// @brief �¼�
struct ffUIEvent { };

/// @brief ����¼�
struct ffUIMouseEvent : public ffUIEvent {
    ffUIMouseEvent(ffMouseButton button,
        fInt x, 
        fInt y,
        fDouble wheel) : Button(button), X(x), Y(y) , Wheel(wheel) { }
    /// @brief ���µļ�
    ffMouseButton Button;
    /// @brief ���µ�λ��
    fInt X, Y;
    /// @brief ���ֹ�����ֵ
    fDouble Wheel;
};

/// @brief �����¼�
struct ffUIKeyEvent : public ffUIEvent {
    ffUIKeyEvent(fInt key) : Key(key) { }
    /// @brief ������ֵ
    fInt Key;
};

/// @brief �����¼�
struct ffUpdateEvent : public ffUIEvent {
    ffUpdateEvent(fDouble elapsedTime, const fcyRect &dest) : ElapsedTime(elapsedTime), Dest(dest), Handled(false) {}
    /// @brief ����һ֡�ļ��ʱ��
    fDouble ElapsedTime;
    /// @brief ��ǰ���Ӷ������ڵ���Ļ�����������
    fcyRect Dest;
    /// @brief �Ƿ��Ѿ�����
    /// @note ���ܻ���һ��Ϊ true ��ֵ�� �� ffUILayer �� Ϊ�˱�֤�¼�����˳��ı�ǣ��벻Ҫ�޸���ֵ��
    fBool Handled;
};

/// @brief ��Ⱦ�¼�
struct ffRenderEvent : public ffUpdateEvent {
    ffRenderEvent(fDouble elapsedTime, const fcyRect &area, ffGraphics *pGraph_) 
        : ffUpdateEvent(elapsedTime, area), pGraph(pGraph_) { }
    /// @brief ��Ⱦ��
    ffGraphics *pGraph;
};