// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once

// General includes
#include <windows.h>
#include <winbase.h>

#include <iostream>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS  // some CString constructors will be explicit

// ATL includes
#pragma warning( disable: 4189 )    // disable local variable is initialized but not referenced
#include <atlbase.h>

#include <vss.h>
#include <vswriter.h>
#include <vsbackup.h>

// STL includes
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

// Used for safe string manipulation
#include <strsafe.h>
#include <atlstr.h>
#include <regex>
#include <msxml2.h>
#include "CComException.h"

using namespace std;

#define CHECK_HRESULT(x) { HRESULT ckhr = ((x)); if (ckhr != S_OK) throw new CComException(ckhr, __FILE__, __LINE__); }

//#include "shadow.h"

