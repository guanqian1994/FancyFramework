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
///        file :   ffImageSet.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////

#include "ffImageset.h"
#include "fcyParser\fcyPathParser.h"
#include "fcyParser\fcyXml.h"
#include "fcyMisc\fcyStringHelper.h"


fBool ffImageset::UpdateList(ffImageset *pImageset, fcStrW resPath) {
    using namespace fcyStringHelper;

    ffXml::Ref imageset;

    imageset = ffXml::Create(resPath);

    if (imageset.Valid() == false)
        return false;

    fcyXmlElementList list = imageset->GetRootElement()->GetNodeByName(L"Image");

    for (int i = 0; i != list.GetCount(); ++i) {
        ffImageset::Image *pImage = new ffImageset::Image;

        pImage->name = list[i]->GetAttribute(L"Name");
        pImage->xPos =
            std::atoi(WideCharToMultiByte(list[i]->GetAttribute(L"XPos")).c_str());
        pImage->yPos =
            std::atoi(WideCharToMultiByte(list[i]->GetAttribute(L"YPos")).c_str());
        pImage->width =
            std::atoi(WideCharToMultiByte(list[i]->GetAttribute(L"Width")).c_str());
        pImage->height =
            std::atoi(WideCharToMultiByte(list[i]->GetAttribute(L"Height")).c_str());

        pImageset->m_images.insert(std::make_pair(pImage->name, pImage));
    }

    return true;
}


ffImageset *ffImageset::Create(fcStrW resPath) {
    ffImageset *pImageset = new ffImageset(resPath);

    if (UpdateList(pImageset, resPath)) {
        return pImageset;
    }

    delete pImageset;

    return nullptr;
}

ffImageset *ffImageset::Create(fcStrW textureResPath, fcStrW imagesetInfoPath) {
    ffImageset *pImageset = new ffImageset(textureResPath, imagesetInfoPath);

    if (UpdateList(pImageset, imagesetInfoPath)) {
        return pImageset;
    }

    delete pImageset;

    return nullptr;
}

ffImageset::ffImageset(fcStrW resPath) {
    using namespace fcyPathParser;
    m_textureResPath =
        GetPath(resPath) + GetFileNameWithoutExt(resPath) + L".png";
}

ffImageset::ffImageset(fcStrW textureResPath, fcStrW imagesetInfoPath) {
    m_textureResPath = textureResPath;
}

ffImageset::~ffImageset() {
    for (auto iter = m_images.begin(); iter != m_images.end(); ++iter) {
        delete iter->second;
    }
}

ffSprite *ffImageset::CreateSprite(fcStrW name) {
    auto result = m_images.find(name);

    if (result == m_images.end()) {
        return NULL;
    }

    ffSprite *pSpr = ffSprite::Create(m_textureResPath.c_str());

    if (pSpr == NULL) {
        return NULL;
    }

    Image *pImage = result->second;

    pSpr->Get()->SetTexRect(fcyRect(
        pImage->xPos, 
        pImage->yPos,
        pImage->xPos + pImage->width,
        pImage->yPos + pImage->height
        ));

    pSpr->Get()->SetHotSpot(fcyVec2(
        pImage->xPos + pImage->width / 2,
        pImage->yPos + pImage->height / 2
        ));

    return pSpr;
}
