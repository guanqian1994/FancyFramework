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
typedef std::vector<ffLayers> ffLayerGroup;

////////////////////////////////////////////////////////////////////////////////
/// @brief ������
////////////////////////////////////////////////////////////////////////////////
class ffScene {
    friend class ffAppImpl;
public:
    ffScene();

    virtual ~ffScene();

    virtual void Release();

    /// @brief ��ǰ�����Ƿ��Ѿ�������
    bool IsCreated();

    /// @brief ��ӳ�����
    void AddLayer(ffLayer *pLayer, fInt group = 0);

    /// @brief ��ӳ����㵽ͼ�������Ⱦ˳�����ȣ�
    void AddLayerBack(ffLayer *pLayer, fInt group = 0);

    /// @brief ���һ����������
    fInt AddLayerGroup();

    /// @brief �Ƴ�������
    void RemoveLayer(ffLayer *pLayer, fInt group = 0);

    /// @brief �Ƴ���������
    /// @note �������������ֻ����һ��ʱЧ���� ffScene::ClearLayers Ч����ͬ
    void RemoveLayerGroup(fInt group = 0);

    /// @brief ���ָ����������
    void ClearLayerGroup(fInt group = 0);

    /// @brief ��������������Ⱦ������ǰ
    /// @warning ��Ⱦ������ǰ��ʾ���������ƽ���ġ����桱
    void BringLayerToFront(ffLayer *pLayer, fInt group = 0);

    /// @brief ������������Ⱦ�������
    void BringLayerToBack(ffLayer *pLayer, fInt group = 0);
    
    /// @brief ��ó���������
    fInt GetLayerCount(fInt group = 0) const;

    /// @brief ��ó�����������
    fInt GetLayerGroupCount() const;

    /// @brief ��ó���ͼ�����������
    /// @return ���ڴ����򷵻� -1
    fInt GetLayerIndex(ffLayer *pLayer, fInt group = 0) const;

    /// @brief ���������ָ��ͼ��
    ffLayer *GetLayerOfIndex(fInt index, fInt group = 0);

    /// @brief ����Ƿ�����ƶ�������
    fBool HasLayer(ffLayer *pLayer, fInt group = 0) const;

    /// @brief ִ�и���
    void DoUpdate(fDouble elapsedTime) { OnUpdate(elapsedTime); }

    /// @brief ִ����Ⱦ
    void DoRender(fDouble elapsedTime, ffGraphics *pGraph) { OnRender(elapsedTime, pGraph); }

protected:
    /// @brief ������ʱ����
    virtual void OnCreate();

    /// @brief ������ʱ����
    virtual void OnDestroy();

    /// @bridef �����㱻�Ƴ�ʱ����
    virtual void OnRemoveLayer(ffLayer *pLayer);

    /// @brief ����Ϣ��Ҫ����ʱ������
    virtual fBool OnMsg(const ffMsg &msg);

    /// @brief ����ʱ������
    virtual void OnUpdate(fDouble elapsedTime);

    /// @brief �������ʱ������
    virtual void OnRender(fDouble elapsedTime, ffGraphics *pGraph);

protected:
    /// @brief ������Ϣ
    /// @note ������д���ϲ���Ϣ���Ƚ���Ϣ���͸��˷����������Ϣû�о������������ OnMsg ������
    /// ������������û�д����򽻸���������������Ϣ��
    bool HandleMsg(const ffMsg &msg);

    /// @brief �������
    void HandleUpdate(fDouble elapsedTime);

    /// @brief ������Ⱦ
    void HandleRender(fDouble elapsedTime, ffGraphics *pGraph);

    /// @brief ���õ�ǰ�����Ѿ�����ʼ��
    void SetCreated();

private:
    fBool m_created;
    ffLayerGroup m_layerGroup;
};
