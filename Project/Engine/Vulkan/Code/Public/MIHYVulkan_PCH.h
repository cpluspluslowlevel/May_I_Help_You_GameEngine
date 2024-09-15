#ifndef _MIHYVULKAN_PCH_H_
#define _MIHYVULKAN_PCH_H_

#include "MIHYCommonHeader.h"

#include "MIHYPlATFORM.H"
#include "MIHYPlatform_API.h"

#include "MIHYCore.h"
#include "MIHYCore_DataStruct.h"

#if defined(MIHYVULKAN_IMPORT)
    #define MIHYVULKAN_API MIHYPLATFORM_LIBRARY_SYMBOL_IMPORT_COMMAND
#else
    #define MIHYVULKAN_API MIHYPLATFORM_LIBRARY_SYMBOL_EXPORT_COMMAND
#endif

#endif