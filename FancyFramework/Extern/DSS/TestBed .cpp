
#include "windows.h"
#include "DSS.h"
#include <iostream>

struct String {
    DSSChar str[32];
};

void PrintDSS(DSS &dss, DSSNode *node, 
#ifdef DSS_USE_WCHAR
              char *buf, size_t bufSize, 
#endif
              unsigned recursion) {
    if (recursion == 0)
        std::cout<<"root";
    if (node->GetDataID()) {
        std::cout<<" - DataID:"<<node->GetDataID()<<std::endl;
    } else {
        std::cout<<" - NilData"<<std::endl;
    }
    for (unsigned i = 0; i != recursion; ++i)
        std::cout<<"  ";
    std::cout<<"{\n";
    for (auto iter = node->GetChildIterator(); !iter.End(); iter.Next()) {
        for (unsigned i = 0; i != recursion + 1; ++i)
            std::cout<<"  ";
#ifdef DSS_USE_WCHAR
        wcstombs_s(NULL, buf, 256, iter.GetName().c_str(), bufSize);
        std::cout<<"'"<<buf<<"'";
#else
        std::cout<<"'"<<iter.GetName().c_str()<<"'";
#endif
        if (iter.GetNode()->ChildCount())
            PrintDSS(dss, iter.GetNode(), 
#ifdef DSS_USE_WCHAR
            buf, bufSize, 
#endif
            recursion + 1);
        else
            if (iter.GetNode()->GetDataID()) {
                std::cout<<" - DataID:"<<iter.GetNode()->GetDataID()<<std::endl;
            } else {
                std::cout<<" - NilData"<<std::endl;
            }
    }
    for (unsigned i = 0; i != recursion; ++i)
        std::cout<<"  ";
    std::cout<<"}\n";

    if (recursion == 0) {
        std::cout<<"\nData List:\n";
        for (DSSDataIterator iter = dss.GetDataIterator(); 
            !iter.End(); iter.Next()) {
                std::cout<<"#"<< iter.GetID() 
                    << " - " 
                    << iter.GetPtr<String>()->str
                    << " - Size:"
                    << iter.GetSize()
                    << " - TypeID:"
                    << iter.GetTypeID()
                    << std::endl;
        }
    }
}

int main() {
    {
        DSS dFile;
        
        //注册数据块类型
        dFile.RegisterType<String>(L"String");

        //创建一些节点并且写入数据
        DSSNode *strNode = dFile(L"data.test", L"String", true, NULL);
        String *str = strNode->GetData<String>(); 

        if (!strNode->Empty())
            wcsncpy_s(str->str, L"Test string :)", 14);

        DSSNode *strNode2 = dFile(L"data", L"String", true, NULL);
        String *str2 = strNode2->GetData<String>();     

        if (!strNode2->Empty())
            wcsncpy_s(str2->str, L"Test string#2 :)", 16);
        
        std::shared_ptr<DSSFile> fileWR(new DSSFile(L"file", true));

        //创建另一个dss系统
        DSS dFile2;

        //注册数据块类型
        dFile2.RegisterType<String>(L"str");

        String *str3 = dFile2(L"data.strpool.str01", L"str", true, NULL)->GetData<String>();

        if (str3)
            wcsncpy_s(str3->str, L"in the other dss!! :)", 21);

        //将两个dss系统写到同一个文件中
        if (dFile.Save(fileWR.get()) == DSS::Success && dFile2.Save(fileWR.get()) == DSS::Success)
            std::cout<<"\nSave succeed!!!"<<std::endl;
    }

    {
        std::shared_ptr<char> buffer(new char[256]);
        std::cout<<"\nRead File:\n"<<std::endl;
        std::shared_ptr<DSSFile> fileWR(new DSSFile(L"file", false));
        DSS::DSSResult result;
        //从文件中读取数据
        DSS file(fileWR.get(), &result);
        if (result == DSS::Success) {
            PrintDSS(file, file.GetRoot(), buffer.get(), 256, 0);
            DSS file2(fileWR.get(), &result);
            std::cout<<"\nRead other dss:\n"<<std::endl;
            if (result == DSS::Success)
                PrintDSS(file2, file.GetRoot(),buffer.get(), 256, 0);
        }
 
    }

    system("pause");
    return 0;
}