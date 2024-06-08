#include "MIHYPlatform_PCH.h"
#include "MIHYPlatform_Library_Loader.h"

#include <Windows.h>

namespace MIHYPlatform
{

    Library_Handle load_library(const char* path){

        MessageBoxA(NULL, path, "load_library", MB_OK);

        HMODULE dllHandle{LoadLibraryA(path)};
        if(dllHandle == NULL){
            return nullptr;
        }

        return dllHandle;

    }

    Library_Handle load_library(const wchar_t* path){

        MessageBoxW(NULL, path, L"load_library", MB_OK);

        HMODULE dllHandle{LoadLibraryW(path)};
        if(dllHandle == NULL){
            return nullptr;
        }

        return dllHandle;

    }


}