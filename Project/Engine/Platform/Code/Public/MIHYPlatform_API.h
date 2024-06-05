#ifndef _MIHYPLATFORM_API_H_
#define _MIHYPLATFORM_API_H_


#if defined(_WIN64)
    #define MIHYPLATFORM_LIBRARY_SYMBOL_EXPORT_COMMAND __declspec(dllexport)
    #define MIHYPLATFORM_LIBRARY_SYMBOL_IMPORT_COMMAND __declspec(dllimport)
#elif defined(__linux__)
    #define MIHYPLATFORM_LIBRARY_SYMBOL_EXPORT_COMMAND __attribute__(visibility("default"))
    #define MIHYPLATFORM_LIBRARY_SYMBOL_IMPORT_COMMAND __attribute__(visibility("default"))
#else
    static_assert(false, "Platform not supported");
#endif


#endif