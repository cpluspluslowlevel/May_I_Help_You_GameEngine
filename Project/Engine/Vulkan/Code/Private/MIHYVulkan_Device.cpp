#include "MIHYVulkan_PCH.h"
#include "MIHYVulkan_Device.h"

#include "vulkan/vulkan.h"

#pragma comment(lib, "vulkan-1.lib")

VkInstance instance;

MIHYCore::DataStruct::MIHYVector<const char*> required_layer_name_vector{1, {
                                                                                "VK_LAYER_LUNARG_standard_validation"
                                                                            }};

namespace MIHYVulkan{

    void mihyvulkan_find_physical_device(){
        
        std::cout << "mihyvulkan_find_physical_device" << std::endl;

        VkApplicationInfo application_info{};
        application_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        application_info.pApplicationName   = "MIHY";
        application_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        application_info.pEngineName        = "MIHY";
        application_info.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
        application_info.apiVersion         = VK_API_VERSION_1_0;

        VkInstanceCreateInfo instance_create_info{};
        instance_create_info.sType                      = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instance_create_info.pNext                      = nullptr;
        instance_create_info.flags                      = NULL;
        instance_create_info.pApplicationInfo           = &application_info;
        instance_create_info.enabledLayerCount          = 0;
        instance_create_info.ppEnabledLayerNames        = nullptr;
        instance_create_info.enabledExtensionCount      = 0;
        instance_create_info.ppEnabledExtensionNames    = nullptr;

        if(vkCreateInstance(&instance_create_info, nullptr, &instance) == VK_SUCCESS){
            std::cout << "Vulkan Instance Created" << std::endl;
        }else{
            std::cout << "Vulkan Instance Creation Failed" << std::endl;
        }

        UInt32 layer_property_count;
        vkEnumerateInstanceLayerProperties(&layer_property_count, nullptr);

        MIHYCore::DataStruct::MIHYVector<VkLayerProperties> layer_property_vector{layer_property_count};
        layer_property_vector.resize(layer_property_count);
        vkEnumerateInstanceLayerProperties(&layer_property_count, layer_property_vector.get_memory());



    }

}