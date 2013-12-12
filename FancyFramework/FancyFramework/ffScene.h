////////////////////////////////////////////////////////////////////////////////
/// @file  ffScene.h
/// @brief 
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ffApp.h"

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

    /// @brief ������յ���Ϣ
    /// @note ������д���ϲ���Ϣ���Ƚ���Ϣ���͸��˷����������Ϣû�о������������ OnMsg ������
    /// ������������û�д����򽻸���������������Ϣ��
    bool HandleMsg(const f2dMsg &pMsg);

    /// @brief ��ǰ�����Ƿ��Ѿ�������
    bool IsCreated();

    /// @brief ���õ�ǰ�����Ѿ�����ʼ��
    void SetCreated();
private:
    bool m_created;
};
