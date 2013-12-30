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

#include <map>
#include <f2d.h>

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
/// @brief 框架主类
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
    virtual fcyVec2 GetWindowSize() = 0;

    /// @brief 获得缓冲区
    /// @note 默认大小 4096B
    /// @warning 使用缓冲区时获得的结果请立即使用
    virtual void *GetBuffer() = 0;

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
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 应用框架事件监听
/// @note  通过覆写这个类来实现消息回调
////////////////////////////////////////////////////////////////////////////////
struct ffAppEventListener {
    /// @brief 被创建时调用
    virtual void OnCreate(ffApp *pApp);

    /// @brief 被销毁时调用
    virtual void OnDestroy(ffApp *pApp);

    /// @bridef 场景被移除时调用
    virtual void OnRemoveScene(ffScene *pScene);

    /// @brief 有消息需要处理时被调用
    /// @note 返回 true 则表示此消息已经被处理
    virtual fBool OnMsg(const f2dMsg &pMsg);

    /// @brief 更新时被调用
    virtual void OnUpdate(fDouble elapsedTime);

    /// @brief 画面更新时被调用
    virtual void OnRender(fDouble elapsedTime, ffGraphics *pGraph);
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

    /// @brief 设置相机缩放动作
    virtual void SetScaleAction(ffAction *pAction) = 0;

    /// @brief 设置相机位置动作
    virtual void SetPositionAction(ffAction *pAction) = 0;

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
/// @brief 命令输入
/// @note 使用索引来获得类似 command param1 param2 param3...  的值
/// 使用名称来获得类似 command -param1 value1 -param2 value2... 的值，你也可以
/// 指定索引 0 来获得 value1 的值
////////////////////////////////////////////////////////////////////////////////
class ffCommandInput {
public:
    ffCommandInput(fcStrW command);

    ~ffCommandInput();

    /// @brief 获得命令名称
    fcStrW GetCommand(fcStrW str) const;

    /// @brief 获得指定名称的参数
    fcStrW GetParam(fcStrW str) const;

    /// @brief 获得指定位置的参数
    fcStrW GetParam(fuInt index) const;

    /// @brief 尝试以整数类型来获得指定名称的参数
    fBool GetIntParam(fcStrW str, fInt *pOut) const;

    /// @brief 尝试以整数类型来获得指定索引的参数
    fBool GetIntParam(fuInt index, fInt *pOut) const;

    /// @brief 尝试以布尔类型来获得指定名称的参数
    fBool GetBooleanParam(fcStrW str, fBool *pOut) const;

    /// @brief 尝试以布尔类型来获得指定索引的参数
    fBool GetBooleanParam(fuInt index, fBool *pOut) const;

    /// @brief 尝试以浮点类型来获得指定名称的参数
    fBool GetFloatParam(fcStrW str, fFloat *pOut) const;

    /// @brief 尝试以浮点类型来获得指定索引的参数
    fBool GetFloatParam(fuInt index, fFloat *pOut) const;

private:
    std::wstring m_command;

    /// <paramName, paramValue>
    std::map<std::wstring, std::wstring> m_params;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 监视接口
/// @note 这个类用于注册需要监视的对象用来辅助调试它们，且是一个资源监视器，该类是控制台系统的基础
/////////////////////////////////////////////////////////// /////////////////////
struct ffMonitor {
    /// @brief 被监视的对象类型
    enum ObjectType {
        System,     ///< @brief 系统对象，可以以固定名称来接收输入内容
        Object,     ///< @brief 普通对象，可以以指针名称来接受输入内容
        Resource,   ///< @brief 资源对象，不可以接受任何输入内容，只是用于记录计数统计
    };

    /// @brief 获得单例对象
    static ffMonitor &Get();

    /// @brief 注册一个对象
    virtual void Register(ffInfo *ptr, ObjectType type) = 0;

    /// @brief 注销一个对象
    virtual void UnRegister(ffInfo *ptr) = 0;

    /// @brief 设置报告文件
    virtual void SetReportFile(fcStrW resPath) = 0;

    /// @brief 设置报告文件
    virtual fcStrW SendCommand(fcStrW str) = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 对象信息
/// @note 继承此类给予对象提供报告信息的功能
////////////////////////////////////////////////////////////////////////////////
class ffInfo {
public:
    ffInfo(ffMonitor::ObjectType type)                      { ffMonitor::Get().Register(this, type); }

    virtual ~ffInfo()                                       { ffMonitor::Get().UnRegister(this); }

    /// @brief 获得当前对象用于打印输出的提示信息
    virtual fcStrW GetInfo() const                          { return NULL; };

    /// @brief 获得当前对象用于在监视接口索引的名称
    virtual fcStrW GetInfoName() const                      { return NULL; };

    /// @brief 处理收到的指令
    virtual fcStrW OnCommand(const ffCommandInput &input)   { return NULL; };
};

