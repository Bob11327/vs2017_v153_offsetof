// SimpleObject.h : Declaration of the CSimpleObject

#pragma once
#include "resource.h"       // main symbols
#include "offsetoftest_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

//---------------------------------------------------------------------------
// NOTE WELL:
// As far as I know, a key to reproducing the offsetof error is that
// the embedded structure must be a CLASS definition that inherits from a STRUCT definition,
// and the fields are defined in the nested structure
//---------------------------------------------------------------------------

class CSize : public tagSIZE
{
public:
	CSize() throw() { cx = cy = 0; };
	CSize(_In_ DWORD dwSize) throw() { cx = LOWORD(dwSize); cy = HIWORD(dwSize); }
};

//---------------------------------------------------------------------------
// CSimpleObject
//---------------------------------------------------------------------------

class ATL_NO_VTABLE CSimpleObject :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimpleObject, &CLSID_SimpleObject>,
	public IDispatchImpl<ISimpleObject, &IID_ISimpleObject, &LIBID_offsetoftestLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSimpleObject()
	{
		memset(m_data, sizeof(m_data), 0);
		m_size.cx = m_size.cy = 32;
	}

BEGIN_COM_MAP(CSimpleObject)
	COM_INTERFACE_ENTRY(ISimpleObject)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

BEGIN_PROP_MAP(CSimpleObject)
	PROP_DATA_ENTRY("_cx", m_size.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_size.cy, VT_UI4)
END_PROP_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	char	m_data[256];				//member variable at offset 0
	CSize	m_size;						//member variable at offset 256
};
