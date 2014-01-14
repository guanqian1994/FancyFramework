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
///        file :   ffScene.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffScene.h"

#include "ffLayer.h"
#include "ffAssert.h"

ffScene::ffScene()
    : m_created(false) {
    ffAssert(AddLayerGroup() == 0);
}

ffScene::~ffScene() {
    
}

void ffScene::Release() {
    if (this->IsCreated()) {
        for (int i = 0; i != m_layerGroup.size(); ++i) {
            for (int j = 0; j != m_layerGroup[i].size(); ++j) {
                OnRemoveLayer(m_layerGroup[i][j]);
            }
        }
        this->OnDestroy();
    }
    delete this;
}

void ffScene::OnCreate() {
}

void ffScene::OnDestroy() {
}

void ffScene::OnRemoveLayer(ffLayer *pLayer) {
    pLayer->Release();
}

fBool ffScene::OnMsg(const ffMsg &msg) {
    return false;
}

void ffScene::OnUpdate(fDouble elapsedTime) {
}

void ffScene::OnRender(fDouble elapsedTime, ffGraphics *pGraph) {
}

bool ffScene::HandleMsg(const ffMsg &msg) {
    for (ffLayerGroup::reverse_iterator iter = m_layerGroup.rbegin(); iter != m_layerGroup.rend(); ++iter) {
        for (ffLayers::reverse_iterator subiter = iter->rbegin(); subiter != iter->rend(); ++subiter) {
            if ((*subiter)->OnMsg(msg) == true)
                return true;
        }
    }

    return this->OnMsg(msg);
}

void ffScene::HandleUpdate(fDouble elapsedTime) {
    this->OnUpdate(elapsedTime);

    for (int i = 0; i != m_layerGroup.size(); ++i) {
        for (int j = 0; j != m_layerGroup[i].size(); ++j) {
            m_layerGroup[i][j]->OnUpdate(elapsedTime);
        }
    }
}

void ffScene::HandleRender(fDouble elapsedTime, ffGraphics *pGraph) {
    this->OnRender(elapsedTime, pGraph);

    for (int i = 0; i != m_layerGroup.size(); ++i) {
        for (int j = 0; j != m_layerGroup[i].size(); ++j) {
            m_layerGroup[i][j]->OnRender(elapsedTime, pGraph);
        }
    }
}

bool ffScene::IsCreated() {
    return m_created;
}

void ffScene::SetCreated() {
    m_created = true;
}

void ffScene::AddLayer(ffLayer *pLayer, fInt group) {
    m_layerGroup[group].push_back(pLayer);
    pLayer->SetParent(this, group);
}

void ffScene::AddLayerBack(ffLayer *pLayer, fInt group) {
    m_layerGroup[group].insert(m_layerGroup[group].begin(), pLayer);
}

fInt ffScene::AddLayerGroup() {
    m_layerGroup.push_back(ffLayers());
    return m_layerGroup.size() - 1;
}

void ffScene::RemoveLayer(ffLayer *pLayer, fInt group) {
    ffLayers::iterator result = 
        std::find(m_layerGroup[group].begin(), m_layerGroup[group].end(), pLayer);

    if (result != m_layerGroup[group].end()) {
        m_layerGroup[group].erase(result);
        pLayer->SetParent(NULL, -1);
        pLayer->Release();
    }
}

void ffScene::RemoveLayerGroup(fInt group) {
    if (m_layerGroup.size() == 1) {
        this->ClearLayerGroup(0);
    } else {
        ClearLayerGroup(group);

        ffLayerGroup::iterator removePos = (m_layerGroup.begin() += group);
        m_layerGroup.erase(removePos);
    }
}

void ffScene::ClearLayerGroup(fInt group) {
    ffLayers::iterator iter = m_layerGroup[group].begin();

    for (; iter != m_layerGroup[group].end(); ++iter) {
        (*iter)->SetParent(NULL, -1);
        (*iter)->Release();
    }

    m_layerGroup[group].clear();
}

void ffScene::BringLayerToFront(ffLayer *pLayer, fInt group) {
    ffLayers::iterator result =
        std::find(m_layerGroup[group].begin(), m_layerGroup[group].end(), pLayer);

    if (result != m_layerGroup[group].end()) {
        ffLayer *pLayerTemp = *result;
        m_layerGroup[group].erase(result);
        m_layerGroup[group].insert(m_layerGroup[group].begin(), pLayerTemp);
    }
}

void ffScene::BringLayerToBack(ffLayer *pLayer, fInt group) {
    ffLayers::iterator result =
        std::find(m_layerGroup[group].begin(), m_layerGroup[group].end(), pLayer);

    if (result != m_layerGroup[group].end()) {
        ffLayer *pLayerTemp = *result;
        m_layerGroup[group].erase(result);
        m_layerGroup[group].push_back(pLayerTemp);
    }
}

fInt ffScene::GetLayerCount(fInt group) const {
    return m_layerGroup[group].size();
}

fInt ffScene::GetLayerGroupCount() const {
    return m_layerGroup.size();
}

fInt ffScene::GetLayerIndex(ffLayer *pLayer, fInt group) const {
    ffLayers::const_iterator begin = m_layerGroup[group].begin();
    ffLayers::const_iterator result =
        std::find(m_layerGroup[group].begin(), m_layerGroup[group].end(), pLayer);

    if (result == m_layerGroup[group].end())
        return -1;

    return result - begin;
}

ffLayer *ffScene::GetLayerOfIndex(fInt index, fInt group) {
    return m_layerGroup[group][index];
}

fBool ffScene::HasLayer(ffLayer *pLayer, fInt group) const {
    ffLayers::const_iterator result =
        std::find(m_layerGroup[group].begin(), m_layerGroup[group].end(), pLayer);

    return result != m_layerGroup[group].end();
}