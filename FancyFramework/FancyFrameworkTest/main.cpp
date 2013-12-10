#include "f2d.h"
#include "ff.h"

int main() {
    ffApp *pApp = ffApp::Create(800, 600);
    ffApp::Destroy(pApp);
}