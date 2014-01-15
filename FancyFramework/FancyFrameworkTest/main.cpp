#define _CRT_NON_CONFORMING_SWPRINTFS

#include <iostream>
#include "f2d.h"
#include "ff.h"

void PrintCommand(const ffCommand &command) {
    std::wcout << L"Src:("<< command.GetCommand() <<")"<< std::endl;
    std::wcout << L"Name:(" << command.GetName() << ")" << std::endl;
    for (int i = 0; i != command.GetParamCount(); ++i) {
        std::wcout << L"(" << command.GetParamName(i) << L") - (" << command.GetParam(i) << L")" << std::endl;
    }

    std::wcout << std::endl;
}

int main() {
    PrintCommand(L"command -name1 pa'ram1 -name2 'this is param2!'");
        
    PrintCommand(L"c -a 123\n-b aa");

    PrintCommand(L"x x -x");

    std::wcout << ffCommand(L"xxxxxxx -xx 3.14").GetDoubleParam(L"xx") << std::endl;

    system("pause");
    return 0;
}