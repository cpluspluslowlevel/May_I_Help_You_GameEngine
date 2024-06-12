#include "MIHYPlatform_PCH.h"
#include "MIHYPlatform_Library_Loader.h"

#include <Windows.h>

namespace MIHYPlatform
{

    Library_Handle load_library(const char* path){

        HMODULE dllHandle{LoadLibraryA(path)};
        if(dllHandle == NULL){
            return nullptr;
        }

        return dllHandle;

    }

    Library_Handle load_library(const wchar_t* path){

        HMODULE dllHandle{LoadLibraryW(path)};
        if(dllHandle == NULL){
            return nullptr;
        }

        return dllHandle;

    }


}