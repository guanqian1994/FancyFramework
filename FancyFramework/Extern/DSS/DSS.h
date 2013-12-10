/******************************************************************************
* 文件名：DSS.h
* 作者：补子畅
* 创建于：2013年7月27日
* 邮箱：buzichang@vip.qq.com
*****************************************************************************/

#ifndef DSS_H_
#define DSS_H_

#include <cassert>
#include <string>
#include <memory>
#include <list>
#include <map>

#define DSS_VERSION "1.0.0"
#define DSS_VERNUM 0x1000

#define DSS_VER_MAJOR 1
#define DSS_VER_MINOR 0
#define DSS_VER_REVISION 0
#define DSS_VER_SUBREVISION 0

//使用宽字符
#define DSS_USE_WCHAR
//优先使用ZLIB读写
#define DSS_USE_ZLIB

#define DATAFILE_HEAD { 0xCF, 0x58, DSS_VER_MAJOR, DSS_VER_MINOR, DSS_VER_REVISION, DSS_VER_SUBREVISION }
#define DATAFILE_HEAD_SIZE 6
#define WRITEREADFILE_BUFFERSIZE 256
#define TYPENAME_STRING_LENGTH_MAX 24
#define NODENAME_STRING_LENGTH_MAX 32

#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName)  \
            TypeName(const TypeName&);      \
            void operator=(const TypeName&)
#endif

#ifdef DSS_USE_WCHAR

typedef std::wstring DSSStr;
typedef wchar_t DSSChar;
#define PATH_DELIMITER L"."

#else

typedef std::string DSSStr;
typedef char DSSChar;
#define PATH_DELIMITER "."

#endif

#define TYPEID_INITIAL_VALUE 15
#define BUILT_IN_TYPE 0

/*! \brief 
        文件读写类 */
class DSSFileBase {
public:
    DSSFileBase(const DSSStr &fileName, bool writable)
        :  m_writable(writable) {
    }
    virtual ~DSSFileBase() { }
    virtual int Write(const void *data, unsigned int len) = 0;
    virtual int Read(void *buf, unsigned int len) = 0;
    virtual bool OpenSuccess() const = 0;
    virtual bool Writable() const { return m_writable; }
private:
    bool m_writable;
};

class WinFile;
class ZlibFile;

#ifdef _WINDOWS_

class WinFile : public DSSFileBase {
public:
    WinFile(const DSSStr &fileName, bool writable)
          : DSSFileBase(fileName, writable) {
#ifdef DSS_USE_WCHAR
        m_hFile = CreateFileW(
#else
        m_hFile = CreateFileA(
#endif
		    fileName.c_str(), 
		    writable ? GENERIC_WRITE|GENERIC_READ : GENERIC_READ,
		    FILE_SHARE_READ,
		    NULL,
		    writable ? OPEN_ALWAYS : OPEN_EXISTING,
		    FILE_ATTRIBUTE_NORMAL,
		    NULL);
    }
    ~WinFile() {
        CloseHandle(m_hFile);
    }
    int Write(const void *data, unsigned int len) {
        DWORD realWritten = 0;
        WriteFile(m_hFile, data, (DWORD)len, (LPDWORD)&realWritten, NULL);
        return realWritten;
    }
    int Read(void *buf, unsigned int len) {
        DWORD realReaded = 0;
        ReadFile(m_hFile, buf, (DWORD)len, (LPDWORD)&realReaded, NULL);
        return realReaded;
    }
    bool OpenSuccess() const {
        return m_hFile != INVALID_HANDLE_VALUE;
    }
public:
    HANDLE m_hFile;
};

#endif

#ifdef ZLIB_H

class ZlibFile : public DSSFileBase {
public:
    ZlibFile(const DSSStr &fileName, bool write)
          : DSSFileBase(fileName, write),
            m_file(NULL) {
#ifdef DSS_USE_WCHAR
        std::shared_ptr<char> buffer(new char[256]);
        wcstombs_s(NULL, buffer.get(), 256, fileName.c_str(), 256);
        m_file = gzopen(buffer.get(), write ? "wb" : "r");
#else
        m_file = gzopen(fileName.c_str(), write ? "wb" : "r");
#endif
    }
    ~ZlibFile() {
        if (m_file)
            gzclose(m_file);
    }
    int Write(const void *data, unsigned int len) {
        return gzwrite(m_file, data, len);
    }
    int Read(void *buf, unsigned int len) {
        return gzread(m_file, buf, len);
    }
    bool OpenSuccess() const {
        return m_file;
    }
private:
    gzFile m_file;
};

#endif

#if defined (ZLIB_H) && defined (DSS_USE_ZLIB)
    typedef ZlibFile DSSFile;
#else
    typedef WinFile DSSFile;
#endif

typedef size_t DATAID;
typedef size_t TYPEID;
typedef void* (DSSAllocFunc)(size_t, void*);

class DSS;
class DSSNode;

struct DataInfo {
    friend class DSS;
    friend class DSSNode;
public:
    DataInfo() { }
    DataInfo(TYPEID tID, size_t refCount, size_t size, void *pData)
        : typeID(tID), 
          referenceCount(referenceCount), 
          size(size), pDataBlock(pData) { }

    void *GetUserType() {
        return pDataBlock;
    }

    size_t GetSize() const {
        return size;
    }
    TYPEID GetTypeID() const {
        return typeID;
    }
private:
    TYPEID typeID;
    size_t referenceCount;
    size_t size;
    void *pDataBlock;
};

struct TypeInfo {
    TypeInfo() { }
    TypeInfo(const DSSStr &tName, size_t size)
        : typeName(tName), dataSize(size) { }
    DSSStr typeName;
    size_t dataSize;
};

/*! \brief 
        数据块列表迭代器 */
class DSSDataIterator {
    friend class DSS;
public:
    DSSDataIterator(
        DSS *pDFile,
        std::map<DATAID, DataInfo>::iterator iter,
        std::map<DATAID, DataInfo>::iterator endIter)
      : m_pDFile(pDFile),
        m_iter(iter),
        m_endIter(endIter) {
    }
    ~DSSDataIterator() {
    }
    bool End() const {
        return m_iter == m_endIter;
    }
    void Next() {
        ++m_iter;
    }
    DATAID GetID() {
        return m_iter->first;
    }
    size_t GetSize() const {
        return m_iter->second.GetSize();
    }
    void* GetPtr() {
        return m_iter->second.GetUserType();
    }
    const void* GetPtr() const {
        return m_iter->second.GetUserType();
    }
    template <typename T> T* GetPtr() {
        return static_cast<T*>(m_iter->second.GetUserType());
    }
    template <typename T> const T* GetPtr() const {
        return static_cast<T*>(m_iter->second.GetUserType());
    }
    TYPEID GetTypeID() const {
        return m_iter->second.GetTypeID();
    }
    DataInfo &Get() {
        return m_iter->second;
    }
    const DataInfo &Get() const {
        return m_iter->second;
    }
private:
    DSS *m_pDFile;
    std::map<DATAID, DataInfo>::iterator m_iter;
    std::map<DATAID, DataInfo>::iterator m_endIter;
};

/*! \brief 
        子节点迭代器 */
class DSSNodeChildIterator {
    friend class DSS;
public:
    DSSNodeChildIterator(
        DSS *pDFile,
        std::map<DSSStr, std::shared_ptr<DSSNode> >::iterator iter,
        std::map<DSSStr, std::shared_ptr<DSSNode> >::iterator endIter)
      : m_pDFile(pDFile),
        m_iter(iter),
        m_endIter(endIter) {
    }
    ~DSSNodeChildIterator() {
    }
    bool End() const {
        return m_iter == m_endIter;
    }
    void Next() {
        ++m_iter;
    }
    const DSSStr &GetName() const {
        return m_iter->first;
    }
    DSSNode *GetNode() {
        return m_iter->second.get();
    }
    const DSSNode *GetNode() const {
        return m_iter->second.get();
    }
private:
    DSS *m_pDFile;
    std::map<DSSStr, std::shared_ptr<DSSNode> >::iterator m_iter;
    std::map<DSSStr, std::shared_ptr<DSSNode> >::iterator m_endIter;
};

/*! \brief 
        数据存储系统 */
class DSS {
    friend class DSSNode;
public:
    enum DSSResult {
        Success             = 0,
        Incompatible        = 1,
        FileNotOpen         = 2,
        CanNotReadOrWrite   = 3,
        UnknowError         = 4,
    };
    /*! \brief 
            构造新的存储文件 
        \param pAllocFunc
            用于分配内存的函数指针*/
    DSS(DSSAllocFunc *pAllocFunc = DSS::AllocFunc);
    /*! \brief 
            构造新的存储文件 
        \param pFileRW
            文件读写类（读模式）
        \param pAllocFunc
            用于分配内存的函数指针*/
    DSS(DSSFileBase *pFileRW, DSSResult *pResultOut, DSSAllocFunc *pAllocFunc = DSS::AllocFunc);
    ~DSS();
    /*! \brief 
            存储数据
        \param fileRW
            文件读写类（写模式）
        \return 
            见 SaveResult */
    DSSResult Save(DSSFileBase *pFileRW);
    /*! \brief 
            新建一个数据块
        \param typeName
            类型名
        \param pOut
            返回数据块指针
        \return 
            返回数据块索引，失败返回索引为0 */
    DATAID CreateData(const DSSStr &typeName, DataInfo **pOut);
    /*! \brief 
            新建一个数据块
        \param typeID
            类型索引
        \param pOut
            返回数据块指针
        \return 
            返回数据块索引，失败返回索引为0 */
    DATAID CreateData(TYPEID typeID, DataInfo **pOut);
    /*! \brief 
            删除一个数据块

            注意：这是一个不安全的操作，如果删除某个数据块，但是并不会对引用该数据块的节点
            进行任何处理。如果你确实需要删除某个数据块，并且将引用该数据块的节点置为空节点，
            你可以将需要删除的数据块全部删除后保存DSS至文件，在下次读取时这些引用到已经被
            删除的节点会被置为空节点。或者你可以使用 DSSNode::Check 方法安全地使用节点。
        \param id
            数据块索引
        \return 
            操作是否成功，返回false表示这个数据块不存在 */
    bool DeleteData(DATAID id);
    /*! \brief 
            获得数据
        \param id
            数据块索引
        \return 
            返回数据指针，失败返回NULL */
    void *GetData(DATAID id);
    const void *GetData(DATAID id) const;
    /*! \brief 
            获得数据块信息结构
        \param id
            数据块索引
        \return 
            返回数据块信息结构指针，失败返回NULL */
    DataInfo *GetDataInfo(DATAID id);
    const DataInfo *GetDataInfo(DATAID id) const ;
    /*! \brief 
            注册一个新的数据类型
        \param typeName
            类型名称
        \param dataSize
            该类型所占的字节数
        \return 
            类型ID，失败返回0 */
    TYPEID RegisterType(const DSSStr &typeName, size_t dataSize);
    /*! \brief 
            注册一个新的数据类型
        \param typeName
            类型名称
        \return 
            类型ID，失败返回0 */
    template <typename T> TYPEID RegisterType(const DSSStr &typeName) {
        return RegisterType(typeName, sizeof(T));
    }
    /*! \brief 
            注销一个数据类型
        \param typeName
            类型名称
        \return 
            类型索引，失败返回0 */
    bool UnRegisterType(TYPEID id);
    /*! \brief 
            获得数据类型信息结构
        \param id
            类型索引
        \return 
            类型信息结构，失败返回NULL */
    const TypeInfo *GetTypeInfo(TYPEID id) const;
    /*! \brief 
            获得数据类型信息结构
        \param typeName
            类型名
        \return 
            类型信息结构，失败返回NULL */
    const TypeInfo *GetTypeInfo(const DSSStr &typeName) const;
    /*! \brief 
            获得数据索引
        \param typeName
            类型名
        \return 
            类型索引，失败返回0 */
    TYPEID GetTypeID(const DSSStr &typeName) const;
    /*! \brief 
            获得数据迭代器
        \return 
            返回迭代器 */
    DSSDataIterator GetDataIterator();
    /*! \brief 
            获得根节点
        \return 
            返回根节点 */
    DSSNode *GetRoot() { return m_pRoot.get(); }
    const DSSNode *GetRoot() const { return m_pRoot.get(); }
    /*! \brief 
            获得当前数据块数量
        \return 
            返回数量 */
    size_t DataCount() const { return m_dataPool.size(); }
    /*! \brief 
            获得当前节点数量
        \return 
            返回数量 */
    size_t NodeCount() const { return m_nodeCount; }
    /*! \brief 
            见 DSSNode 类的 () 运算符重载*/
    DSSNode *operator() (const DSSStr &path);
    const DSSNode *operator() (const DSSStr &path) const;
    DSSNode *operator() (const DSSStr &path, bool autoCreate);
    DSSNode *operator() (const DSSStr &path, const DSSStr &typeName, bool autoCreate, bool *pWasCreate);
    
    static void *AllocFunc(size_t want, void *p) {
        if (want) {
            void *p = new char[want];
            memset(p, 0, want);
            return p;
        } else {
            delete p;
            return NULL;
        }
    }
private:
    DATAID m_id;
    TYPEID m_typeid;
    size_t m_nodeCount;
    DSSAllocFunc *m_pAllocFunc;
    std::shared_ptr<DSSNode> m_pRoot;
    std::map<TYPEID, TypeInfo> m_typePool;
    std::map<DATAID, DataInfo> m_dataPool;
    DISALLOW_COPY_AND_ASSIGN(DSS);
};

class DSSNode {
    friend class DSS;
public:
    ~DSSNode();
    /*! \brief 
            创建子节点

            创建一个新的节点和新的数据块，并让新节点引用新数据块。
        \param path
            路径
        \param typeName
            类型名
        \param autoCreate
            是否自动创建。如果该参数传递 true，如果你要创建一个中间节点都不存在的路径时，会
            自动创建中间节点为空节点。
        \return 
            返回被创建的新节点指针，失败返回NULL */
    DSSNode *CreateChild(const DSSStr &path, const DSSStr &typeName, bool autoCreate);
    /*! \brief 
            创建引用数据子节点

            创建一个新的节点，并且引用提供的节点的数据块。
        \param path
            路径
        \param pReference
            引用目标节点，如果传递 NULL，则创建的是空节点。
        \param autoCreate
            是否自动创建。如果该参数传递 true，如果你要创建一个中间节点都不存在的路径时，会
            自动创建中间节点为空节点。
        \return 
            返回被创建的新节点指针，失败返回NULL */
    DSSNode *CreateChild(const DSSStr &path, const DSSNode *pReference, bool autoCreate);
    /*! \brief 
            获得父节点
        \return 
            返回父节点指针 */
    DSSNode *GetParent() { return m_pDParent; }
    const DSSNode *GetParent() const { return m_pDParent; }
    /*! \brief 
            获得子节点
        \param path
            路径
        \return 
            返回子节点指针 */
    DSSNode *GetChild(const DSSStr &path);
    const DSSNode *GetChild(const DSSStr &path) const;
    /*! \brief 
            获得子节点
        \param path
            路径
        \return 
            删除成功返回 true， 删除失败返回false */
    bool DeleteChild(const DSSStr &path);
    /*! \brief 
            获得子节点数目
        \return 
            子节点数目 */
    size_t ChildCount() const { return m_pChild.size(); }
    /*! \brief 
            清空子节点*/
    void ClearChild();
    /*! \brief 
            获得数据指针
        \return 
            数据指针 */
    void *GetData() { 
        return this ? m_dataInfo->GetUserType() : NULL;
    }
    const void *GetData() const {
        return this ? m_dataInfo->GetUserType() : NULL;
    }
    template<typename T> T *GetData() {
        assert(m_dataInfo->GetSize() == sizeof(T));
        return this ? static_cast<T*>(m_dataInfo->GetUserType()) : NULL; 
    }
    template<typename T> const T *GetData() const {
        assert(m_dataInfo->GetSize() == sizeof(T));
        return this ? static_cast<T*>(m_dataInfo->GetUserType()) : NULL; 
    }
    /*! \brief 
            获得数据信息结构指针
        \return 
            数据信息结构指针 */
    DataInfo *GetDataInfo() { return m_pDFile->GetDataInfo(m_id); }
    const DataInfo *GetDataInfo() const { return m_pDFile->GetDataInfo(m_id); }
    /*! \brief 
            获得数据索引
        \return 
            数据索引*/
    DATAID GetDataID() const { return m_id; }
    /*! \brief 
            检查节点数据是否有效
        \return 
            节点数据无效返回 false，有效返回true */
    bool Check();
    /*! \brief 
            检查节点是否引用数据
        \return 
            存在数据返回 false，不存在数据返回true */
    bool Empty() const;
    /*! \brief 
            重置数据

            清空节点数据
        \return 
            返回当前节点 */
    DSSNode *ResetData();
    /*! \brief 
            重置数据
        \param pNode
            重置当前数据，再根据传递节点的数据块类型来为当前节点创建一个相同类型的数据块 
        \return 
            返回当前节点 */
    DSSNode *ResetData(DSSNode *pNode);
    /*! \brief 
            重置数据
        \param pNode
            重置当前数据，再根据传递的节点类型名创建一个新的数据块 
        \return 
            创建成功返回 true, 创建失败返回 false */
    bool ResetData(const DSSStr &typeName);
    /*! \brief 
            交换数据块
        \param pNode
            将当前节点的数据块和传递的节点交换数据块引用
        \return 
            返回当前节点 */
    DSSNode *SwapData(DSSNode *pNode);
    /*! \brief 
            转移数据块
        \param pNode
            删除当前节点的数据块，将传入的节点数据转为当前节点的数据，原节点置为空节点
        \return 
            返回当前节点 */
    DSSNode *ReplaceData(DSSNode *pNode);
    /*! \brief 
            获得子节点迭代器
        \return 
            返回子节点迭代器 */
    DSSNodeChildIterator GetChildIterator();
    /*! \brief 
            获得子节点

            等价于 GetChild
        \param path
            节点路径
        \return 
            返回子节点指针 */
    DSSNode *operator() (const DSSStr &path);
    const DSSNode *operator() (const DSSStr &path) const;
    /*! \brief 
            获得子节点

            如果这个子节点不存在，则根据 autoCreate 选项来创建一个空的子节点或整个路径
        \param path
            节点路径
        \param autoCreate
            是否自动创建。如果该参数传递 true，如果你要创建一个中间节点都不存在的路径时
            ，会自动创建中间节点为空节点。
        \return 
            返回子节点指针，失败返回 NULL */
    DSSNode *operator() (const DSSStr &path, bool autoCreate);
    /*! \brief 
            获得子节点

            如果这个子节点不存在，则根据 autoCreate 选项来创建一个指定类型的末尾子节点，
            如果存在中间节点，则中间节点会被创建为空节点。并且这个方法会对末尾子节点进行
            类型检查，如果类型与 typeName 参数不符合，则会重置末尾子节点的类型。
        \param path
            节点路径
        \param typeName
            类型名
        \param autoCreate
            是否自动创建。如果该参数传递 true，如果你要创建一个中间节点都不存在的路径时，
            会自动创建中间节点为空节点。
        \return 
            返回子节点指针，失败返回 NULL */
    DSSNode *operator() (const DSSStr &path, const DSSStr &typeName, bool autoCreate, bool *pWasCreate);
private:
    DSSNode(DSS *pDFile, DSSNode *pParent, DATAID id);
    DSS *m_pDFile;
    DATAID m_id;
    DSSNode *m_pDParent;
    DataInfo *m_dataInfo;
    std::map<DSSStr, std::shared_ptr<DSSNode> > m_pChild;
    DISALLOW_COPY_AND_ASSIGN(DSSNode);
};

#endif
