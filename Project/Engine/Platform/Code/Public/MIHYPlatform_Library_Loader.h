#ifndef _MIHYPLATFORM_LIBRARY_LOADER_H_
#define _MIHYPLATFORM_LIBRARY_LOADER_H_

namespace MIHYPlatform
{


    using Library_Handle = void*;

    MIHYPLATFORM_API Library_Handle load_library(const char* path);
    MIHYPLATFORM_API Library_Handle load_library(const wchar_t* path);


}

#endif