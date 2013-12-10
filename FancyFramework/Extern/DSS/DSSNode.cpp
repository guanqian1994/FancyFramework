/******************************************************************************
* 文件名：DSSNode.cpp
* 作者：补子畅
* 创建于：2013年7月28日
* 邮箱：buzichang@vip.qq.com
*****************************************************************************/

#include "DSS.h"

DSSNode::DSSNode(DSS *pDFile, DSSNode *pParent, DATAID id)
      : m_pDFile(pDFile),
        m_pDParent(pParent),
        m_id(id) {
    ++m_pDFile->m_nodeCount;
    DataInfo *tempInfo = m_pDFile->GetDataInfo(m_id);
    if (tempInfo) {
        m_dataInfo = tempInfo;
        ++m_dataInfo->referenceCount;
    } else {
        m_id = 0;
    }
}

DSSNode::~DSSNode() {
    --m_pDFile->m_nodeCount;
    m_pChild.clear();
    assert(static_cast<bool>(m_id) == static_cast<bool>(m_dataInfo));
    /*如果整个DSS在析构时，数据可能提前被删除*/
    ResetData();
}

DSSNode *DSSNode::CreateChild(const DSSStr &path, 
                              const DSSStr &typeName,
                              bool autoCreate) {
    DSSStr::size_type fpos = path.find(PATH_DELIMITER);
    if(fpos == DSSStr::npos) {
        /*没有找到分隔符*/
        auto iter = m_pChild.find(path);
        if (iter == m_pChild.end()) {
            DATAID dataID = m_pDFile->CreateData(typeName, NULL);
            if (dataID == 0)
                return NULL;
            DSSNode *newNode = new DSSNode(m_pDFile, this, dataID);
            auto result = m_pChild.insert(std::make_pair(path, std::shared_ptr<DSSNode>(newNode)));
            if (result.second) {
                return newNode;
            } else {
                return NULL;
            }
        } else {
            return NULL;
        }
    } else {
        /*找到分隔符*/
        auto iter = m_pChild.find(path.substr(0, fpos));
        if (iter != m_pChild.end()) {
            return iter->second->CreateChild(path.substr(fpos + 1, path.size()), typeName, autoCreate);
        } else {
            DSSNode *pAutoCreateNode = CreateChild(path.substr(0, fpos), NULL, autoCreate);
            return pAutoCreateNode->CreateChild(path.substr(fpos + 1, path.size()), typeName, autoCreate);;
        }
    }
    return NULL;
}

DSSNode *DSSNode::CreateChild(const DSSStr &path, const DSSNode *pReference, bool autoCreate) {
    DSSStr::size_type fpos = path.find(PATH_DELIMITER);
    if(fpos == DSSStr::npos) {
        //没有找到分隔符
        auto iter = m_pChild.find(path);
        if (iter == m_pChild.end()) {
            DATAID dataID = 0;
            if (pReference)
                dataID = pReference->m_id;
            DSSNode *newNode = new DSSNode(m_pDFile, this, dataID);
            auto result = m_pChild.insert(std::make_pair(path, std::shared_ptr<DSSNode>(newNode)));
            if (result.second) {
                return newNode;
            } else {
                return NULL;
            }
        } else {
            return NULL;
        }
    } else {
        //找到分隔符
        auto iter = m_pChild.find(path.substr(0, fpos));
        if (iter != m_pChild.end()) {
            return iter->second->CreateChild(path.substr(fpos + 1, path.size()), pReference, autoCreate);
        } else {
            DSSNode *pAutoCreateNode = CreateChild(path.substr(0, fpos), NULL, false);
            return pAutoCreateNode->CreateChild(path.substr(fpos + 1, path.size()), pReference, autoCreate);;
        }
    }
    return NULL;
}

DSSNode *DSSNode::GetChild(const DSSStr &path) {
    DSSStr::size_type fpos = path.find(PATH_DELIMITER);
    if(fpos == DSSStr::npos) {
        //没有找到分隔符
        auto iter = m_pChild.find(path);
        if (iter != m_pChild.end()) {
            return iter->second.get();
        } else {
            return NULL;
        }
    } else {
        //找到分隔符
        auto iter = m_pChild.find(path.substr(0, fpos));
        if (iter != m_pChild.end()) {
            return iter->second->GetChild(path.substr(fpos + 1, path.size()));
        } else {
            return NULL;
        }
    }
    return NULL;
}

const DSSNode *DSSNode::GetChild(const DSSStr &path) const {
    DSSStr::size_type fpos = path.find(PATH_DELIMITER);
    if(fpos == DSSStr::npos) {
        //没有找到分隔符
        auto iter = m_pChild.find(path);
        if (iter != m_pChild.end()) {
            return iter->second.get();
        } else {
            return NULL;
        }
    } else {
        //找到分隔符
        auto iter = m_pChild.find(path.substr(0, fpos));
        if (iter != m_pChild.end()) {
            return iter->second->GetChild(path.substr(fpos + 1, path.size()));
        } else {
            return NULL;
        }
    }
    return NULL;
}

bool DSSNode::DeleteChild(const DSSStr &path) {
    DSSNode *pWillDelNode = this->GetChild(path);
    if (!pWillDelNode)
        return false;
    DSSStr childName;
    DSSStr::size_type fpos = path.rfind(PATH_DELIMITER);
    if(fpos == DSSStr::npos) {
        childName = path;
    } else {
        childName = path.substr(fpos + 1, path.size());
    }
    auto delIter = pWillDelNode->GetParent()->m_pChild.find(childName);
    if (delIter != pWillDelNode->GetParent()->m_pChild.end()) {
        pWillDelNode->GetParent()->m_pChild.erase(delIter);
        return true;
    } else {
        return false;
    }
}

void DSSNode::ClearChild() {
    m_pChild.clear();
}

bool DSSNode::Empty() const {
    return this ? !(m_id): true;
}

bool DSSNode::Check() {
    if (this == NULL)
        return NULL;
    if (m_id == 0)
        return false;
    if (m_dataInfo = m_pDFile->GetDataInfo(m_id)) {
        return true;
    } else {
        m_id = 0;
        return false;
    }
}

DSSNode *DSSNode::ResetData() {
    DataInfo *pTempInfo = m_pDFile->GetDataInfo(m_id);
    if (pTempInfo) {
        --pTempInfo->referenceCount;
        if (pTempInfo->referenceCount == 0) 
            m_pDFile->DeleteData(m_id);
    }
    m_id = 0;
    m_dataInfo = NULL;
    return this;
}

DSSNode *DSSNode::ResetData(DSSNode *pNode) {
    ResetData();
    DataInfo *tempInfo = pNode->GetDataInfo();
    if (tempInfo) {
        DataInfo *result = NULL;
        m_id = m_pDFile->CreateData(pNode->m_id, &result);
        m_dataInfo = result;
        ++m_dataInfo->referenceCount;
        _memccpy(m_dataInfo->pDataBlock, tempInfo->pDataBlock, 0, m_dataInfo->size);
    } else {
        m_id = 0;
        m_dataInfo = NULL;
    }
    return this;
}

bool DSSNode::ResetData(const DSSStr &typeName) {
    ResetData();
    m_id = m_pDFile->CreateData(m_pDFile->GetTypeID(typeName), &m_dataInfo);
    ++m_dataInfo->referenceCount;
    return m_id;
}

DSSNode *DSSNode::SwapData(DSSNode *pNode) {
    DATAID tempID = m_id;
    DataInfo *pTempInfo = m_dataInfo;
    m_id = pNode->m_id;
    m_dataInfo = pNode->m_dataInfo;
    pNode->m_id = tempID;
    pNode->m_dataInfo = pTempInfo;
    return this;
}

DSSNode *DSSNode::ReplaceData(DSSNode *pNode) {
    ResetData();
    m_id = pNode->m_id;
    m_dataInfo = pNode->m_dataInfo;
    pNode->m_id = 0;
    pNode->m_dataInfo = NULL;
    return this;
}

DSSNodeChildIterator DSSNode::GetChildIterator() {
    return DSSNodeChildIterator(m_pDFile, m_pChild.begin(), m_pChild.end());
}

DSSNode *DSSNode::operator() (const DSSStr &path) {
    return GetChild(path);
}

const DSSNode *DSSNode::operator() (const DSSStr &path) const {
    return GetChild(path);
}


DSSNode *DSSNode::operator() (const DSSStr &path, bool autoCreate) {
    DSSNode *pNodeResult = GetChild(path);
    if (pNodeResult)
        return pNodeResult;
    else 
        return pNodeResult->CreateChild(path, NULL, autoCreate);
}

DSSNode *DSSNode::operator() (const DSSStr &path, const DSSStr &typeName, bool autoCreate, bool *pWasCreate) {
    const TypeInfo *pTypeInfo = m_pDFile->GetTypeInfo(typeName);
    if (pWasCreate)
        *pWasCreate = false;
    if (pTypeInfo == NULL)
        return NULL;
    DSSNode *pNodeResult = GetChild(path);
    if (pNodeResult)
        if (pNodeResult->GetDataInfo() && (pNodeResult->GetDataInfo()->size == pTypeInfo->dataSize)) {
            return pNodeResult;
        } else {
            return pNodeResult->ResetData(typeName) ? pNodeResult : NULL;
        }
    else {
        if (autoCreate) {
            pNodeResult = this->CreateChild(path, typeName, true);
            if (pWasCreate)
                *pWasCreate = static_cast<bool>(pNodeResult);
            return pNodeResult;
        } else {
            return NULL;
        }
    }
}