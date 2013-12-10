/******************************************************************************
* 文件名：DSS.cpp
* 作者：补子畅
* 创建于：2013年7月28日
* 邮箱：buzichang@vip.qq.com
*****************************************************************************/

#include "DSS.h"
#include "stack"

struct FileData {
    FileData() {
        memset(this, 0, sizeof(FileData));
    }
    size_t fileDataSize;
    size_t typeDataSize;
    size_t dataSize;
    size_t nodeSize;
    char size_t_Size;
    char char_Size;
    size_t typeCount;
    size_t dataCount;
    size_t nodeCount;
    size_t allocationID;
    size_t allocatioTypeID;
    char blankBytes[64];
};

struct TypeData {
    TYPEID id;
    size_t dataSize;
    DSSChar name[TYPENAME_STRING_LENGTH_MAX];
    char blankBytes[16];
};

struct _Data {
    DATAID dataID;
    TYPEID typeID;
    size_t size;
    char blankBytes[16];
};

struct NodeData {
    TYPEID dataID;
    size_t childCount;
    DSSChar name[NODENAME_STRING_LENGTH_MAX];
    char blankBytes[16];
};

DSS::DSS(DSSAllocFunc *pAllocFunc)
      : m_pAllocFunc(pAllocFunc),
        m_id(0),
        m_typeid(TYPEID_INITIAL_VALUE),
        m_nodeCount(0) {
    assert(m_pAllocFunc);
    m_pRoot.reset(new DSSNode(this, NULL, 0));
}

#define ConstructorReturn(value) { if (pResultOut) { (*pResultOut) = value; } return; }
#define CheckReadBytes(bytes, exp) { if (exp != bytes) ConstructorReturn(CanNotReadOrWrite); }

DSS::DSS(DSSFileBase *pFileRW, DSSResult *pResultOut, DSSAllocFunc *pAllocFunc)
      : m_pAllocFunc(pAllocFunc),
        m_id(0),
        m_typeid(TYPEID_INITIAL_VALUE),
        m_nodeCount(0) {
    assert(pAllocFunc);
    m_pRoot.reset(new DSSNode(this, NULL, 0));
    std::shared_ptr<DSSChar> buffer(new DSSChar[WRITEREADFILE_BUFFERSIZE]);

    if (!pFileRW->OpenSuccess())
        ConstructorReturn(FileNotOpen);
    if (pFileRW->Writable())
        ConstructorReturn(CanNotReadOrWrite);

    //读入文件头
    {
        char fileHead[DATAFILE_HEAD_SIZE] = DATAFILE_HEAD;
        char fileHeadRead[DATAFILE_HEAD_SIZE];

        CheckReadBytes(DATAFILE_HEAD_SIZE, pFileRW->Read(fileHeadRead, DATAFILE_HEAD_SIZE));

        //检查文件头前两个字节
        if (fileHeadRead[0] != fileHead[0])
            ConstructorReturn(Incompatible);
        if (fileHeadRead[1] != fileHead[1])
            ConstructorReturn(Incompatible);
    }

    //读入文件数据
    FileData fileData;

    CheckReadBytes(sizeof(FileData), pFileRW->Read(&fileData, sizeof(FileData)));
    if (fileData.fileDataSize != sizeof(FileData))
        ConstructorReturn(Incompatible);
    if (fileData.typeDataSize != sizeof(TypeData))
        ConstructorReturn(Incompatible);
    if (fileData.dataSize != sizeof(_Data))
        ConstructorReturn(Incompatible);
    if (fileData.nodeSize != sizeof(NodeData))
        ConstructorReturn(Incompatible);
    if (fileData.size_t_Size != sizeof(size_t))
        ConstructorReturn(Incompatible);
    if (fileData.char_Size != sizeof(DSSChar))
        ConstructorReturn(Incompatible);
    m_id = fileData.allocationID;
    m_typeid = fileData.allocatioTypeID;

    //读入类型数据列表
    {
        TypeData tempTypeData;

        for (size_t i = 0; i < fileData.typeCount; ++i) {
            CheckReadBytes(sizeof(TypeData), pFileRW->Read(&tempTypeData, sizeof(TypeData)));
            //拒绝读入内建类型保留的编号
            if (tempTypeData.id <= TYPEID_INITIAL_VALUE)
                continue;
            m_typePool.insert(
                std::make_pair(tempTypeData.id, TypeInfo(tempTypeData.name, tempTypeData.dataSize)));
        }
    }

    //读入数据列表
    {
        _Data tempDataInfo;

        for (size_t i = 0; i < fileData.dataCount; ++i) {
            CheckReadBytes(sizeof(_Data), pFileRW->Read(&tempDataInfo, sizeof(_Data)));
            if ((tempDataInfo.size && tempDataInfo.dataID && tempDataInfo.typeID) == false)
                continue;
            auto result = m_dataPool.insert(
                std::make_pair(tempDataInfo.dataID, DataInfo(tempDataInfo.typeID, 0, tempDataInfo.size, NULL)));
            if (!result.second)
                ConstructorReturn(UnknowError);
            result.first->second.pDataBlock = m_pAllocFunc(tempDataInfo.size, NULL);
            CheckReadBytes(tempDataInfo.size, pFileRW->Read(result.first->second.pDataBlock, tempDataInfo.size));
        }
    }

    //读入节点数据列表
    {
        NodeData tempNodeData;
        //读入根节点数据
        CheckReadBytes(sizeof(NodeData), pFileRW->Read(&tempNodeData, sizeof(NodeData)));

        std::stack<std::pair<DSSNode*, size_t> > curReadNode;
        curReadNode.push(std::make_pair(this->GetRoot(), tempNodeData.childCount));

        while(!curReadNode.empty()) {
            DSSNode *pCurNode = curReadNode.top().first;
            size_t &surplusChild = curReadNode.top().second;

            if (surplusChild == 0) {
                curReadNode.pop();
                continue;
            }

            CheckReadBytes(sizeof(NodeData), pFileRW->Read(&tempNodeData, sizeof(NodeData)));

            DSSNode *newNode = new DSSNode(this, pCurNode, tempNodeData.dataID);
            auto result = pCurNode->m_pChild.insert(std::make_pair(tempNodeData.name, std::shared_ptr<DSSNode>(newNode)));

            if (result.second == false) {
                ConstructorReturn(UnknowError);
            }
            
            if (tempNodeData.childCount != 0) {
                curReadNode.push(std::make_pair(result.first->second.get(), tempNodeData.childCount));
            }

            --surplusChild;
        }
    }

    ConstructorReturn(Success);
}

DSS::~DSS() {
    auto iter = m_dataPool.begin();
    for (; iter != m_dataPool.end(); ++iter) {
        m_pAllocFunc(0, iter->second.pDataBlock);
        iter->second.pDataBlock = NULL;
    }
    m_dataPool.clear();
    m_pRoot->ClearChild();
}

#define CheckWroteBytes(bytes, exp) { if (exp != bytes) return CanNotReadOrWrite; }

DSS::DSSResult DSS::Save(DSSFileBase *pFileRW) {
    std::shared_ptr<DSSChar> buffer(new DSSChar[WRITEREADFILE_BUFFERSIZE]);
    
    if (!pFileRW->OpenSuccess())
        return FileNotOpen;
    if (!pFileRW->Writable())
        return CanNotReadOrWrite;

    //写入文件头
    {
        char fileHead[DATAFILE_HEAD_SIZE] = DATAFILE_HEAD;
        CheckWroteBytes(DATAFILE_HEAD_SIZE, pFileRW->Write(fileHead, DATAFILE_HEAD_SIZE));
    }

    //写入文件数据
    {
        FileData fileData;

        fileData.fileDataSize = sizeof(FileData);
        fileData.typeDataSize = sizeof(TypeData);
        fileData.dataSize = sizeof(_Data);
        fileData.nodeSize = sizeof(NodeData);
        fileData.size_t_Size = sizeof(size_t);
        fileData.char_Size = sizeof(DSSChar);
        fileData.typeCount = m_typePool.size() - BUILT_IN_TYPE;
        fileData.dataCount = m_dataPool.size();
        fileData.nodeCount = m_nodeCount;
        fileData.allocationID = m_id;
        fileData.allocatioTypeID = m_typeid;

        CheckWroteBytes(sizeof(FileData), pFileRW->Write(&fileData, sizeof(FileData)));
    }

    //写入类型数据列表
    {
        TypeData tempTypeData;

        for (auto iter = m_typePool.begin(); iter != m_typePool.end(); ++iter) {
            //拒绝写出内建类型保留的编号
            if (iter->first <= TYPEID_INITIAL_VALUE)
                continue;
            memset(&tempTypeData, 0, sizeof(TypeData));
            tempTypeData.dataSize = iter->second.dataSize;
            tempTypeData.id = iter->first;
#ifdef DSS_USE_WCHAR
            wcsncpy_s(tempTypeData.name, iter->second.typeName.c_str(), TYPENAME_STRING_LENGTH_MAX);
#else
            strcpy_s(tempTypeData.name, iter->second.typeName.c_str());
#endif
            CheckWroteBytes(sizeof(TypeData), pFileRW->Write(&tempTypeData, sizeof(TypeData)));
        }
    }

    //写入数据列表
    {
        _Data tempDataInfo;
        for (auto iter = m_dataPool.begin(); iter != m_dataPool.end(); ++iter) {
            if (iter->second.referenceCount == 0) {
                tempDataInfo.dataID = 0;
                tempDataInfo.typeID = 0;
                tempDataInfo.size = 0;
                CheckWroteBytes(sizeof(_Data), pFileRW->Write(&tempDataInfo, sizeof(_Data)));
            } else {
                tempDataInfo.dataID = iter->first;
                tempDataInfo.typeID = iter->second.typeID;
                tempDataInfo.size = iter->second.size;
                CheckWroteBytes(sizeof(_Data), pFileRW->Write(&tempDataInfo, sizeof(_Data)));
                CheckWroteBytes(tempDataInfo.size, pFileRW->Write(iter->second.pDataBlock, tempDataInfo.size));
            }
        }
    }

    //写入节点数据列表
    {
        std::stack<std::pair<DSSNode*, DSSNodeChildIterator> > curWriteNode;
        curWriteNode.push(std::make_pair(this->GetRoot(), 
            this->GetRoot()->GetChildIterator()));

        NodeData tempNodeData;
#ifdef DSS_USE_WCHAR
            wcsncpy_s(tempNodeData.name, L"dss-root", NODENAME_STRING_LENGTH_MAX);
#else
            strcpy_s(tempNodeData.name, "dss-root");
#endif
        tempNodeData.dataID = 0;
        tempNodeData.childCount = GetRoot()->ChildCount();

        //首先写入根节点数据
        CheckWroteBytes(sizeof(NodeData), pFileRW->Write(&tempNodeData, sizeof(NodeData)));

        while(!curWriteNode.empty()) {
            DSSNode *pCurNode = curWriteNode.top().first;
            DSSNodeChildIterator &curIter = curWriteNode.top().second;

            if (curIter.End()) {
                curWriteNode.pop();
                continue;
            }

            tempNodeData.dataID = curIter.GetNode()->GetDataID();
            tempNodeData.childCount = curIter.GetNode()->ChildCount();
#ifdef DSS_USE_WCHAR
            wcsncpy_s(tempNodeData.name, curIter.GetName().c_str(), NODENAME_STRING_LENGTH_MAX);
#else
            strcpy_s(tempNodeData.name, curIter.GetName().c_str());
#endif
            CheckWroteBytes(sizeof(NodeData), pFileRW->Write(&tempNodeData, sizeof(NodeData)));

            if (curIter.GetNode()->ChildCount()) {
                curWriteNode.push(std::make_pair(curIter.GetNode(), 
                    curIter.GetNode()->GetChildIterator()));
            }

            curIter.Next();
        }
    }
    return Success;
}

DATAID DSS::CreateData(const DSSStr &typeName, DataInfo **pOut) {
    return CreateData(GetTypeID(typeName), pOut);
}

DATAID DSS::CreateData(TYPEID typeID, DataInfo **pOut) {
    if (typeID == 0)
        return 0;
    if (m_typePool.find(typeID) == m_typePool.end())
        return 0;
    DataInfo info;
    info.typeID = typeID;
    size_t dataSize = GetTypeInfo(info.typeID)->dataSize;
    info.pDataBlock = m_pAllocFunc(dataSize, NULL);
    info.size = dataSize;
    info.referenceCount = 0;
    auto insertResult = m_dataPool.insert(std::make_pair(++m_id, info));
    if(insertResult.second == false) {
        m_pAllocFunc(0, info.pDataBlock);
        --m_id;
        return NULL;
    }
    if (pOut)
        *pOut = &insertResult.first->second;
    return m_id;
}

bool DSS::DeleteData(DATAID id) {
    if (!id) return NULL;
    auto result = m_dataPool.find(id);
    if (result == m_dataPool.end()) {
        return false;
    } else {
        m_pAllocFunc(0, result->second.pDataBlock);
        m_dataPool.erase(result);
        return true;
    }
}

void *DSS::GetData(DATAID id) {
    if (!id) return NULL;
    auto result = m_dataPool.find(id);
    if (result == m_dataPool.end()) {
        return NULL;
    } else {
        return result->second.pDataBlock;
    }
}

const void *DSS::GetData(DATAID id) const {
    if (!id) return NULL;
    auto result = m_dataPool.find(id);
    if (result == m_dataPool.end()) {
        return NULL;
    } else {
        return result->second.pDataBlock;
    }
}

DataInfo *DSS::GetDataInfo(DATAID id) {
    if (!id) return NULL;
    auto result = m_dataPool.find(id);
    if (result == m_dataPool.end()) {
        return NULL;
    } else {
        return &result->second;
    }
}

const DataInfo *DSS::GetDataInfo(DATAID id) const {
    if (!id) return NULL;
    auto result = m_dataPool.find(id);
    if (result == m_dataPool.end()) {
        return NULL;
    } else {
        return &result->second;
    }
}

TYPEID DSS::RegisterType(const DSSStr &typeName, size_t dataSize) {
    //不允许创建重复的名称
    assert(GetTypeID(typeName) == false);
    TypeInfo typeInfo;
    typeInfo.typeName = typeName;
    typeInfo.dataSize = dataSize;
    if (m_typePool.insert(std::make_pair(++m_typeid, typeInfo)).second == false) {
        --m_typeid;
        return 0;
    }
    return m_typeid;
}

const TypeInfo *DSS::GetTypeInfo(TYPEID id) const {
    if (!id) return NULL;
    auto result = m_typePool.find(id);
    if (result == m_typePool.end()) {
        return NULL;
    } else {
        return &result->second;
    }
}

const TypeInfo *DSS::GetTypeInfo(const DSSStr &typeName) const {
    return GetTypeInfo(GetTypeID(typeName));
}

TYPEID DSS::GetTypeID(const DSSStr &typeName) const {
    for (auto iter = m_typePool.begin(); iter != m_typePool.end(); ++iter) {
        if (iter->second.typeName == typeName) {
            return iter->first;
        }
    }
    return 0;
}

bool DSS::UnRegisterType(TYPEID id) {
    if (!id) return false;
    auto result = m_typePool.find(id);
    if (result == m_typePool.end()) {
        return false;
    } else {
        m_typePool.erase(result);
        return true;
    }
}

DSSDataIterator DSS::GetDataIterator() {
    return DSSDataIterator(this, m_dataPool.begin(), m_dataPool.end());
}

DSSNode *DSS::operator() (const DSSStr &path) {
    return GetRoot()->operator()(path);
}

const DSSNode *DSS::operator()(const DSSStr &path) const {
    return GetRoot()->operator()(path);
}

DSSNode *DSS::operator() (const DSSStr &path, bool autoCreate) {
    return GetRoot()->operator()(path, autoCreate);
}

DSSNode *DSS::operator() (const DSSStr &path, const DSSStr &typeName, bool autoCreate, bool *pWasCreate) {
    return GetRoot()->operator()(path, typeName, autoCreate, pWasCreate);
}