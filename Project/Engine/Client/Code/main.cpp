#include <iostream>


#include "MIHYCore.h"
#include "MIHYCore_DataStruct.h"
#include "MIHYPlatform_Library_Loader.h"

int main()
{

    std::cout << "Hello World!" << std::endl;

    MIHYCore::DataStruct::mihyvector_unittest();
    MIHYCore::DataStruct::mihylist_unittest();

    
    return 0;

}