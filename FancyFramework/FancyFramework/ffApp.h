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
///        file :   ffApp.h
///  created by :   frimin
/// modified by :   frimin/(add your name)
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <f2d.h>
#include <mutex>

struct f2dMsg;
struct f2dEngine;
struct f2dGraphics2D;
struct f2dRenderDevice;
struct ffAction;
struct ffStream;
struct ffAppEventListener;
struct ffFont;
struct ffGraphics;
class ffInfo;
class ffScene;

////////////////////////////////////////////////////////////////////////////////
/// @brief 框架主接口
/// @note 框架的入点 :)
////////////////////////////////////////////////////////////////////////////////
struct ffApp {
    /// @brief 获得单例对象
    static ffApp &Get();

    /// @brief 启动框架
    /// @param[in] pListener    框架事件监听类，你必须提供一个有效的对象
    /// @param[in] width        程序窗口宽度
    /// @param[in] height       程序窗口高度
    /// @param[in] title        窗口标题
    /// @param[in] windowed     是否以窗口模式运行
    /// @param[in] vsync        是否开启垂直同步
    /// @param[in] aa           抗锯齿模式
    static void Run(ffAppEventListener *pListener, fFloat width, fFloat height, fcStrW title, fBool windowed = true, fBool vsync = false, F2DAALEVEL aa = F2DAALEVEL::F2DAALEVEL_NONE);

    /// @brief 获得f2d引擎对象
    virtual f2dEngine *GetEngine() = 0;

    /// @brief 获得f2d渲染设备对象
    virtual f2dRenderDevice *GetRenderDevice() = 0;

    /// @brief 获得二维图形渲染对象
    virtual ffGraphics *GetGraphics2D() = 0;

    /// @brief 获得当面屏幕尺寸
    virtual fcyVec2 GetBufferSize() = 0;

    /// @brief 重设窗口
    /// @param[in] width        程序窗口宽度
    /// @param[in] height       程序窗口高度
    /// @param[in] windowed     是否以窗口模式运行
    /// @param[in] vsync        是否开启垂直同步
    /// @param[in] aa           抗锯齿模式
    virtual void SetWindow(fFloat width, fFloat height, fBool windowed = true, fBool vsync = false, F2DAALEVEL aa = F2DAALEVEL::F2DAALEVEL_NONE) = 0;

    /// @brief 设置背景色
    /// @warning 背景色只会在调用 ffApp::ScreenClear 时有效
    virtual void SetBackgroundColor(const fcyColor &color) = 0;

    /// @brief 清除屏幕内容
    virtual void ScreenClear() = 0;

    /// @brief 添加场景
    virtual void AddScene(ffScene *pScene) = 0;

    /// @brief 获得当前在场景队列的数量
    virtual size_t GetSceneCount() const = 0;

    /// @brief 获得当前正在显示的场景
    virtual ffScene *GetCurrentScene() = 0;

    /// @brief 下一个场景
    virtual void NextScene() = 0;

    /// @brief 移除场景
    virtual void RemoveScene(ffScene *pScene) = 0;

    /// @brief 清空场景队列
    virtual void ClearScene() = 0;

    /// @brief 获得上一帧更新阶段流逝时间
    virtual fDouble GetUpdateTime() = 0;

    /// @brief 获得上一帧渲染阶段流逝时间
    virtual fDouble GetRenderTime() = 0;

    /// @brief 结束框架
    virtual void Exit() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 消息类
////////////////////////////////////////////////////////////////////////////////
class ffMsg {
public:
    class ffMsgParam {
    public:
        ffMsgParam();

        ffMsgParam(fuLong value);

        fInt ToInt() const;

        fDouble ToDouble() const;

        fCharW ToChar() const;

        fCharW ToCharW() const;

        fcStrW ToStrW() const;

        void *ToPtr() const;

        void Set(fuLong value);

        fuLong Get() const;

    private:
        fuLong m_param;
    };

    ffMsg();

    ffMsg(const f2dMsg &msg);

    F2DMSGTYPE GetType() const;

    ffMsgParam &operator[](fInt index);

    const ffMsgParam &operator[](fInt index) const;

private:
    F2DMSGTYPE m_type;
    ffMsgParam m_param[4];
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 应用框架事件监听
/// @note  通过覆写这个类来实现消息回调
////////////////////////////////////////////////////////////////////////////////
struct ffAppEventListener {
    /// @brief 被创建时调用
    virtual void OnCreate(ffApp &app);

    /// @brief 被销毁时调用
    virtual void OnDestroy(ffApp &app);

    /// @bridef 场景被移除时调用
    virtual void OnRemoveScene(ffScene *pScene);

    /// @brief 有消息需要处理时被调用
    /// @note 返回 true 则表示此消息已经被处理
    virtual fBool OnMsg(const ffMsg &msg);

    /// @brief 更新时被调用
    virtual void OnUpdate(fDouble elapsedTime);

    /// @brief 画面更新时被调用
    virtual void OnRender(fDouble elapsedTime, ffGraphics *pGraph);

    /// @brief 在渲染完场景画面后被调用
    virtual void OnLastRender(fDouble elapsedTime, ffGraphics *pGraph);
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 渲染器
////////////////////////////////////////////////////////////////////////////////
struct ffGraphics : public f2dGraphics2D {
    /// @brief 选择渲染视图
    enum View {
        Invalid,///< @brief 无效的值
        Camera, ///< @brief 相机视图
        Screen, ///< @brief 屏幕视图
    };

    /// @brief 启动渲染器并完成状态同步
    virtual fResult Begin(View viewType = Screen) = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 绘制类
/// @note  提供基本的绘制功能
/// @warning 在创建 ffApp 成功之后才能够使用
////////////////////////////////////////////////////////////////////////////////
struct ffDrawer {
    /// @brief 获得单例对象
    static ffDrawer &Get();

    /// @brief 绘制圆形
    virtual void DrawCircle(f2dGraphics2D *pGraph, const fcyVec2 &center, fFloat radius) = 0;

    /// @brief 绘制线段
    virtual void DrawLine(f2dGraphics2D *pGraph, const fcyVec2 &p1, const fcyVec2 &p2) = 0;

    /// @brief 绘制多边形
    virtual void DrawPolygon(f2dGraphics2D *pGraph, const fcyVec2 *pVertices, fInt vertexCount) = 0;

    /// @brief 绘制矩形
    virtual void DrawRectangle(f2dGraphics2D *pGraph, const fcyRect &rect) = 0;

    /// @brief 绘制实心的圆形
    virtual void DrawSolidCircle(f2dGraphics2D *pGraph, const fcyVec2 &center, fFloat radius) = 0;

    /// @brief 绘制实心的矩形
    virtual void DrawSolidRectangle(f2dGraphics2D *pGraph, const fcyRect &rect) = 0;

    /// @brief 绘制文本
    /// @warning 此处位置参数是左上角位置，f2d的 f2dFontRenderer::DrawTextW 的位置参数
    /// 为基线位置
    virtual void DrawWString(f2dGraphics2D *pGraph, fcyVec2 pos, const wchar_t *pString) = 0;

    /// @brief 设置即将要绘制内容的颜色
    virtual void SetColor(const fcyColor &color) = 0;

    /// @brief 设置即将要绘制内容的颜色
    virtual void SetPenSize(fFloat size) = 0;

    /// @brief 获得字体对象
    virtual ffFont *GetFont() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 相机状态存储结构
////////////////////////////////////////////////////////////////////////////////
struct ffCameraStatus{
    /// @brief 缩放
    fFloat scale;

    /// @brief 位置
    fcyVec2 position;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 相机接口
////////////////////////////////////////////////////////////////////////////////
struct ffCamera {
    /// @brief 获得单例对象
    static ffCamera &Get();

    /// @brief 设置相机状态
    virtual void SetStatus(const ffCameraStatus &status) = 0;

    /// @brief 设置相机缩放
    virtual void SetScale(fFloat scale) = 0;

    /// @brief 设置相机位置
    virtual void SetPosition(const fcyVec2 &pos) = 0;

    /// @brief 获得相机状态
    virtual ffCameraStatus &GetStatus() = 0;

    virtual const ffCameraStatus &GetStatus() const = 0;

    /// @brief 获得相机缩放值
    virtual fFloat &GetScale() = 0;

    virtual fFloat GetScale() const = 0;

    /// @brief 获得相机位置
    virtual const fcyVec2 &GetPosition() = 0;

    virtual const fcyVec2 &GetPosition() const = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 缓冲区
////////////////////////////////////////////////////////////////////////////////

class ffBuffer {
public:
    ffBuffer();

    ~ffBuffer();

    char *CheckBuffer(size_t needSize);

    char *GetBuffer();

    size_t GetSize();

private:
    size_t m_bufferSize;

    char *m_pBuffer;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 互斥对象
////////////////////////////////////////////////////////////////////////////////
template <class T, class MutexT = std::mutex>
struct ffMutexObj {
    ffMutexObj() { };
    ffMutexObj(const T &value) : Value(value) { }

    void lock()     { Mutex.lock(); }
    bool try_lock() { return Mutex.try_lock(); }
    void unlock()   { Mutex.unlock(); }

    T Value;
    MutexT Mutex;
};