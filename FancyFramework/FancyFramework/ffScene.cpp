
#include "ffScene.h"


ffScene::ffScene()
    : m_created(false) {
}

ffScene::~ffScene() {
    if (IsCreated())
        OnDestroy();
}

void ffScene::OnCreate() {
}

void ffScene::OnDestroy() {
}

bool ffScene::OnMsg(const f2dMsg &pMsg) {
    return false;
}

void ffScene::OnUpdate(fDouble elapsedTime) {
}

void ffScene::OnRender(fDouble elapsedTime, f2dGraphics2D *pGraph) {
}

bool ffScene::HandleMsg(const f2dMsg &pMsg) {
    return this->OnMsg(pMsg);
}

bool ffScene::IsCreated() {
    return m_created;
}

void ffScene::SetCreated() {
    m_created = true;
}