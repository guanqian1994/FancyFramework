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
///        file :   ffAction.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////

#include <set>
#include <fcyMath.h>

////////////////////////////////////////////////////////////////////////////////
/// @brief 值调节器
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class ffModifier {
public:
    ffMonitor() : m_pValue(NULL), m_pManager(NULL) {
    }

    ～ffModifier() {
        m_pManager->Remove(this);
    }

    const T &Get() const {
        return *m_pValue;
    }

    void Set(const T &value) {
        *m_pValue = value;
    }

    void SetManager(ffMonitorManager<T> *pManager) {
        if (pManager == NULL) {
            if (m_pManager) {
                m_pManager->UnRegister(this);
            }
            m_pManager = NULL;
            m_pValue = NULL);
        }
        else {
            if (m_pManager) {
                m_pManager->UnRegister(this);
            }
            m_pManager = pManager;
            m_pManager->Register(this);
        }
    }

    void Reset(ffMonitorManager<T> *pManager, T *pValue) {
        m_pManager = pManager;
        m_pValue = pValue;
    }

private:
    T *m_pValue;
    ffMonitorManager<T> *m_pManager;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 调节器管理
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class ffMonitorManager {
public:
    ffMonitorManager(T *pValue);
    ~ffMonitorManager();

    void Register(ffMonitor<T>* pModifier);
    void UnRegister(ffMonitor<T>* pModifier);
    void Clear();
private:
    T *m_pValue;
    std::set<ffMonitor<T>*>;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 步骤接口
////////////////////////////////////////////////////////////////////////////////
struct ffStep {
    virtual void Release() = 0;

    /// @brief 执行这个步骤
    virtual fBool Do(fDouble elapsedTime, ffStep *pPrevStep) = 0;

    /// @brief 设置步骤参数
    virtual void SetParam(fLong param, fLong param2 = 0, fLong param3 = 0, fLong param4 = 0) = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 动作接口
////////////////////////////////////////////////////////////////////////////////
struct ffAction {
    virtual void Release() = 0;

    /// @brief 动作
    virtual void Do(fDouble elapsedTime) = 0;

    /// @brief 设置起始步骤参数
    virtual void SetParam(fLong param, fLong param2 = 0, fLong param3 = 0, fLong param4 = 0) = 0;

    /// @brief 获得指定索引的结果
    virtual fFloat GetResult(fuInt index) const = 0;

    /// @brief 以浮点结果解释返回值
    virtual fFloat GetFloatResult() const = 0;

    /// @brief 以双精度浮点结果解释返回值
    virtual fDouble GetDoubleResult() const = 0;

    /// @brief 以整数结果解释返回值
    virtual fInt GetIntResult() const = 0;

    /// @brief 以二维向量结果解释返回值
    virtual fcyVec2 GetVec2Result() const = 0;

    /// @brief 以布尔结果解释返回值
    virtual fBool GetBoolResult() const = 0;

    /// @brief 添加步骤
    virtual fInt *AddStep(ffStep *pStep) = 0;

    /// @brief 获得指定步骤
    virtual ffStep *GetStep(fInt index) = 0;

    /// @brief 获得步骤数量
    virtual fuInt *GetStepCount(ffStep *pStep) = 0;
};