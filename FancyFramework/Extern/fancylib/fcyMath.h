////////////////////////////////////////////////////////////////////////////////
/// @file  fcyMath.h
/// @brief ��ѧ�⣬������ѧ��ؽṹ
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyType.h"

#include <cmath>

#define FCYMAX(a,b) (((a)>(b))?(a):(b))
#define FCYMIN(a,b) (((a)<(b))?(a):(b))

/// @addtogroup fancy��ѧ��
/// @brief �ṩ��ѧ����֧��
/// @note ��������˵�����Ƕȵ�λ��Ϊ����
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief 2D����
////////////////////////////////////////////////////////////////////////////////
class fcyVec2
{
public:
	fFloat x; ///< @brief x����
	fFloat y; ///< @brief y����
public: // ���캯��
	fcyVec2()
		: x(0.f), y(0.f) {}
	/// @brief     ���캯��
	/// @param[in] X x����
	/// @param[in] Y y����
	fcyVec2(fFloat X, fFloat Y)
		: x(X), y(Y) {}
	/// @brief     ���캯������data[0]~data[1]ȡ������ֵ
	/// @warning   ����ȫ�ĺ���
	/// @param[in] data ��������ָ��
	fcyVec2(fFloat *data)
		: x(data[0]), y(data[1]) {}
public: // ���������
	/// @brief 2D�������
	fBool operator==(const fcyVec2& right)const
	{
		return (x == right.x && y == right.y);
	}
	/// @brief 2D��������
	fBool operator!=(const fcyVec2& right)const
	{
		return (x != right.x || y != right.y);
	}
	/// @brief 2D�������
	fcyVec2 operator+(const fcyVec2& right)const
	{
		return fcyVec2(x + right.x, y + right.y);
	};
	/// @brief 2D�����Լ�
	fcyVec2& operator+=(const fcyVec2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	};
	/// @brief 2D�������
	fcyVec2 operator-(const fcyVec2& right)const
	{
		return fcyVec2(x - right.x, y - right.y);
	};
	/// @brief 2D�����Լ�
	fcyVec2& operator-=(const fcyVec2& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	};
	/// @brief 2D��������
	fcyVec2 operator*(fFloat right)const
	{
		return fcyVec2(x * right, y * right);
	};
	/// @brief 2D�������ˣ�������
	fcyVec2 operator/(fFloat right)const
	{
		return fcyVec2(x / right, y / right);
	};
	/// @brief 2D����������
	fcyVec2& operator*=(fFloat right)
	{
		x = x * right;
		y = y * right;
		return *this;
	};
	/// @brief 2D���������ˣ�������
	fcyVec2& operator/=(fFloat right)
	{
		x = x / right;
		y = y / right;
		return *this;
	};
	/// @brief 2D�������
	fFloat operator*(const fcyVec2& right)const
	{
		return x * right.x + y * right.y;
	}
	/// @brief ȡ��
	fcyVec2 operator-()const
	{
		return fcyVec2(-x, -y);
	};
public: // ����
	// ����
	/// @brief ������ֵ
	void Set(fFloat X,fFloat Y)
	{
		x = X; y = Y;
	}
	/// @brief ƽ����
	fFloat Cross(const fcyVec2& right)const
	{
		return  x * right.y - right.x * y;
	};
	/// @brief �淶������
	void Normalize()
	{
		fFloat mode = sqrt( x * x +  y * y );
		if(mode != 0)
		{
			x /= mode;
			y /= mode;
		}
	};
	/// @brief ���ع淶������
	fcyVec2 GetNormalize()const
	{
		fFloat mode=sqrt( x *  x +  y *  y);
		if(mode != 0)
			return fcyVec2(x / mode, y / mode);
		else
			return fcyVec2();
	};
	/// @brief ��ģ
	fFloat Length()const
	{
		return sqrt( x*x + y*y );
	}
	/// @brief ��ģ��ƽ��
	fFloat Length2()const
	{
		return ( x*x + y*y );
	}
	/// @brief     ��ʱ����ת
	/// @param[in] angle ��ת�Ƕ�
	void Rotation(fFloat angle)
	{
		fFloat s = sin(angle),
		       c = cos(angle);
		fFloat tx = x*c - y*s,
		       ty = x*s + y*c;
		x = tx;
		y = ty;
	}
	/// @brief     ��ʱ����ת
	/// @note      ����������ת���������Ǻ�������
	/// @param[in] s Sinֵ(=sin(angle))
	/// @param[in] c Cosֵ(=cos(angle))
	void RotationSC(fFloat s, fFloat c)
	{
		fFloat tx = x*c - y*s,
			ty = x*s + y*c;
		x = tx; y = ty;
	}
	/// @brief ������x��ļн�
	fFloat CalcuAngle()
	{
		return atan2(y,x);
	}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 3D����
////////////////////////////////////////////////////////////////////////////////
class fcyVec3
{
public:
	fFloat x; ///< @brief x����
	fFloat y; ///< @brief y����
	fFloat z; ///< @brief z����
public: // ���캯��
	fcyVec3()
		: x(0.f), y(0.f), z(0.f) {}
	/// @brief     ���캯��
	/// @param[in] X x����
	/// @param[in] Y y����
	/// @param[in] Z z����
	fcyVec3(fFloat X, fFloat Y, fFloat Z)
		: x(X), y(Y), z(Z) {}
	/// @brief     ���캯������data[0]~data[2]ȡ������ֵ
	/// @warning   ����ȫ�ĺ���
	/// @param[in] data ��������ָ��
	fcyVec3(fFloat *data)
		: x(data[0]), y(data[1]), z(data[2]) {}
public: // ���������
	/// @brief 3D�������
	fBool operator==(const fcyVec3& right)const
	{
		return (x == right.x && y == right.y && z == right.z);
	}
	/// @brief 3D��������
	fBool operator!=(const fcyVec3& right)const
	{
		return (x != right.x || y != right.y || z != right.z);
	}
	/// @brief 3D�������
	fcyVec3 operator+(const fcyVec3& right)const
	{
		return fcyVec3(
			x + right.x,
			y + right.y,
			z + right.z
			);
	};
	/// @brief 3D�����Լ�
	fcyVec3& operator+=(const fcyVec3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	};
	/// @brief 3D�������
	fcyVec3 operator-(const fcyVec3& right)const
	{
		return fcyVec3(
			x - right.x,
			y - right.y, 
			z - right.z
			);
	};
	/// @brief 3D�����Լ�
	fcyVec3& operator-=(const fcyVec3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	};
	/// @brief 3D��������
	fcyVec3 operator*(fFloat right)const
	{
		return fcyVec3(
			x * right,
			y * right,
			z * right
			);
	};
	/// @brief 3D�������ˣ�������
	fcyVec3 operator/(fFloat right)const
	{
		return fcyVec3(
			x / right,
			y / right,
			z / right
			);
	};
	/// @brief 3D����������
	fcyVec3& operator*=(fFloat right)
	{
		x = x * right;
		y = y * right;
		z = z * right;
		return *this;
	};
	/// @brief 3D���������ˣ�������
	fcyVec3& operator/=(fFloat right)
	{
		x = x / right;
		y = y / right;
		z = z / right;
		return *this;
	};
	/// @brief 3D�������
	fFloat operator*(const fcyVec3& right)const
	{
		return x * right.x + y * right.y + z * right.z;
	};
	/// @brief ȡ��
	fcyVec3 operator-()const
	{
		return fcyVec3(-x, -y, -z);
	};
public: // ����
	// ����
	/// @brief ��ֵ��ֵ
	void Set(fFloat X, fFloat Y, fFloat Z)
	{
		x = X; y = Y; z = Z;
	}
	/// @brief �������
	fcyVec3 Cross(const fcyVec3& right)const
	{
		return fcyVec3(
			y*right.z -  z*right.y,
			z*right.x -  x*right.z,
			x*right.y -  y*right.x);
	};
	/// @brief �淶������
	void Normalize()
	{
		fFloat mode = sqrt( x*x +  y*y +  z*z );
		if(mode != 0)
		{
			x/=mode;
			y/=mode;
			z/=mode;
		}
	};
	/// @brief ���ع淶������
	fcyVec3 GetNormalize()const
	{
		fFloat mode = sqrt( x*x + y*y + z*z );
		if(mode != 0)
			return fcyVec3( x / mode, y / mode, z / mode);
		else
			return fcyVec3();
	};
	/// @brief ȡģ
	fFloat Length()const
	{
		return sqrt( x*x + y*y + z*z );
	};
	/// @brief ȡģ��ƽ��
	fFloat Length2()const
	{
		return x*x + y*y + z*z;
	}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 4D����
////////////////////////////////////////////////////////////////////////////////
class fcyVec4
{
public:
	fFloat x; ///< @brief x����
	fFloat y; ///< @brief y����
	fFloat z; ///< @brief z����
	fFloat w; ///< @brief w����
public: // ���캯��
	fcyVec4()
		: x(0.f), y(0.f), z(0.f), w(0.f) 
	{
		this->w = 10;
	}
	/// @brief     ���캯��
	/// @param[in] X x����
	/// @param[in] Y y����
	/// @param[in] Z z����
	/// @param[in] W w����
	fcyVec4(fFloat X, fFloat Y, fFloat Z, fFloat W)
		: x(X), y(Y), z(Z), w(W) {}
	/// @brief     ���캯������data[0]~data[3]ȡ������ֵ
	/// @warning   ����ȫ�ĺ���
	/// @param[in] data ��������ָ��
	fcyVec4(fFloat *data)
		: x(data[0]), y(data[1]), z(data[2]), w(data[3]) {}
public: // ���������
	/// @brief 4D�������
	fBool operator==(const fcyVec4& right)const
	{
		return (x == right.x && y == right.y && z == right.z && w == right.w);
	}
	/// @brief 4D��������
	fBool operator!=(const fcyVec4& right)const
	{
		return (x != right.x || y != right.y || z != right.z || w != right.w);
	}
	/// @brief 4D�������
	fcyVec4 operator+(const fcyVec4& right)const
	{
		return fcyVec4(
			x + right.x,
			y + right.y,
			z + right.z,
			w + right.w
			);
	};
	/// @brief 4D�����Լ�
	fcyVec4& operator+=(const fcyVec4& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		w += right.w;
		return *this;
	};
	/// @brief 4D�������
	fcyVec4 operator-(const fcyVec4& right)const
	{
		return fcyVec4(
			x - right.x,
			y - right.y, 
			z - right.z,
			w - right.w
			);
	};
	/// @brief 4D�����Լ�
	fcyVec4& operator-=(const fcyVec4& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		w -= right.w;
		return *this;
	};
	/// @brief 4D��������
	fcyVec4 operator*(fFloat right)const
	{
		return fcyVec4(
			x * right,
			y * right,
			z * right,
			w * right
			);
	};
	/// @brief 4D�������ˣ�������
	fcyVec4 operator/(fFloat right)const
	{
		return fcyVec4(
			x / right,
			y / right,
			z / right,
			w / right
			);
	};
	/// @brief 4D����������
	fcyVec4& operator*=(fFloat right)
	{
		x = x * right;
		y = y * right;
		z = z * right;
		w = w * right;
		return *this;
	};
	/// @brief 4D���������ˣ�������
	fcyVec4& operator/=(fFloat right)
	{
		x = x / right;
		y = y / right;
		z = z / right;
		w = w / right;
		return *this;
	};
	/// @brief ȡ��
	fcyVec4 operator-()const
	{
		return fcyVec4(-x, -y, -z, -w);
	};
public: // ����
	/// @brief ��ֵ��ֵ
	void Set(fFloat X, fFloat Y, fFloat Z)
	{
		x = X; y = Y; z = Z;
	}
	/// @brief ��ֵ��ֵ
	void Set(fFloat X, fFloat Y, fFloat Z, fFloat W)
	{
		x = X; y = Y; z = Z; w = W;
	}
	/// @brief �淶������
	void Normalize()
	{
		fFloat mode = sqrt( x*x +  y*y +  z*z + w*w );
		if(mode != 0)
		{
			x/=mode;
			y/=mode;
			z/=mode;
			w/=mode;
		}
	};
	/// @brief ���ع淶������
	fcyVec4 GetNormalize()const
	{
		fFloat mode = sqrt( x*x + y*y + z*z + w*w );
		if(mode != 0)
			return fcyVec4( x / mode, y / mode, z / mode, w / mode );
		else
			return fcyVec4();
	};
	/// @brief ȡģ
	fFloat Length()const
	{
		return sqrt( x*x + y*y + z*z + w*w );
	};
	/// @brief ȡģ��ƽ��
	fFloat Length2()const
	{
		return x*x + y*y + z*z + w*w;
	}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 4x4����
/// @note  ��ʽ����
////////////////////////////////////////////////////////////////////////////////
class fcyMatrix4
{
public:
	union
	{
		struct
		{
			fFloat _11, _12, _13, _14;
			fFloat _21, _22, _23, _24;
			fFloat _31, _32, _33, _34;
			fFloat _41, _42, _43, _44;
		};
		fFloat m[4][4];  /// @brief ����������
	};
public:
	/// @brief ��ʼ��Ϊ��λ����
	fcyMatrix4()
	{
		_11=1.f;  _12=0.f;  _13=0.f;  _14=0.f;
		_21=0.f;  _22=1.f;  _23=0.f;  _24=0.f;
		_31=0.f;  _32=0.f;  _33=1.f;  _34=0.f;
		_41=0.f;  _42=0.f;  _43=0.f;  _44=1.f;
	};
	/// @brief ʹ���Զ����ֵ��ʼ������
	fcyMatrix4(fFloat m11,fFloat m12,fFloat m13,fFloat m14,
		fFloat m21,fFloat m22,fFloat m23,fFloat m24,
		fFloat m31,fFloat m32,fFloat m33,fFloat m34,
		fFloat m41,fFloat m42,fFloat m43,fFloat m44)
	{
		_11=m11;  _12=m12;  _13=m13;  _14=m14;
		_21=m21;  _22=m22;  _23=m23;  _24=m24;
		_31=m31;  _32=m32;  _33=m33;  _34=m34;
		_41=m41;  _42=m42;  _43=m43;  _44=m44;
	};
public:
	/// @brief ������ֵ
	void Set(fFloat m11,fFloat m12,fFloat m13,fFloat m14,
		fFloat m21,fFloat m22,fFloat m23,fFloat m24,
		fFloat m31,fFloat m32,fFloat m33,fFloat m34,
		fFloat m41,fFloat m42,fFloat m43,fFloat m44)
	{
		_11=m11;  _12=m12;  _13=m13;  _14=m14;
		_21=m21;  _22=m22;  _23=m23;  _24=m24;
		_31=m31;  _32=m32;  _33=m33;  _34=m34;
		_41=m41;  _42=m42;  _43=m43;  _44=m44;
	};
public:
	/// @brief �������
	fcyMatrix4 operator+(const fcyMatrix4& right)const
	{
		return fcyMatrix4(
			_11 + right._11, _12 + right._12, _13 + right._13, _14 + right._14,
			_21 + right._21, _22 + right._22, _23 + right._23, _24 + right._24,
			_31 + right._31, _32 + right._32, _33 + right._33, _34 + right._34,
			_41 + right._41, _42 + right._42, _43 + right._43, _44 + right._44
			);
	};
	/// @brief �����Լ�
	fcyMatrix4& operator+=(const fcyMatrix4& right)
	{
		_11 += right._11; _12 += right._12; _13 += right._13; _14 += right._14;
		_21 += right._21; _22 += right._22; _23 += right._23; _24 += right._24;
		_31 += right._31; _32 += right._32; _33 += right._33; _34 += right._34;
		_41 += right._41; _42 += right._42; _43 += right._43; _44 += right._44;

		return *this;
	};
	/// @brief �������
	fcyMatrix4 operator-(const fcyMatrix4& right)const
	{
		return fcyMatrix4(
			_11 - right._11, _12 - right._12, _13 - right._13, _14 - right._14,
			_21 - right._21, _22 - right._22, _23 - right._23, _24 - right._24,
			_31 - right._31, _32 - right._32, _33 - right._33, _34 - right._34,
			_41 - right._41, _42 - right._42, _43 - right._43, _44 - right._44
			);
	};
	/// @brief �����Լ�
	fcyMatrix4& operator-=(const fcyMatrix4& right)
	{
		_11 -= right._11; _12 -= right._12; _13 -= right._13; _14 -= right._14;
		_21 -= right._21; _22 -= right._22; _23 -= right._23; _24 -= right._24;
		_31 -= right._31; _32 -= right._32; _33 -= right._33; _34 -= right._34;
		_41 -= right._41; _42 -= right._42; _43 -= right._43; _44 -= right._44;

		return *this;
	};
	/// @brief �������
	fcyMatrix4 operator*(const fcyMatrix4& right)const
	{
		return fcyMatrix4(
			_11 * right._11 + _12 * right._21 + _13 * right._31 + _14 * right._41,
			_11 * right._12 + _12 * right._22 + _13 * right._32 + _14 * right._42,
			_11 * right._13 + _12 * right._23 + _13 * right._33 + _14 * right._43,
			_11 * right._14 + _12 * right._24 + _13 * right._34 + _14 * right._44,

			_21 * right._11 + _22 * right._21 + _23 * right._31 + _24 * right._41,
			_21 * right._12 + _22 * right._22 + _23 * right._32 + _24 * right._42,
			_21 * right._13 + _22 * right._23 + _23 * right._33 + _24 * right._43,
			_21 * right._14 + _22 * right._24 + _23 * right._34 + _24 * right._44,

			_31 * right._11 + _32 * right._21 + _33 * right._31 + _34 * right._41,
			_31 * right._12 + _32 * right._22 + _33 * right._32 + _34 * right._42,
			_31 * right._13 + _32 * right._23 + _33 * right._33 + _34 * right._43,
			_31 * right._14 + _32 * right._24 + _33 * right._34 + _34 * right._44,

			_41 * right._11 + _42 * right._21 + _43 * right._31 + _44 * right._41,
			_41 * right._12 + _42 * right._22 + _43 * right._32 + _44 * right._42,
			_41 * right._13 + _42 * right._23 + _43 * right._33 + _44 * right._43,
			_41 * right._14 + _42 * right._24 + _43 * right._34 + _44 * right._44
			);
	};
	/// @brief ��������
	fcyMatrix4 operator*(const fFloat& right)const
	{
		return fcyMatrix4(_11 * right,_12 * right,_13 * right,_14 * right,
			_21 * right,_22 * right,_23 * right,_24 * right,
			_31 * right,_32 * right,_33 * right,_34 * right,
			_41 * right,_42 * right,_43 * right,_44 * right );
	};
	/// @brief �����Գ�
	fcyMatrix4& operator*=(const fcyMatrix4& right)
	{
		_11 = _11 * right._11 + _12 * right._21 + _13 * right._31 + _14 * right._41;
		_12 = _11 * right._12 + _12 * right._22 + _13 * right._32 + _14 * right._42;
		_13 = _11 * right._13 + _12 * right._23 + _13 * right._33 + _14 * right._43;
		_14 = _11 * right._14 + _12 * right._24 + _13 * right._34 + _14 * right._44;

		_21 = _21 * right._11 + _22 * right._21 + _23 * right._31 + _24 * right._41;
		_22 = _21 * right._12 + _22 * right._22 + _23 * right._32 + _24 * right._42;
		_23 = _21 * right._13 + _22 * right._23 + _23 * right._33 + _24 * right._43;
		_24 = _21 * right._14 + _22 * right._24 + _23 * right._34 + _24 * right._44;

		_31 = _31 * right._11 + _32 * right._21 + _33 * right._31 + _34 * right._41;
		_32 = _31 * right._12 + _32 * right._22 + _33 * right._32 + _34 * right._42;
		_33 = _31 * right._13 + _32 * right._23 + _33 * right._33 + _34 * right._43;
		_34 = _31 * right._14 + _32 * right._24 + _33 * right._34 + _34 * right._44;

		_41 = _41 * right._11 + _42 * right._21 + _43 * right._31 + _44 * right._41;
		_42 = _41 * right._12 + _42 * right._22 + _43 * right._32 + _44 * right._42;
		_43 = _41 * right._13 + _42 * right._23 + _43 * right._33 + _44 * right._43;
		_44 = _41 * right._14 + _42 * right._24 + _43 * right._34 + _44 * right._44;

		return *this;
	};
public:
	/// @brief   ��������
	/// @note    ���ض��ľ�����п����������
	/// @warning �����������Ͻ�3*3��ת���ֵ�3������Ϊ��λ��������������ֱʱ���ô˷�
	void FastInvert()
	{
		/* 
		������
			���Ͻ�3*3 = ԭ���Ͻ�3*3 ת��
			���½�1*3 = ԭ���½�1*3 �����෴���������Ͻ�3*3��ת�ú�
			ʣ�²���
		*/
		Set(
			_11, _21, _31, 0.f,
			_12, _22, _32, 0.f,
			_13, _23, _33, 0.f,
			-_41*_11-_42*_12-_43*_13,
			-_41*_21-_42*_22-_43*_23,
			- _41*_31-_42*_32-_43*_33,
			1.f
			);
	};
	/// @brief ת��
	void Transpose()
	{
		Set(
			_11,_21,_31,_41,
			_12,_22,_32,_42,
			_13,_23,_33,_43,
			_14,_24,_34,_44
			);
	};
public:
	/// @brief ���ص�λ����
	static fcyMatrix4 GetIdentity()
	{
		return fcyMatrix4(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	};
	/// @brief ����������ϵ��������
	static fcyMatrix4 GetSwaper()
	{
		return fcyMatrix4(
			1.f, 0.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	};
	/// @brief     ����ƽ�ƾ���
	/// @param[in] vec ƽ����
	static fcyMatrix4 GetTranslateMatrix(const fcyVec3& vec)
	{
		return fcyMatrix4(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			vec.x, vec.y, vec.z, 1.f
			);
	};
	/// @brief     �������ž���
	/// @param[in] value ͳһ������
	static fcyMatrix4 GetScaleMatrix(const fFloat value)
	{
		return fcyMatrix4(
			value, 0.f, 0.f, 0.f,
			0.f, value, 0.f, 0.f,
			0.f, 0.f, value, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	};
	/// @brief     �������ž���
	/// @param[in] vec ������
	static fcyMatrix4 GetScaleMatrix(const fcyVec3& vec)
	{
		return fcyMatrix4(
			vec.x, 0.f, 0.f, 0.f,
			0.f, vec.y, 0.f, 0.f,
			0.f, 0.f, vec.z, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	}
	/// @brief     ������X����ת����
	/// @param[in] angle ��ת�Ƕ�
	static fcyMatrix4 GetRotateX(const fFloat angle)
	{
		fFloat angle_sin = sin(angle),
			angle_cos = cos(angle);

		return fcyMatrix4(
			1.f, 0.f, 0.f, 0.f,
			0.f, angle_cos, angle_sin, 0.f,
			0.f, -angle_sin, angle_cos, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	};
	/// @brief     ������Y����ת����
	/// @param[in] angle ��ת�Ƕ�
	static fcyMatrix4 GetRotateY(const fFloat angle)
	{
		fFloat angle_sin = sin(angle),
			angle_cos = cos(angle);

		return fcyMatrix4(
			angle_cos, 0.f, -angle_sin, 0.f,
			0.f, 1.f, 0.f, 0.f,
			angle_sin, 0.f, angle_cos, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	};
	/// @brief     ������Z����ת����
	/// @param[in] angle ��ת�Ƕ�
	static fcyMatrix4 GetRotateZ(const fFloat angle)
	{
		fFloat angle_sin = sin(angle),
			angle_cos = cos(angle);

		return fcyMatrix4(
			angle_cos, angle_sin, 0.f, 0.f,
			-angle_sin, angle_cos, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	};
	/// @brief     ������XYZ������ת����
	/// @param[in] yaw   �������� y ����ת�ĽǶ�
	/// @param[in] pitch �������� x ����ת�ĽǶ�
	/// @param[in] roll  ������� z ����ת�ĽǶ�
	static fcyMatrix4 GetRotationYawPitchRoll(
		const fFloat yaw,
		const fFloat pitch,
		const fFloat roll)
	{
		fFloat sin_x = sin(pitch);
		fFloat cos_x = cos(pitch);
		fFloat sin_y = sin(yaw);
		fFloat cos_y = cos(yaw);
		fFloat sin_z = sin(roll);
		fFloat cos_z = cos(roll);

		return fcyMatrix4(
			cos_y*cos_z, cos_y*sin_z, -sin_y, 0.f,
			sin_x*sin_y*cos_z - cos_x*sin_z, sin_x*sin_y*sin_z + cos_x*cos_z, sin_x*cos_y, 0.f,
			cos_x*sin_y*cos_z + sin_x*sin_z, cos_x*sin_y*sin_z - sin_x*cos_z, cos_x*cos_y, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	};
	/// @brief     ����ϵ ��������������ת����
	/// @param[in] axisRotation ��ת����
	/// @param[in] angle        �Ƕ�
	static fcyMatrix4 GetRotationAxisRH(
		const fcyVec3& axisRotation,  
		const fFloat angle)
	{
		fFloat angle_sin = sin(angle),
			angle_cos = cos(angle);

		return fcyMatrix4(
			angle_cos + ( 1 - angle_cos ) * axisRotation.x * axisRotation.x , 
			( 1 - angle_cos ) * axisRotation.x * axisRotation.y + axisRotation.z * angle_sin , 
			( 1 - angle_cos ) * axisRotation.x * axisRotation.z - axisRotation.y * angle_sin  , 
			0,

			( 1 - angle_cos ) * axisRotation.x * axisRotation.y - axisRotation.z * angle_sin , 
			angle_cos + ( 1 - angle_cos ) * axisRotation.y * axisRotation.y ,
			( 1 - angle_cos ) * axisRotation.y * axisRotation.z + axisRotation.x * angle_sin ,
			0,

			( 1 - angle_cos ) * axisRotation.x * axisRotation.z + axisRotation.y * angle_sin ,
			( 1 - angle_cos ) * axisRotation.y * axisRotation.z - axisRotation.x * angle_sin  , 
			angle_cos + ( 1 - angle_cos ) * axisRotation.z * axisRotation.z , 
			0,

			0 ,	0 ,	0 ,	1
			);
	};
	/// @brief     ����ϵ ��������������ת����
	/// @param[in] axisRotation ��ת����
	/// @param[in] angle        �Ƕ�
	static fcyMatrix4 GetRotationAxisLH(
		const fcyVec3& axisRotation,
		const fFloat angle)
	{
		fFloat angle_sin = sin(angle),
			angle_cos = cos(angle);

		return fcyMatrix4(
			angle_cos + ( 1 - angle_cos ) * axisRotation.x * axisRotation.x , 
			( 1 - angle_cos ) * axisRotation.x * axisRotation.y - axisRotation.z * angle_sin , 
			( 1 - angle_cos ) * axisRotation.x * axisRotation.z + axisRotation.y * angle_sin  , 
			0,

			( 1 - angle_cos ) * axisRotation.x * axisRotation.y + axisRotation.z * angle_sin , 
			angle_cos + ( 1 - angle_cos ) * axisRotation.y * axisRotation.y ,
			( 1 - angle_cos ) * axisRotation.y * axisRotation.z - axisRotation.x * angle_sin ,
			0,

			( 1 - angle_cos ) * axisRotation.x * axisRotation.z - axisRotation.y * angle_sin ,
			( 1 - angle_cos ) * axisRotation.y * axisRotation.z + axisRotation.x * angle_sin  , 
			angle_cos + ( 1 - angle_cos ) * axisRotation.z * axisRotation.z , 
			0,

			0 ,	0 ,	0 ,	1
			);
	};
	/// @brief     ����ϵ ���ع۲�ĳ��ľ���
	/// @param[in] eye    �۾�λ��
	/// @param[in] lookat �۲�λ��
	/// @param[in] up     �Ϸ�����
	static fcyMatrix4 GetLookAtLH(const fcyVec3& eye, const fcyVec3& lookat, const fcyVec3& up)
	{
		fcyVec3 zaxis(lookat - eye);
		zaxis.Normalize();
		fcyVec3 xaxis = up.Cross(zaxis);
		xaxis.Normalize();
		fcyVec3 yaxis = zaxis.Cross(xaxis);

		return fcyMatrix4(
			xaxis.x     ,  yaxis.x    ,  zaxis.x    ,  0.f,
			xaxis.y     ,  yaxis.y    ,  zaxis.y    ,  0.f,
			xaxis.z     ,  yaxis.z    ,  zaxis.z    ,  0.f,
			-(xaxis*eye), -(yaxis*eye), -(zaxis*eye),  1.f
			);
	};
	/// @brief     ����ϵ ���ع۲�ĳ��ľ���
	/// @param[in] eye    �۾�λ��
	/// @param[in] lookat �۲�λ��
	/// @param[in] up     �Ϸ�����
	static fcyMatrix4 GetLookAtRH(const fcyVec3& eye, const fcyVec3& lookat, const fcyVec3& up)
	{
		fcyVec3 xaxis(up);
		xaxis.Normalize();
		fcyVec3 zaxis(eye - lookat);
		zaxis.Normalize();
		xaxis = xaxis.Cross(zaxis);
		fcyVec3 yaxis = zaxis.Cross(xaxis);

		return fcyMatrix4(
			xaxis.x, yaxis.x, zaxis.x ,0.f ,
			xaxis.y, yaxis.y, zaxis.y ,0.f ,
			xaxis.z, yaxis.z, zaxis.z ,0.f ,
			-(xaxis*eye),-(yaxis*eye),-(zaxis*eye),1.f
			);
	};
	/// @brief     ����ϵ ������ͶӰ����
	/// @param[in] w         ������ӷ�Χ
	/// @param[in] h         ������ӷ�Χ
	/// @param[in] nearPlane �������
	/// @param[in] farPlane  ��Զ����
	static fcyMatrix4 GetOrthoLH(
		const fuInt w,
		const fuInt h,
		const fFloat nearPlane,
		const fFloat farPlane)
	{
		return fcyMatrix4(
			2.0f/w, 0.f, 0.f, 0.f,
			0.f, 2.0f/h, 0.f, 0.f,
			0.f, 0.f, 1.f /(farPlane-nearPlane), 0.f,
			0.f, 0.f, nearPlane/(nearPlane - farPlane), 1.f
			);
	};
	/// @brief     ����ϵ ������ͶӰ����
	/// @param[in] w         ������ӷ�Χ
	/// @param[in] h         ������ӷ�Χ
	/// @param[in] nearPlane �������
	/// @param[in] farPlane  ��Զ����
	static fcyMatrix4 GetOrthoRH(
		const fuInt w,
		const fuInt h,
		const fFloat nearPlane,
		const fFloat farPlane)
	{
		return fcyMatrix4(
			2.0f/w, 0.f, 0.f, 0.f,
			0.f, 2.0f/h, 0.f, 0.f,
			0.f, 0.f, 1.f /(nearPlane - farPlane), 0.f,
			0.f, 0.f, nearPlane/(nearPlane - farPlane), 1.f
			);
	};
	/// @brief     ����ϵ ����͸��ͶӰ����
	/// @param[in] ration    ��Ļ�ݺ�ȣ����ߣ�
	/// @param[in] fovY      ������Ұ��Χ�����ȣ�
	/// @param[in] nearPlane �������
	/// @param[in] farPlane  ��Զ����
	static fcyMatrix4 GetPespctiveLH(
		const fFloat ration,
		const fFloat fovY,
		const fFloat nearPlane,
		const fFloat farPlane)
	{
		fFloat t = 1.f / tan(fovY*0.5f);

		return fcyMatrix4(
			t/ration, 0.f, 0.f, 0.f,
			0.f, t, 0.f, 0.f,
			0.f, 0.f, farPlane/(farPlane-nearPlane), 1.f,
			0.f, 0.f, -( nearPlane*farPlane )/( farPlane-nearPlane ), 0.f
			);
	};
	/// @brief     ����ϵ ����͸��ͶӰ����
	/// @param[in] ration    ��Ļ�ݺ�ȣ����ߣ�
	/// @param[in] fovY      ������Ұ��Χ�����ȣ�
	/// @param[in] nearPlane �������
	/// @param[in] farPlane  ��Զ����
	static fcyMatrix4 GetPespctiveRH(
		const fFloat ration,
		const fFloat fovY,
		const fFloat nearPlane,
		const fFloat farPlane)
	{
		fFloat t = 1.f / tan(fovY*0.5f);

		return fcyMatrix4(
			t/ration, 0.f, 0.f, 0.f,
			0.f, t, 0.f, 0.f,
			0.f, 0.f, farPlane/(nearPlane-farPlane), -1.f,
			0.f, 0.f, ( nearPlane*farPlane )/( nearPlane-farPlane),	0.f
			);
	};
	/// @brief     ����ϵ �����Զ�������ͶӰ����
	/// @param[in] l  �����Xֵ
	/// @param[in] r  ���Ҳ�Xֵ
	/// @param[in] b  ���·�Yֵ
	/// @param[in] t  ���Ϸ�Yֵ
	/// @param[in] zn �������
	/// @param[in] zf ��Զ����
	static fcyMatrix4 GetOrthoOffCenterLH(
		const fFloat l,
		const fFloat r,
		const fFloat b,
		const fFloat t,
		const fFloat zn,
		const fFloat zf)
	{
		return fcyMatrix4(
			2.f/(r-l)  , 0.f        , 0.f        , 0.f,
			0.f        , 2.f/(t-b)  , 0.f        , 0.f,
			0.f        , 0.f        , 1.f/(zf-zn), 0.f,
            (l+r)/(l-r), (t+b)/(b-t), zn/(zn-zf) , 1.f
			);
	};
	/// @brief     ����ϵ �����Զ�������ͶӰ����
	/// @param[in] l  �����Xֵ
	/// @param[in] r  ���Ҳ�Xֵ
	/// @param[in] b  ���·�Yֵ
	/// @param[in] t  ���Ϸ�Yֵ
	/// @param[in] zn �������
	/// @param[in] zf ��Զ����
	static fcyMatrix4 GetOrthoOffCenterRH(
		const fFloat l,
		const fFloat r,
		const fFloat b,
		const fFloat t,
		const fFloat zn,
		const fFloat zf)
	{
		return fcyMatrix4(
			2.f/(r-l)  , 0.f        , 0.f        , 0.f,
			0.f        , 2.f/(t-b)  , 0.f        , 0.f,
			0.f        , 0.f        , 1.f/(zn-zf), 0.f,
			(l+r)/(l-r), (t+b)/(b-t), zn/(zn-zf) , 1.f
			);
	};
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ��ɫֵ
////////////////////////////////////////////////////////////////////////////////
class fcyColor
{
public:
	union{
		fuInt argb;   ///< @brief ��ɫֵ
		struct
		{
			fByte b;
			fByte g;
			fByte r;
			fByte a;
		};
	};
public: // ���캯��
	/// @brief Ĭ�Ϲ��캯��������Alpha=255�ĺ�ɫ
	fcyColor()
		: argb(0xFF000000) {}
	/// @brief ʹ����ɫֵ������ɫ
	fcyColor(fuInt ARGB)
		: argb(ARGB) {}
	/// @brief ʹ��RGBֵ������ɫ��A=255
	/// @param[in] R ȡֵΪ[0,255]
	/// @param[in] G ȡֵΪ[0,255]
	/// @param[in] B ȡֵΪ[0,255]
	fcyColor(fInt R, fInt G, fInt B)
		: a(255), r((fByte)R), g((fByte)G), b((fByte)B) {}
	/// @brief ʹ��ARGBֵ������ɫ
	/// @param[in] A ȡֵΪ[0,255]
	/// @param[in] R ȡֵΪ[0,255]
	/// @param[in] G ȡֵΪ[0,255]
	/// @param[in] B ȡֵΪ[0,255]
	fcyColor(fInt A, fInt R, fInt G, fInt B)
		: a((fByte)A), r((fByte)R), g((fByte)G), b((fByte)B) {}
	/// @brief     ʹ��RGB����ֵ������ɫ
	/// @param[in] R ȡֵΪ[0,1]
	/// @param[in] G ȡֵΪ[0,1]
	/// @param[in] B ȡֵΪ[0,1]
	fcyColor(fDouble R, fDouble G, fDouble B)
		: a((fByte)255), r((fByte)(R * 255)), g((fByte)(G * 255)), b((fByte)(B * 255)) {}
	/// @brief     ʹ��RGB����ֵ������ɫ
	/// @param[in] A ȡֵΪ[0,1]
	/// @param[in] R ȡֵΪ[0,1]
	/// @param[in] G ȡֵΪ[0,1]
	/// @param[in] B ȡֵΪ[0,1]
	fcyColor(fDouble A, fDouble R, fDouble G, fDouble B)
		: a((fByte)(A * 255)), r((fByte)(R * 255)), g((fByte)(G * 255)), b((fByte)(B * 255)) {}
public: // ����
	/// @brief ������ֵ
	void Set(fByte A, fByte R, fByte G, fByte B)
	{
		a = A;
		r = R;
		g = G;
		b = B;
	}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ����
////////////////////////////////////////////////////////////////////////////////
class fcyRect
{
public:
	fcyVec2 a;  ///< @brief �������Ͻ�
	fcyVec2 b;  ///< @brief �������½�
public:
	fcyRect() {}
	/// @brief     ��������
	/// @param[in] A �������Ͻ�
	/// @param[in] B �������½�
	fcyRect(const fcyVec2& A, const fcyVec2& B)
		: a(A), b(B) {}
	/// @brief     ��������
	/// @param[in] x1 ���
	/// @param[in] y1 ����
	/// @param[in] x2 �ױ�
	/// @param[in] y2 �ұ�
	fcyRect(fFloat x1, fFloat y1, fFloat x2, fFloat y2)
		: a(x1,y1), b(x2,y2) {}
public:
	/// @brief ȡ���
	fFloat GetWidth()const
	{
		return fabs(a.x - b.x);
	}
	/// @brief ȡ�߶�
	fFloat GetHeight()const
	{
		return fabs(a.y - b.y);
	}
	/// @brief �Ƿ������
	/// @note  ���߽�
	fBool Contain(const fcyVec2& x)const
	{
		return (x.x>=a.x && x.x<=b.x && x.y>=a.y && x.y<=b.y);
	}
	/// @brief �Ƿ���Բ�ཻ
	/// @note  ������
	fBool Contain(const fcyVec2& x, fFloat R)const
	{
		return (x.x + R >= a.x && x.x - R <=b.x && x.y + R >=a.y && x.y - R <=b.y);
	}
	/// @brief ������ĵ�
	fcyVec2 GetCenter()const
	{
		return ((a+b)*0.5);
	}
	/// @brief      ���Ƿ��ཻ�����ཻ���ع�������
	/// @param[in]  Rect ���жϵľ���
	/// @param[out] pOut ������ཻ����
	fBool Intersect(const fcyRect& Rect, fcyRect* pOut)const
	{
		fcyRect tRet(
			FCYMAX(a.x, Rect.a.x),
			FCYMAX(a.y, Rect.a.y),
			FCYMIN(b.x, Rect.b.x),
			FCYMIN(b.y, Rect.b.y)
			);

		if(tRet.a.x <= tRet.b.x && tRet.a.y <= tRet.b.y)
		{
			// �ཻ
			if(pOut)
				*pOut = tRet;
			return true;
		}
		else
			return false;
	}
};

/// @}

