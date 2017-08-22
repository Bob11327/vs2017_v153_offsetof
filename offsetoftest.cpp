// offsetoftest.cpp : Implementation of WinMain


#include "stdafx.h"
#include "offsetoftest_i.h"
#include "SimpleObject.h"


using namespace ATL;


class CoffsetoftestModule : public ATL::CAtlExeModuleT< CoffsetoftestModule >
{
};

CoffsetoftestModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/,
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	CString msg;
	CString	totalOutput;

#if defined(_CRT_USE_BUILTIN_OFFSETOF)
	msg = L"_CRT_USE_BUILTIN_OFFSETOF is defined\n";
#else
	msg = L"_CRT_USE_BUILTIN_OFFSETOF is not defined\n";
#endif
	OutputDebugString(msg);
	totalOutput += msg;

	msg.Format(L"_MSC_VER = %u\n", _MSC_VER);
	OutputDebugString(msg);
	totalOutput += msg;

	const ATL_PROPMAP_ENTRY* pEntry = CSimpleObject::GetPropertyMap();
	msg.Format(L"Offset of %s = %u\n", pEntry->szDesc, pEntry->dwOffsetData);
	OutputDebugString(msg);
	totalOutput += msg;

	msg.Format(L"offsetof(CSimpleObject, m_size.cx) == %u\n", offsetof(CSimpleObject, m_size.cx));
	OutputDebugString(msg);
	totalOutput += msg;

	msg.Format(L"offsetof(CSimpleObject, m_size.cy) == %u\n", offsetof(CSimpleObject, m_size.cy));
	OutputDebugString(msg);
	totalOutput += msg;

	::MessageBox(NULL, totalOutput, L"C++ offsetof test application", MB_OK);

	return _AtlModule.WinMain(nShowCmd);
}

