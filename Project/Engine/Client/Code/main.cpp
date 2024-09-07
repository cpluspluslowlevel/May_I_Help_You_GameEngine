#include <iostream>


#include "MIHYCore.h"
#include "MIHYCore_DataStruct.h"
#include "MIHYPlatform_Library_Loader.h"

#include "MIHYVulkan.h"
#include "MIHYVulkan_Device.h"

int main()
{

    std::cout << "Test start!" << std::endl;

    MIHYCore::DataStruct::mihyvector_unittest();
    MIHYCore::DataStruct::mihylist_unittest();
    MIHYCore::DataStruct::mihyhashmap_unittest();

    std::cout << "Test end!" << std::endl;

    MIHYVulkan::mihyvulkan_find_physical_device();
    
    return 0;

}