#include "MIHYPlatform_PCH.h"
#include "MIHYPlatform_Library_Loader.h"

#include <Windows.h>

namespace MIHYPlatform
{

    LibraryHandle load_library(const char* path){

        MessageBox(NULL, path, TEXT("load_library"), MB_OK);

        HMODULE dllHandle{LoadLibrary(path)};
        if(dllHandle == NULL){
            return nullptr;
        }

        return dllHandle;

    }


}