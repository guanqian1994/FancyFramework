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
#include <regex>
#include "fcyParser\fcyPathParser.h"
#include "fcyParser\fcyXml.h"
#include "fcyMisc\fcyStringHelper.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief 贴图动画
////////////////////////////////////////////////////////////////////////////////
ffAnimation::ffAnimation(ffSprite *pSprite) 
    : m_pSprite(pSprite) {
}

ffAnimation::ffAnimation(ffSprite *pSprite, fDouble frameRate, const fcyVec2 &hotSpotPos, const fcyVec2 &hotSpotOffset)
    : m_pSprite(pSprite),
      m_frameRate(frameRate),
      m_hotSpotPos(hotSpotPos),
      m_hotSpotOffset(hotSpotOffset) {

    m_delayTime = 1.f / m_frameRate;
}

ffAnimation::~ffAnimation() {
    m_pSprite->Release();
}

void ffAnimation::Update(fDouble elapsedTime) {
    m_elapseTime += elapsedTime;

    if (m_elapseTime >= m_delayTime) {

        ++m_curFrame;

        if (m_curFrame == m_endFrame) {
            if (m_loop) {
                m_curFrame = m_beginFrame;
            } else {
                --m_curFrame;
            }
        }

        m_elapseTime = 0.f;
    }

    const Frame &frame = m_frames[m_curFrame];

    m_pSprite->Get()->SetTexRect(fcyRect(
        frame.xPos,
        frame.yPos,
        frame.xPos + frame.width,
        frame.yPos + frame.height
        ));

    m_pSprite->Get()->SetHotSpot(fcyVec2(
        frame.xPos + frame.width * m_hotSpotPos.x + m_hotSpotOffset.x,
        frame.yPos + frame.height * m_hotSpotPos.y + m_hotSpotOffset.y
        ));
}

void ffAnimation::AddFrame(fInt xPos, fInt yPos, fInt width, fInt height) {
    m_frames.push_back({ xPos, yPos, width, height });
}

void ffAnimation::AddFrame(Frame frame) {
    m_frames.push_back(frame);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief 贴图集
////////////////////////////////////////////////////////////////////////////////
fBool ffImageset::UpdateList(ffImageset *pImageset, fcStrW resPath) {
    using namespace fcyStringHelper;

    pImageset->m_imagesetDoc = ffXml::Create(resPath);

    if (pImageset->m_imagesetDoc.Valid() == false)
        return false;

    fcyXmlElement *pRoot = pImageset->m_imagesetDoc->GetRootElement();

    for (int i = 0; i != pRoot->GetNodeCount(); ++i) {
        fcyXmlElement *pElement = pRoot->GetNode(i);
        if (pElement->GetName() == L"Group") {
            pImageset->m_curHandleAnimation = new Animation;

            Animation *pAnimation = pImageset->m_curHandleAnimation;

            pAnimation->frameRate = std::atof(WideCharToMultiByte(pElement->GetAttribute(L"FrameRate")).c_str());;

            std::wregex regex(LR"(^\{(.*),(.*) (.*),(.*)\}$)");

            std::wcmatch matchResult;

            bool match = std::regex_match(pElement->GetAttribute(L"HotSpot").c_str(), matchResult, regex);

            if (match) {
                if (matchResult.size() != 5)
                    continue;

                pAnimation->hotSpotPos.x =
                    std::atof(WideCharToMultiByte(matchResult[1]).c_str());
                pAnimation->hotSpotPos.y =
                    std::atof(WideCharToMultiByte(matchResult[2]).c_str());

                pAnimation->hotSpotOffset.x =
                    std::atof(WideCharToMultiByte(matchResult[3]).c_str());
                pAnimation->hotSpotOffset.y =
                    std::atof(WideCharToMultiByte(matchResult[4]).c_str());
            }


            pImageset->m_animationList.insert(
                std::make_pair(pElement->GetAttribute(L"Name"), pAnimation));

            continue;
        }

        if (pElement->GetName() == L"Image") {
            ffImageset::Image *pImage = new ffImageset::Image;

            pImage->name = pElement->GetAttribute(L"Name");

            pImage->xPos =
                std::atoi(WideCharToMultiByte(pElement->GetAttribute(L"XPos")).c_str());
            pImage->yPos =
                std::atoi(WideCharToMultiByte(pElement->GetAttribute(L"YPos")).c_str());
            pImage->width =
                std::atoi(WideCharToMultiByte(pElement->GetAttribute(L"Width")).c_str());
            pImage->height =
                std::atoi(WideCharToMultiByte(pElement->GetAttribute(L"Height")).c_str());

            if (pImageset->m_curHandleAnimation != nullptr) {
                pImageset->m_curHandleAnimation->frames.push_back(
                { pImage->xPos, pImage->yPos, pImage->width, pImage->height });
            }

            fBool result = pImageset->m_images.insert(std::make_pair(pImage->name, pImage)).second;

            ffAssertPrint(result, "插入图片到列表失败");

            if (result == false) {
                delete pImage;
            }

            continue;
        }
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

    for (auto iter = m_animationList.begin(); iter != m_animationList.end(); ++iter) {
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

ffAnimation *ffImageset::CreateAnimation(fcStrW name) {
    auto result = m_animationList.find(name);

    if (result == m_animationList.end()) {
        return NULL;
    }

    ffSprite *pSpr = ffSprite::Create(m_textureResPath.c_str());

    if (pSpr == NULL) {
        return NULL;
    }

    Animation *animationInfo = result->second;

    ffAnimation *pAnimation = new ffAnimation(pSpr, 
        animationInfo->frameRate,
        animationInfo->hotSpotPos,
        animationInfo->hotSpotOffset);

    for (auto iter = animationInfo->frames.begin(); iter != animationInfo->frames.end(); ++iter) {
        pAnimation->AddFrame(*iter);
    }

    pAnimation->SetEndFrame(pAnimation->GetFrameNums());

    return pAnimation;
}