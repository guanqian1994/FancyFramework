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
///        file :   ffApp.cpp
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#include "ffApp.h"
#include "ffScene.h"

#include "fcyMisc\fcyStringHelper.h"
////////////////////////////////////////////////////////////////////////////////
/// @brief 消息类
////////////////////////////////////////////////////////////////////////////////
ffMsg::ffMsgParam::ffMsgParam() {
    m_param = 0L;
};

ffMsg::ffMsgParam::ffMsgParam(fuLong value) {
    m_param = value;
};

fInt ffMsg::ffMsgParam::ToInt() const {
    return static_cast<fInt>(m_param);
}

fDouble ffMsg::ffMsgParam::ToDouble() const {
    return *(fDouble*)(&m_param);
}

fCharW ffMsg::ffMsgParam::ToChar() const {
    return static_cast<fChar>(m_param);
}

fCharW ffMsg::ffMsgParam::ToCharW() const {
    return static_cast<fCharW>(m_param);
}

fcStrW ffMsg::ffMsgParam::ToStrW() const {
    return (fcStrW)m_param;
}

void *ffMsg::ffMsgParam::ToPtr() const {
    return (void*)m_param;
}

void ffMsg::ffMsgParam::Set(fuLong value) {
    m_param = value;
}

fuLong ffMsg::ffMsgParam::Get() const {
    return m_param;
}

ffMsg::ffMsg() {
    
}

ffMsg::ffMsg(const f2dMsg &msg) {
    m_type = msg.Type;
    m_param[0].Set(msg.Param1);
    m_param[1].Set(msg.Param2);
    m_param[2].Set(msg.Param3);
    m_param[3].Set(msg.Param4);
}

F2DMSGTYPE ffMsg::GetType() const {
    return m_type;
}

ffMsg::ffMsgParam &ffMsg::operator[](fInt index) {
    return m_param[index];
}

const ffMsg::ffMsgParam &ffMsg::operator[](fInt index) const {
    return m_param[index];
}


////////////////////////////////////////////////////////////////////////////////
/// @brief 应用框架事件监听
////////////////////////////////////////////////////////////////////////////////
void ffAppEventListener::OnCreate(ffApp *pApp) { 
}

void ffAppEventListener::OnDestroy(ffApp *pApp) { 
}

void ffAppEventListener::OnRemoveScene(ffScene *pScene) {
    pScene->Release();
}

fBool ffAppEventListener::OnMsg(const ffMsg &msg) { 
    return false; 
}

void ffAppEventListener::OnUpdate(fDouble elapsedTime) { 
}

void ffAppEventListener::OnRender(fDouble elapsedTime, ffGraphics *pGraph) {
}

////////////////////////////////////////////////////////////////////////////////
/// @brief 指令类
////////////////////////////////////////////////////////////////////////////////

ffCommand::ffCommand(fcStrW command) {
    Analyze(command);
    m_command = command;
}

ffCommand::~ffCommand() {

}

fcStrW ffCommand::GetName() const {
    return m_name.c_str();
}

fcStrW ffCommand::GetCommand() const {
    return m_command.c_str();
}

fcStrW ffCommand::GetParam(fcStrW str) const {
    for (auto iter = m_params.begin(); iter != m_params.end(); ++iter) {
        if (iter->first.size() == 0) {
            break;
        }
        if (iter->first == str) {
            return iter->second.c_str();
        }
    }
    return NULL;
}

fcStrW ffCommand::GetParam(fuInt index) const {
    return m_params[index].second.c_str();
}

fcStrW ffCommand::GetParamName(fuInt index) const {
    return m_params[index].first.c_str();
}

fInt ffCommand::GetParamCount() const {
    return m_params.size();
}

fInt ffCommand::GetIntParam(fcStrW str) const {
    return std::atoi(fcyStringHelper::WideCharToMultiByte(GetParam(str)).c_str());
}

fInt ffCommand::GetIntParam(fuInt index) const {
    return std::atoi(fcyStringHelper::WideCharToMultiByte(m_params[index].second).c_str());
}

fLong ffCommand::GetLongParam(fcStrW str) const {
    return std::atol(fcyStringHelper::WideCharToMultiByte(GetParam(str)).c_str());
}

fLong ffCommand::GetlongParam(fuInt index) const {
    return std::atol(fcyStringHelper::WideCharToMultiByte(m_params[index].second).c_str());
}

fBool ffCommand::GetBooleanParam(fcStrW str) const {
    if (std::wcscmp(GetParam(str), L"true") == 0) {
        return true;
    }
    return (fBool)GetLongParam(str);
}

fBool ffCommand::GetBooleanParam(fuInt index) const {
    if (std::wcscmp(m_params[index].second.c_str(), L"true") == 0) {
        return true;
    }
    return (fBool)GetlongParam(index);
}

fDouble ffCommand::GetDoubleParam(fcStrW str) const {
    return std::atof(fcyStringHelper::WideCharToMultiByte(GetParam(str)).c_str());
}

fDouble ffCommand::GetDoubleParam(fuInt index) const {
    return std::atof(fcyStringHelper::WideCharToMultiByte(m_params[index].second).c_str());
}

void ffCommand::Analyze(const std::wstring &command) {

    // 当前词计数
    fuInt wordNum = 0;

    // 当前词开始位置
    fuInt curBegin = 0;

    // 在引号中
    wchar_t inQuotationMark = L'\0';
    
    // 在词中
    fBool inWord = false;

    for (fuInt i = 0; i != command.size() + 1; ++i) {
        switch (command[i])
        {
        case L'"':
        case L'\'':
        case L' ':
        case L'\t':
        case L'\n':
        case L'\0':
            if (inWord == true) {
                // 在引号中
                if (inQuotationMark != L'\0') {
                    // 当前字符和起始引号标记相同
                    if (command[i] == inQuotationMark) {
                        inQuotationMark = L'\0';
                    } else {
                        break;
                    }
                } else {
                    // 如果不在引号中遇见 " 和 '字符，则当成普通字符
                    if (command[i] == L'"' || command[i] == L'\'') {
                        break;
                    }
                }

                if (wordNum == 0) {
                    m_name = std::wstring(command, curBegin, i - curBegin);
                    inWord = false;
                    ++wordNum;
                    break;
                }

                if (command[curBegin] == L'-') {
                    // 如果是参数名称，则直接添加
                    m_params.push_back(std::make_pair(std::wstring(command, curBegin + 1, i - curBegin - 1), std::wstring()));
                } else {
                    // 如果是参数，检查最后一个参数存储位置是否被占用，否则新建
                    if (m_params.size() && m_params.back().second.size() == 0) {
                        m_params.back().second = std::wstring(command, curBegin, i - curBegin);
                    } else {
                        m_params.push_back(std::make_pair(std::wstring(), std::wstring(command, curBegin, i - curBegin)));
                    }
                }
                inWord = false;
                ++wordNum;
            }
            else {
                if (command[i] == L'"' || command[i] == L'\'') {
                    inWord = true;
                    inQuotationMark = command[i];
                    curBegin = i + 1;
                }
            }
            break;
        default:
            if (inWord == false) {
                inWord = true;
                curBegin = i;
            }
            break;
        }
    }
}
