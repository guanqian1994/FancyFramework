////////////////////////////////////////////////////////////////////////////////
/// @file  fcyType.h
/// @brief ����fancylib�и��ֻ����������͡�����ͨ�õĺ�
////////////////////////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////////////////////////
// ������������
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup fancy�������������
/// @brief fancy���еĻ����������Ͷ���
/// @{
typedef bool                fBool;   ///< @brief �߼���
typedef char                fChar;   ///< @brief �ַ���
typedef wchar_t             fCharW;  ///< @brief ���ַ�
typedef unsigned char       fByte;   ///< @brief �ֽ���
typedef short               fShort;  ///< @brief 16λ������
typedef unsigned short      fuShort; ///< @brief 16λ�޷��Ŷ�����
typedef int                 fInt;    ///< @brief 32λ����
typedef unsigned int        fuInt;   ///< @brief 32λ�޷�������
typedef __int64             fLong;   ///< @brief 64λ������
typedef unsigned __int64    fuLong;  ///< @brief 64λ�޷��ų�����
typedef float               fFloat;  ///< @brief ������
typedef double              fDouble; ///< @brief ˫���ȸ�����
typedef fChar*              fStr;    ///< @brief Cʽ�ַ���
typedef const fChar*        fcStr;   ///< @brief Cʽ�ַ�������
typedef fCharW*             fStrW;   ///< @brief Cʽ���ַ���
typedef const fCharW*       fcStrW;  ///< @brief Cʽ���ַ�������
typedef fByte*              fData;   ///< @brief �ڴ�����ָ��
typedef const fByte*        fcData;  ///< @brief �����ڴ�����ָ��
typedef fuLong              fLen;    ///< @brief ������
typedef fInt                fResult; ///< @brief Ԥ���巵��ֵ
                                     ///< @details
                                     /// fResult �������� \n
                                     ///   ����λ  ��     \n
                                     ///     0 - �ɹ�     \n
                                     ///     1 - ʧ��     \n
                                     ///   30-16 λ��     \n
                                     ///     ��������Ϊ0  \n
                                     ///   15-0  λ��     \n
                                     ///     ������������
/// @}

////////////////////////////////////////////////////////////////////////////////
// �궨��
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup fancy��궨��
/// @brief fancy���еĸ��ֺ궨��
/// @{

#ifndef NULL
/// @brief ��ָ��
#define NULL                0
#endif

/// @brief ǿ��������
#define FCYINLINE           __forceinline

/// @brief     ����ָ��
/// @param[in] x Ҫ���յ�ָ��
#define FCYSAFEDEL(x)    { delete (x); (x) = NULL;   }

/// @brief     ����ָ������
/// @param[in] x Ҫ���յ�����ָ��
#define FCYSAFEDELARR(x) { delete[] (x); (x) = NULL; }

/// @brief     �������ü����ӿ�
/// @param[in] x Ҫ���յĽӿ�
#define FCYSAFEKILL(x)   { if(x){ (x)->Release(); (x)=NULL; } }
/// @}

////////////////////////////////////////////////////////////////////////////////
// ����
////////////////////////////////////////////////////////////////////////////////
/// @brief     �ж�fResult�Ƿ�ɹ�
/// @param[in] fr Ҫ�жϵķ���ֵ
#define FCYOK(fr)     (((fResult)(fr)) >= 0)

/// @brief     �ж�fResult�Ƿ�ʧ��
/// @param[in] fr Ҫ�жϵķ���ֵ
#define FCYFAILED(fr) (((fResult)(fr)) <  0)

/// @brief ����һ��fResult����
/// @param[in] code ����ʵ�岿��
#define FCYMAKEERR(code)           ((fResult) (0x80000000 | ((fuInt)(code))))

/// @brief          ����һ��fResult����ֵ
/// @param[in] sev  ���س̶ȣ�0=�ɹ���1=ʧ��
/// @param[in] code ����ʵ�岿��
#define FCYMAKERET(sev,code)       ((fResult) (((fuInt)(sev)<<31) | ((fuInt)(code))))

/// @brief          ����һ��fResult����ֵ
/// @param[in] sev  ���س̶ȣ�0=�ɹ���1=ʧ��
/// @param[in] rsv  ����ֵ��Ĭ��ȡ0
/// @param[in] desc ��������
#define FCYMAKERETEX(sev,rsv,desc) ((fResult) (((fuInt)(sev)<<31) | ((fuInt)(rsv)<<16) | ((fuInt)(desc))))

/// @brief     ���ش�������
/// @param[in] fr Ҫ����ķ���ֵ
#define FCYRESULT_CODE(fr)     ((fr) & 0xFFFF)

/// @brief     ���ش�����ֵ
/// @param[in] fr Ҫ����ķ���ֵ
#define FCYRESULT_RSV(fr)      (((fr) >> 16) & 0x7FFF)

/// @brief     ���ش������س̶�
/// @param[in] fr Ҫ����ķ���ֵ
/// @return    0=�ɹ��� 1=ʧ��
#define FCYRESULT_SEVERITY(fr) (((fr) >> 31) & 0x1)

////////////////////////////////////////////////////////////////////////////////
// ��������
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup fancy��������ֵ
/// @brief fancy���еĳ�������
/// @note  ����FCYRESULT_RSV����ֵΪ0ʱ������ʾ��������
/// @{

#define FCYERR_OK               ((fResult)0)   ///< @brief ��������ֵ
#define FCYERR_UNKNOWN          FCYMAKEERR(0)  ///< @brief δ֪����ֵ
#define FCYERR_INTERNALERR      FCYMAKEERR(1)  ///< @brief �ڲ�����
                                               ///< @details ͨ����ʾAPI����ʧ��
#define FCYERR_ILLEGAL          FCYMAKEERR(2)  ///< @brief ��Ч����
#define FCYERR_NOTIMPL          FCYMAKEERR(3)  ///< @brief δʵ��
#define FCYERR_NOTSUPPORT       FCYMAKEERR(4)  ///< @brief ��֧��
#define FCYERR_INVAILDDATA      FCYMAKEERR(5)  ///< @brief ��Ч����
#define FCYERR_INVAILDPARAM     FCYMAKEERR(6)  ///< @brief ��Ч����
#define FCYERR_INVAILDVERSION   FCYMAKEERR(7)  ///< @brief ��Ч�汾
#define FCYERR_OBJNOTEXSIT      FCYMAKEERR(8)  ///< @brief ���󲻴���
#define FCYERR_OBJEXSITED       FCYMAKEERR(9)  ///< @brief �����Ѵ���
#define FCYERR_OUTOFRANGE       FCYMAKEERR(10) ///< @brief ������Χ
                                               ///< @details �ļ���������ʵ����β��Խ��
#define FCYERR_OUTOFMEM         FCYMAKEERR(11) ///< @brief �ڴ治��

/// @}