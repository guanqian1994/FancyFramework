#pragma once

struct f2dMsg;
struct f2dEngine;
struct f2dGraphics2D;
struct f2dRenderDevice;
struct ffAppEventListener;

////////////////////////////////////////////////////////////////////////////////
/// @brief �������
////////////////////////////////////////////////////////////////////////////////
struct ffApp {
    static ffApp &Get();
    static ffApp *Create(ffAppEventListener *pListener, fFloat width, fFloat height, fcStrW title = L"ffApp", fBool windowed = true, fBool vsync = false, F2DAALEVEL aa = F2DAALEVEL::F2DAALEVEL_NONE);

    virtual f2dEngine *GetEngine() = 0;
    virtual f2dRenderDevice *GetRenderDevice() = 0;
    virtual f2dGraphics2D *GetRenderGraphics2D() = 0;
    virtual fcyVec2 GetScreenSize() = 0;

    virtual void SetBackgroundColor(const fcyColor &color) = 0;

    virtual void Run() = 0;
    virtual void ScreenClear() = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Ӧ�ÿ��ʱ�����
/// @note  ͨ����д�������ʵ����Ϣ�ص�
////////////////////////////////////////////////////////////////////////////////
struct ffAppEventListener {
    virtual void OnCreate(ffApp *pApp);
    virtual void OnDestroy(ffApp *pApp);
    virtual bool OnMsg(const f2dMsg *pMsg);
    virtual void OnUpdate(fDouble elapsedTime);
    virtual void OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph);
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ������
/// @note  �ṩ��ݵ�API�Թ������Ļ��ƹ��ܣ��� ffApp �������ɹ��� ffDrawer Ҳ�ᱻ����
////////////////////////////////////////////////////////////////////////////////
struct ffDrawer {
    static ffDrawer &Get();
    virtual void DrawCircle(const fcyVec2 &center, fFloat radius) = 0;
    virtual void DrawLine(const fcyVec2 &p1, const fcyVec2 &p2) = 0;
    virtual void DrawPolygon(const fcyVec2 *pVertices, fInt vertexCount) = 0;
    virtual void DrawRectangle(const fcyRect &rect) = 0;
    virtual void DrawSolidCircle(const fcyVec2 &center, fFloat radius) = 0;
    virtual void DrawSolidRectangle(const fcyRect &rect) = 0;
    virtual void DrawWString(fcyVec2 pos, const wchar_t *pString) = 0;
    virtual void SetColor(const fcyColor &color) = 0;
};

struct ffColors {
    static fcyColor Black;
    static fcyColor Blue;
    static fcyColor Brown;
    static fcyColor Gold;
    static fcyColor Gray;
    static fcyColor Green;
    static fcyColor Orange;
    static fcyColor Pink;
    static fcyColor Purple;
    static fcyColor Red;
    static fcyColor Violet;
    static fcyColor White;
    static fcyColor Yellow; 
};