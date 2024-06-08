#ifndef _MIHYMODULE_PCH_H_
#define _MIHYMODULE_PCH_H_

#include <unordered_map>
#include <vector>
#include <list>
#include <string>


#include "MIHYPlatform_API.h"

#if defined(MIHYMODULE_IMPORT)
    #define MIHYMODULE_API MIHYPLATFORM_LIBRARY_SYMBOL_IMPORT_COMMAND
#else
    #define MIHYMODULE_API MIHYPLATFORM_LIBRARY_SYMBOL_EXPORT_COMMAND
#endif


#include "MIHYPlatform.h"

#endif