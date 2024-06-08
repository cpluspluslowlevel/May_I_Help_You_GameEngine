#ifndef _MIHYCORE_PCH_H_
#define _MIHYCORE_PCH_H_

#include <unordered_map>
#include <vector>
#include <list>
#include <string>


#include "MIHYPlatform_API.h"

#if defined(MIHYCORE_IMPORT)
    #define MIHYCORE_API MIHYPLATFORM_LIBRARY_SYMBOL_IMPORT_COMMAND
#else
    #define MIHYCORE_API MIHYPLATFORM_LIBRARY_SYMBOL_EXPORT_COMMAND
#endif


#include "MIHYPlatform.h"


#endif