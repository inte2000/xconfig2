// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#ifdef _WINDOWS
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <tchar.h>
#endif

#include "std_inc.h"
#include "boost_inc.h"
#include "modules.h"

#ifdef _SUPPORT_XML
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#endif

#ifdef _SUPPORT_JSON
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#endif
