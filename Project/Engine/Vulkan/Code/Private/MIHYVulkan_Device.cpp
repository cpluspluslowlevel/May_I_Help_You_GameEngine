#include "MIHYVulkan_PCH.h"
#include "MIHYVulkan_Device.h"

#include "vulkan/vulkan.h"

namespace MIHYVulkan{

    void mihyvulkan_find_physical_device(){
        
        std::cout << "mihyvulkan_find_physical_device" << std::endl;

        VkInstanceCreateInfo instance_create_info{};
        instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    }

}