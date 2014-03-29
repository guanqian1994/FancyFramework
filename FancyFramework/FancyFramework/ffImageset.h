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
#include <f2dRenderer.h>
#include "ffRes.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief 贴图集
////////////////////////////////////////////////////////////////////////////////
class ffImageset {
public:
    struct Image {
        int xPos, yPos, width, height;

        std::wstring name;
    };

    /// @brief 创建一个贴图集
    static ffImageset *Create(fcStrW resPath);

    /// @brief 创建一个贴图集
    static ffImageset *Create(fcStrW textureResPath, fcStrW imagesetInfoPath);

    ~ffImageset();

    /// @brief 从贴图集里创建贴图精灵
    ffSprite *CreateSprite(fcStrW name);

private:
    static fBool UpdateList(ffImageset *pImageset, fcStrW resPath);

    ffImageset(fcStrW resPath);

    ffImageset(fcStrW textureResPath, fcStrW imagesetInfoPath);

    std::wstring m_textureResPath;

    std::map<std::wstring, Image*> m_images;
};