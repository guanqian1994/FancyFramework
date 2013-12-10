////////////////////////////////////////////////////////////////////////////////
/// @file  f2dInputKeyboardImpl.h
/// @brief fancy2D����ϵͳ ����ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyRefObj.h"
#include "fcyIO\fcyStream.h"

#include "../f2dInputSys.h"

#include "f2dInputSysAPI.h"

class f2dEngineImpl;

////////////////////////////////////////////////////////////////////////////////
/// @brief �����豸ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dInputKeyboardImpl :
	public fcyRefObjImpl<f2dInputKeyboard>
{
	friend class f2dInputSysImpl;
protected:
	class DefaultListener :
		public f2dInputKeyboardEventListener
	{
	protected:
		f2dEngineImpl* m_pEngine;
	public:
		void OnKeyboardBtnDown(F2DINPUTKEYCODE KeyCode);
		void OnKeyboardBtnUp(F2DINPUTKEYCODE KeyCode);
	public:
		DefaultListener(f2dInputSysImpl* pInputSys);
	};
private:
	static const fuInt BufferSize; 
	static const DIDATAFORMAT DIDF_Keyboard;
	static const DIOBJECTDATAFORMAT DIODF_Keyboard[256];
private:
	f2dInputSysImpl* m_pSys;
	IDirectInputDevice8* m_pDev;
	DefaultListener m_DefaultListener;
	f2dInputKeyboardEventListener* m_pListener;
	fBool m_ButtonState[256];
public:
	f2dInputMouse* ToMouse();
	f2dInputKeyboard* ToKeyboard();
	f2dInputJoystick* ToJoystick();

	fResult UpdateState(); 

	f2dInputKeyboardEventListener* GetListener();
	fResult SetListener(f2dInputKeyboardEventListener* pListener);
	
	fBool IsKeyDown(F2DINPUTKEYCODE KeyCode);
protected: // ��ֱֹ��new/delete
	f2dInputKeyboardImpl(f2dInputSysImpl* pSys, HWND Win, const GUID& pGUID, fBool bGlobalFocus);
	~f2dInputKeyboardImpl();
};
