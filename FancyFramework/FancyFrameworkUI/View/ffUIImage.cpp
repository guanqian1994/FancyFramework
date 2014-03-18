////////////////////////////////////////////////
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
///        file :   ffUIImage.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffUIImage.h"

ffUIImage *ffUIImage::Create(ffUIView *pParent, ffPoint local, fcStrW imageResPath) {
    ffSprite *pSprite = ffSprite::Create(imageResPath);

    return Create(pParent, local, pSprite);
}

ffUIImage *ffUIImage::Create(ffUIView *pParent, ffPoint local, ffSprite *pSprite) {
    if (pParent) {
        if (pSprite == NULL) {
            return NULL;
        }
        ffUIImage *pImage = new ffUIImage(pParent, pSprite);

        pImage->SetLocation(local);
        pImage->SetSize(fcyVec2(
            pSprite->Get()->GetTexRect().GetWidth(), 
            pSprite->Get()->GetTexRect().GetHeight()));

        return pImage;
    }
    return NULL;
}

void ffUIImage::SetImage(ffSprite *pSprite) {
    m_image = pSprite;
}

ffSprite *ffUIImage::GetImage() {
    return m_image.GetPtr();
}

fBool ffUIImage::OnRender(ffRenderEvent *pEvent) {
    OnRenderOriginal(pEvent);
    Render.Do(this, pEvent);
    return true;
}

void ffUIImage::OnRenderOriginal(ffRenderEvent *pEvent) {
    if (m_image.Valid())
        m_image->Draw(pEvent->pGraph, pEvent->Dest);
}

ffUIImage::ffUIImage(ffUIView *pParent, ffSprite *pSprite) : ffUIView(pParent), m_image(pSprite) {

}