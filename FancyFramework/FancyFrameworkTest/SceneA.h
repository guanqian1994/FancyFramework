#pragma once

class SceneA : public ffScene {
public:
    bool OnMsg(const f2dMsg &pMsg);
    void OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph);
};