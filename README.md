# vs2017_v153_offsetof
Reproducible scenario for offsetof() problem in Visual Studio 2017 v15.3.2

Visual Studio 2017 version 15.3 (through 15.3.2) has an apparent regression bug affecting the offsetof() macro.

This is important in ATL/COM programming, where the property map (BEGIN_PROP_MAP/PROP_DATA_ENTRY) updates fields based on the offset from the structure.

This sample defines a CSimpleObject class with an m_size member at offset 256 in the structure.

Running the program doesn't instantiate the object - it just OutputDebugString's some values, then accumulates that output into a MessageBox, showing that the results are incorrect.

When compiled & run with VS2017 v15.2, the correct output is seen:
````
_CRT_USE_BUILTIN_OFFSETOF is not defined
_MSC_VER = 1910
Offset of _cx = 272
offsetof(CSimpleObject, m_size.cx) == 272
offsetof(CSimpleObject, m_size.cy) == 276
````

When compiled & run with VS2017 v15.3, the incorrect output is seen:
````
_CRT_USE_BUILTIN_OFFSETOF is defined
_MSC_VER = 1911
Offset of _cx = 0
offsetof(CSimpleObject, m_size.cx) == 0
offsetof(CSimpleObject, m_size.cy) == 4
````
