#pragma once

struct ffApp {
    static ffApp *Get();
    static ffApp *Create(fFloat width, fFloat height, fcStrW title = L"ffApp", fBool windowed = true, fBool vsync = false, F2DAALEVEL aa = F2DAALEVEL::F2DAALEVEL_NONE);
    static void Destroy(ffApp *pffApp);
};

struct ffDrawer {
    virtual void DrawPolygon(const fcyVec2 *pVertices, fInt vertexCount, const fcyColor &color);
    virtual void DrawSolidPolygon(const fcyVec2 *pVertices, fInt vertexCount, const fcyColor &color);
    virtual void DrawCircle(const fcyVec2 &center, fFloat radius, const fcyColor &color);
    virtual void DrawSolidCircle(const fcyVec2 &center, fFloat radius, const fcyColor &color);
    virtual void DrawSegment(const fcyVec2 &p1, const fcyVec2 &p2, const fcyColor &color);
    virtual void DrawString(fcyVec2 pos, const fcyColor &color, const char *pString, ...);
    virtual void DrawWString(fcyVec2 pos, const fcyColor &color, const wchar_t *pString);
};

struct ffColors {
    static fcyColor White;
    static fcyColor Black;
};