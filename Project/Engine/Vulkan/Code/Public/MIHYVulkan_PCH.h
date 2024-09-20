#ifndef _MIHYVULKAN_PCH_H_
#define _MIHYVULKAN_PCH_H_

#include "vulkan/vulkan.h"

#include "MIHYCommonHeader.h"

#include "MIHYPlatform.h"
#include "MIHYPlatform_API.h"

#include "MIHYCore.h"
#include "MIHYCore_DataStruct.h"

#include "MIHYVulkan_Function.h"

#if defined(MIHYVULKAN_IMPORT)
    #define MIHYVULKAN_API MIHYPLATFORM_LIBRARY_SYMBOL_IMPORT_COMMAND
#else
    #define MIHYVULKAN_API MIHYPLATFORM_LIBRARY_SYMBOL_EXPORT_COMMAND
#endif

#endif