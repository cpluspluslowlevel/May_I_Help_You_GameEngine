#ifndef _MIHYPLATFORM_LIBRARY_LOADER_H_
#define _MIHYPLATFORM_LIBRARY_LOADER_H_

namespace MIHYPlatform
{


    using LibraryHandle = void*;

    MIHYPLATFORM_API LibraryHandle load_library(const char* path);


}

#endif