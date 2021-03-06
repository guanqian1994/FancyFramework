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
///        file :   ffUIProperty.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <mutex>

namespace ffUIProperty {
    ////////////////////////////////////////////////////////////////////////////////
    /// @brief 值属性访问接口
    ////////////////////////////////////////////////////////////////////////////////
    template<typename T> class Value {
    public:
        typedef std::function<void(const T&)> Seter;
        typedef std::function<const T&()> Geter;

        Value(Seter seter, Geter geter)
            : m_seter(seter), m_geter(geter) {
        
        }

        void Set(const T &param) {
            std::lock_guard<std::recursive_mutex> lock(this->m_mutex);
            m_seter(param);
        }

        const T& Get() {
            std::lock_guard<std::recursive_mutex> lock(this->m_mutex);
            return m_geter();
        }

        /// 非线程安全
        const T& ConstGet() const {
            return m_geter();
        }

        const T &operator =(const T& p) {
            Set(p);
            return p;
        }

        const T &operator ()() {
            return Get();
        }

    private:
        Geter m_geter;
        Seter m_seter;
        std::recursive_mutex m_mutex;
    };

    ////////////////////////////////////////////////////////////////////////////////
    /// @brief 指针属性访问接口
    ////////////////////////////////////////////////////////////////////////////////
    template<typename T> class Ptr {
    public:
        typedef std::function<void(T*)> Seter;
        typedef std::function<T*()> Geter;

        Ptr(Seter seter, Geter geter)
            : m_seter(seter), m_geter(geter) {

        }

        void Set(T *param) {
            std::lock_guard<std::recursive_mutex> lock(this->m_mutex);
            m_seter(param);
        }

        T *Get() {
            std::lock_guard<std::recursive_mutex> lock(this->m_mutex);
            return m_geter();
        }

        /// 非线程安全
        T *ConstGet() const {
            return m_geter();
        }

        T* operator =(T* ptr) {
            Set(ptr);
            return ptr;
        }

        T* operator ()() {
            return Get();
        }

    private:
        Geter m_geter;
        Seter m_seter;
        std::recursive_mutex m_mutex;
    };
}