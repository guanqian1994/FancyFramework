#include <windows.h>
#include <iostream>
#include "Profile.h"
#include <fstream>
int main() {
    //std::fstream outfile("stud.txt", std::ios::out);
    Profile profile;
    profile.Begin();
#ifdef PROFILE_USE_WCHAR
    {
        PROFILE(L"update");
        {
            PROFILE(L"world");
            { PROFILE(L"obj01"); Sleep(10); }
            { PROFILE(L"obj02"); Sleep(10); }
            { PROFILE(L"obj03"); Sleep(10); }
            { PROFILE(L"obj04"); Sleep(10); }
        }
    }
    {
        PROFILE(L"render");
        {
            PROFILE(L"world");
            { PROFILE(L"obj01"); Sleep(20); }
            { PROFILE(L"obj02"); Sleep(20); }
            { PROFILE(L"obj03"); Sleep(20); }
            { PROFILE(L"obj04"); Sleep(20); }
        }
    }
    profile.End();
    std::wcout<<profile.GetReportStr()<<std::endl;
#else
    {
        PROFILE("update");
        {
            PROFILE("world");
            { PROFILE("obj01"); Sleep(10); }
            { PROFILE("obj02"); Sleep(10); }
            { PROFILE("obj03"); Sleep(10); }
            { PROFILE("obj04"); Sleep(10); }
        }
    }
    {
        PROFILE("render");
        {
            PROFILE("world");
            { PROFILE("obj01"); Sleep(20); }
            { PROFILE("obj02"); Sleep(20); }
            { PROFILE("obj03"); Sleep(20); }
            { PROFILE("obj04"); Sleep(20); }
        }
    }
    profile.End();
    std::cout<<profile.GetReportStr()<<std::endl;
#endif
    system("pause");
    return 0;
}