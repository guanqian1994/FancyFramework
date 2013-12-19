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
///        file :   ffScene.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include "ffApp.h"

class ffLayer;
typedef std::vector<ffLayer*> ffLayers;

////////////////////////////////////////////////////////////////////////////////
/// @brief ������
////////////////////////////////////////////////////////////////////////////////
class ffScene {
public:
    ffScene();
    ~ffScene();

    /// @brief ������ʱ����
    virtual void OnCreate();

    /// @brief ������ʱ����
    virtual void OnDestroy();

    /// @brief ����Ϣ��Ҫ����ʱ������
    virtual bool OnMsg(const f2dMsg &pMsg);

    /// @brief ����ʱ������
    virtual void OnUpdate(fDouble elapsedTime);

    /// @brief �������ʱ������
    virtual void OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph);

    /// @brief ������Ϣ
    /// @note ������д���ϲ���Ϣ���Ƚ���Ϣ���͸��˷����������Ϣû�о������������ OnMsg ������
    /// ������������û�д����򽻸���������������Ϣ��
    bool HandleMsg(const f2dMsg &pMsg);

    /// @brief �������
    bool HandleUpdate(fDouble elapsedTime);

    /// @brief ������Ⱦ
    bool HandleRender(fDouble elapsedTime, f2dGraphics2D *pGraph);

    /// @brief ��ǰ�����Ƿ��Ѿ�������
    bool IsCreated();

    /// @brief ���õ�ǰ�����Ѿ�����ʼ��
    void SetCreated();

    /// @brief ��ӳ�����
    void AddLayer(ffLayer *pLayer);

    /// @brief �Ƴ�������
    void RemoveLayer(ffLayer *pLayer);

    /// @brief ������г�����
    void ClearLayers();

    /// @brief ��������������ǰ
    void BringLayerToFront(ffLayer *pLayer);

    /// @brief ���������������
    void BringLayerToBack(ffLayer *pLayer);

    /// @brief ����Ƿ�����ƶ�������
    fBool HasLayer(ffLayer *pLayer);

protected:

private:
    fBool m_created;
    ffLayers m_layers
};
