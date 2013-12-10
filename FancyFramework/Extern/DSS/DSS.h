/******************************************************************************
* �ļ�����DSS.h
* ���ߣ����ӳ�
* �����ڣ�2013��7��27��
* ���䣺buzichang@vip.qq.com
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

//ʹ�ÿ��ַ�
#define DSS_USE_WCHAR
//����ʹ��ZLIB��д
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
        �ļ���д�� */
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
        ���ݿ��б������ */
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
        �ӽڵ������ */
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
        ���ݴ洢ϵͳ */
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
            �����µĴ洢�ļ� 
        \param pAllocFunc
            ���ڷ����ڴ�ĺ���ָ��*/
    DSS(DSSAllocFunc *pAllocFunc = DSS::AllocFunc);
    /*! \brief 
            �����µĴ洢�ļ� 
        \param pFileRW
            �ļ���д�ࣨ��ģʽ��
        \param pAllocFunc
            ���ڷ����ڴ�ĺ���ָ��*/
    DSS(DSSFileBase *pFileRW, DSSResult *pResultOut, DSSAllocFunc *pAllocFunc = DSS::AllocFunc);
    ~DSS();
    /*! \brief 
            �洢����
        \param fileRW
            �ļ���д�ࣨдģʽ��
        \return 
            �� SaveResult */
    DSSResult Save(DSSFileBase *pFileRW);
    /*! \brief 
            �½�һ�����ݿ�
        \param typeName
            ������
        \param pOut
            �������ݿ�ָ��
        \return 
            �������ݿ�������ʧ�ܷ�������Ϊ0 */
    DATAID CreateData(const DSSStr &typeName, DataInfo **pOut);
    /*! \brief 
            �½�һ�����ݿ�
        \param typeID
            ��������
        \param pOut
            �������ݿ�ָ��
        \return 
            �������ݿ�������ʧ�ܷ�������Ϊ0 */
    DATAID CreateData(TYPEID typeID, DataInfo **pOut);
    /*! \brief 
            ɾ��һ�����ݿ�

            ע�⣺����һ������ȫ�Ĳ��������ɾ��ĳ�����ݿ飬���ǲ���������ø����ݿ�Ľڵ�
            �����κδ��������ȷʵ��Ҫɾ��ĳ�����ݿ飬���ҽ����ø����ݿ�Ľڵ���Ϊ�սڵ㣬
            ����Խ���Ҫɾ�������ݿ�ȫ��ɾ���󱣴�DSS���ļ������´ζ�ȡʱ��Щ���õ��Ѿ���
            ɾ���Ľڵ�ᱻ��Ϊ�սڵ㡣���������ʹ�� DSSNode::Check ������ȫ��ʹ�ýڵ㡣
        \param id
            ���ݿ�����
        \return 
            �����Ƿ�ɹ�������false��ʾ������ݿ鲻���� */
    bool DeleteData(DATAID id);
    /*! \brief 
            �������
        \param id
            ���ݿ�����
        \return 
            ��������ָ�룬ʧ�ܷ���NULL */
    void *GetData(DATAID id);
    const void *GetData(DATAID id) const;
    /*! \brief 
            ������ݿ���Ϣ�ṹ
        \param id
            ���ݿ�����
        \return 
            �������ݿ���Ϣ�ṹָ�룬ʧ�ܷ���NULL */
    DataInfo *GetDataInfo(DATAID id);
    const DataInfo *GetDataInfo(DATAID id) const ;
    /*! \brief 
            ע��һ���µ���������
        \param typeName
            ��������
        \param dataSize
            ��������ռ���ֽ���
        \return 
            ����ID��ʧ�ܷ���0 */
    TYPEID RegisterType(const DSSStr &typeName, size_t dataSize);
    /*! \brief 
            ע��һ���µ���������
        \param typeName
            ��������
        \return 
            ����ID��ʧ�ܷ���0 */
    template <typename T> TYPEID RegisterType(const DSSStr &typeName) {
        return RegisterType(typeName, sizeof(T));
    }
    /*! \brief 
            ע��һ����������
        \param typeName
            ��������
        \return 
            ����������ʧ�ܷ���0 */
    bool UnRegisterType(TYPEID id);
    /*! \brief 
            �������������Ϣ�ṹ
        \param id
            ��������
        \return 
            ������Ϣ�ṹ��ʧ�ܷ���NULL */
    const TypeInfo *GetTypeInfo(TYPEID id) const;
    /*! \brief 
            �������������Ϣ�ṹ
        \param typeName
            ������
        \return 
            ������Ϣ�ṹ��ʧ�ܷ���NULL */
    const TypeInfo *GetTypeInfo(const DSSStr &typeName) const;
    /*! \brief 
            �����������
        \param typeName
            ������
        \return 
            ����������ʧ�ܷ���0 */
    TYPEID GetTypeID(const DSSStr &typeName) const;
    /*! \brief 
            ������ݵ�����
        \return 
            ���ص����� */
    DSSDataIterator GetDataIterator();
    /*! \brief 
            ��ø��ڵ�
        \return 
            ���ظ��ڵ� */
    DSSNode *GetRoot() { return m_pRoot.get(); }
    const DSSNode *GetRoot() const { return m_pRoot.get(); }
    /*! \brief 
            ��õ�ǰ���ݿ�����
        \return 
            �������� */
    size_t DataCount() const { return m_dataPool.size(); }
    /*! \brief 
            ��õ�ǰ�ڵ�����
        \return 
            �������� */
    size_t NodeCount() const { return m_nodeCount; }
    /*! \brief 
            �� DSSNode ��� () ���������*/
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
            �����ӽڵ�

            ����һ���µĽڵ���µ����ݿ飬�����½ڵ����������ݿ顣
        \param path
            ·��
        \param typeName
            ������
        \param autoCreate
            �Ƿ��Զ�����������ò������� true�������Ҫ����һ���м�ڵ㶼�����ڵ�·��ʱ����
            �Զ������м�ڵ�Ϊ�սڵ㡣
        \return 
            ���ر��������½ڵ�ָ�룬ʧ�ܷ���NULL */
    DSSNode *CreateChild(const DSSStr &path, const DSSStr &typeName, bool autoCreate);
    /*! \brief 
            �������������ӽڵ�

            ����һ���µĽڵ㣬���������ṩ�Ľڵ�����ݿ顣
        \param path
            ·��
        \param pReference
            ����Ŀ��ڵ㣬������� NULL���򴴽����ǿսڵ㡣
        \param autoCreate
            �Ƿ��Զ�����������ò������� true�������Ҫ����һ���м�ڵ㶼�����ڵ�·��ʱ����
            �Զ������м�ڵ�Ϊ�սڵ㡣
        \return 
            ���ر��������½ڵ�ָ�룬ʧ�ܷ���NULL */
    DSSNode *CreateChild(const DSSStr &path, const DSSNode *pReference, bool autoCreate);
    /*! \brief 
            ��ø��ڵ�
        \return 
            ���ظ��ڵ�ָ�� */
    DSSNode *GetParent() { return m_pDParent; }
    const DSSNode *GetParent() const { return m_pDParent; }
    /*! \brief 
            ����ӽڵ�
        \param path
            ·��
        \return 
            �����ӽڵ�ָ�� */
    DSSNode *GetChild(const DSSStr &path);
    const DSSNode *GetChild(const DSSStr &path) const;
    /*! \brief 
            ����ӽڵ�
        \param path
            ·��
        \return 
            ɾ���ɹ����� true�� ɾ��ʧ�ܷ���false */
    bool DeleteChild(const DSSStr &path);
    /*! \brief 
            ����ӽڵ���Ŀ
        \return 
            �ӽڵ���Ŀ */
    size_t ChildCount() const { return m_pChild.size(); }
    /*! \brief 
            ����ӽڵ�*/
    void ClearChild();
    /*! \brief 
            �������ָ��
        \return 
            ����ָ�� */
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
            ���������Ϣ�ṹָ��
        \return 
            ������Ϣ�ṹָ�� */
    DataInfo *GetDataInfo() { return m_pDFile->GetDataInfo(m_id); }
    const DataInfo *GetDataInfo() const { return m_pDFile->GetDataInfo(m_id); }
    /*! \brief 
            �����������
        \return 
            ��������*/
    DATAID GetDataID() const { return m_id; }
    /*! \brief 
            ���ڵ������Ƿ���Ч
        \return 
            �ڵ�������Ч���� false����Ч����true */
    bool Check();
    /*! \brief 
            ���ڵ��Ƿ���������
        \return 
            �������ݷ��� false�����������ݷ���true */
    bool Empty() const;
    /*! \brief 
            ��������

            ��սڵ�����
        \return 
            ���ص�ǰ�ڵ� */
    DSSNode *ResetData();
    /*! \brief 
            ��������
        \param pNode
            ���õ�ǰ���ݣ��ٸ��ݴ��ݽڵ�����ݿ�������Ϊ��ǰ�ڵ㴴��һ����ͬ���͵����ݿ� 
        \return 
            ���ص�ǰ�ڵ� */
    DSSNode *ResetData(DSSNode *pNode);
    /*! \brief 
            ��������
        \param pNode
            ���õ�ǰ���ݣ��ٸ��ݴ��ݵĽڵ�����������һ���µ����ݿ� 
        \return 
            �����ɹ����� true, ����ʧ�ܷ��� false */
    bool ResetData(const DSSStr &typeName);
    /*! \brief 
            �������ݿ�
        \param pNode
            ����ǰ�ڵ�����ݿ�ʹ��ݵĽڵ㽻�����ݿ�����
        \return 
            ���ص�ǰ�ڵ� */
    DSSNode *SwapData(DSSNode *pNode);
    /*! \brief 
            ת�����ݿ�
        \param pNode
            ɾ����ǰ�ڵ�����ݿ飬������Ľڵ�����תΪ��ǰ�ڵ�����ݣ�ԭ�ڵ���Ϊ�սڵ�
        \return 
            ���ص�ǰ�ڵ� */
    DSSNode *ReplaceData(DSSNode *pNode);
    /*! \brief 
            ����ӽڵ������
        \return 
            �����ӽڵ������ */
    DSSNodeChildIterator GetChildIterator();
    /*! \brief 
            ����ӽڵ�

            �ȼ��� GetChild
        \param path
            �ڵ�·��
        \return 
            �����ӽڵ�ָ�� */
    DSSNode *operator() (const DSSStr &path);
    const DSSNode *operator() (const DSSStr &path) const;
    /*! \brief 
            ����ӽڵ�

            �������ӽڵ㲻���ڣ������ autoCreate ѡ��������һ���յ��ӽڵ������·��
        \param path
            �ڵ�·��
        \param autoCreate
            �Ƿ��Զ�����������ò������� true�������Ҫ����һ���м�ڵ㶼�����ڵ�·��ʱ
            �����Զ������м�ڵ�Ϊ�սڵ㡣
        \return 
            �����ӽڵ�ָ�룬ʧ�ܷ��� NULL */
    DSSNode *operator() (const DSSStr &path, bool autoCreate);
    /*! \brief 
            ����ӽڵ�

            �������ӽڵ㲻���ڣ������ autoCreate ѡ��������һ��ָ�����͵�ĩβ�ӽڵ㣬
            ��������м�ڵ㣬���м�ڵ�ᱻ����Ϊ�սڵ㡣��������������ĩβ�ӽڵ����
            ���ͼ�飬��������� typeName ���������ϣ��������ĩβ�ӽڵ�����͡�
        \param path
            �ڵ�·��
        \param typeName
            ������
        \param autoCreate
            �Ƿ��Զ�����������ò������� true�������Ҫ����һ���м�ڵ㶼�����ڵ�·��ʱ��
            ���Զ������м�ڵ�Ϊ�սڵ㡣
        \return 
            �����ӽڵ�ָ�룬ʧ�ܷ��� NULL */
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
