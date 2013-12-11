////////////////////////////////////////////////////////////////////////////////
/// @file  ffApp.h
/// @brief 声明f2D的引擎的基本接口
////////////////////////////////////////////////////////////////////////////////
#pragma once

struct f2dMsg;
struct f2dEngine;
struct f2dGraphics2D;
struct f2dRenderDevice;
struct ffAppEventListener;

////////////////////////////////////////////////////////////////////////////////
/// @brief 框架主类
/// @note 框架的入点 :)
////////////////////////////////////////////////////////////////////////////////
struct ffApp {
    /// @brief 获得单例对象
    static ffApp &Get();

    /// @brief 创建框架
    /// @param[in] pListener    框架事件监听类，你必须提供一个有效的对象
    /// @param[in] width        程序窗口宽度
    /// @param[in] height       程序窗口高度
    /// @param[in] title        窗口标题
    /// @param[in] windowed     是否以窗口模式运行
    /// @param[in] vsync        是否开启垂直同步
    /// @param[in] aa           抗锯齿模式
    /// @result    创建失败返回NULL
    static ffApp *Create(ffAppEventListener *pListener, fFloat width, fFloat height, fcStrW title = L"ffApp", fBool windowed = true, fBool vsync = false, F2DAALEVEL aa = F2DAALEVEL::F2DAALEVEL_NONE);
    
    /// @brief 获得f2d引擎对象
    virtual f2dEngine *GetEngine() = 0;

    /// @brief 获得f2d渲染设备对象
    virtual f2dRenderDevice *GetRenderDevice() = 0;

    /// @brief 获得f2d二维图形渲染对象
    virtual f2dGraphics2D *GetRenderGraphics2D() = 0;

    /// @brief 获得当面屏幕尺寸
    virtual fcyVec2 GetScreenSize() = 0;

    /// @brief 设置背景色
    /// @warning 背景色只会在调用 ffApp::ScreenClear 时有效
    virtual void SetBackgroundColor(const fcyColor &color) = 0;

    /// @brief 启动框架
    virtual void Run() = 0;

    /// @brief 清除屏幕内容
    virtual void ScreenClear() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 应用框架时间监听
/// @note  通过覆写这个类来实现消息回调
////////////////////////////////////////////////////////////////////////////////
struct ffAppEventListener {
    virtual void OnCreate(ffApp *pApp);
    virtual void OnDestroy(ffApp *pApp);
    virtual bool OnMsg(const f2dMsg *pMsg);
    virtual void OnUpdate(fDouble elapsedTime);
    virtual void OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph);
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 绘制类
/// @note  提供便捷的API以供基本的绘制功能
/// @warning 在创建 ffApp 成功之后才能够使用
////////////////////////////////////////////////////////////////////////////////
struct ffDrawer {
    /// @brief 获得单例对象
    static ffDrawer &Get();

    /// @brief 绘制圆形
    virtual void DrawCircle(const fcyVec2 &center, fFloat radius) = 0;

    /// @brief 绘制线段
    virtual void DrawLine(const fcyVec2 &p1, const fcyVec2 &p2) = 0;

    /// @brief 绘制多边形
    virtual void DrawPolygon(const fcyVec2 *pVertices, fInt vertexCount) = 0;

    /// @brief 绘制矩形
    virtual void DrawRectangle(const fcyRect &rect) = 0;

    /// @brief 绘制实心的圆形
    virtual void DrawSolidCircle(const fcyVec2 &center, fFloat radius) = 0;

    /// @brief 绘制实心的矩形
    virtual void DrawSolidRectangle(const fcyRect &rect) = 0;

    /// @brief 绘制文本
    virtual void DrawWString(fcyVec2 pos, const wchar_t *pString) = 0;

    /// @brief 设置即将要绘制内容的颜色
    virtual void SetColor(const fcyColor &color) = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 颜色集合
/// @note  预置了一些颜色值
////////////////////////////////////////////////////////////////////////////////
struct ffColors {
    static fcyColor Black;  ///< @brief 黑色
    static fcyColor Blue;   ///< @brief 蓝色
    static fcyColor Brown;  ///< @brief 棕色
    static fcyColor Gold;   ///< @brief 金黄
    static fcyColor Gray;   ///< @brief 灰色
    static fcyColor Green;  ///< @brief 绿色
    static fcyColor Orange; ///< @brief 橘黄色
    static fcyColor Pink;   ///< @brief 粉红色
    static fcyColor Purple; ///< @brief 紫色
    static fcyColor Red;    ///< @brief 红色
    static fcyColor Violet; ///< @brief 紫罗兰
    static fcyColor White;  ///< @brief 白色
    static fcyColor Yellow; ///< @brief 黄色
};