#include "MIHYVulkan_PCH.h"
#include "MIHYVulkan_Device.h"

#include "vulkan/vulkan.h"

#ifdef MIHY_PLATFORM_WINDOWS
#include <Windows.h>
#include "vulkan/vulkan_win32.h"
#endif



#pragma comment(lib, "vulkan-1.lib")

namespace MIHYVulkan{

    struct MIHYVULKAN_QUEUE{
        VkQueue                                                         graphics_queue;
        VkQueue                                                         present_queue;
    };

    struct MIHYVULKAN_VULKAN{

        VkInstance                                                      instance;
        VkDebugReportCallbackEXT                                        debug_report_callback;
        
        VkSurfaceKHR                                                    output_surface;

        VkPhysicalDevice                                                physical_device;
        VkDevice                                                        logical_device;
        MIHYVULKAN_QUEUE                                                queue;

    };

    MIHYVULKAN_VULKAN vulkan{};

    MIHYCore::DataStruct::MIHYVector<const char*> required_layer_name_vector{1, {
                                                                                    "VK_LAYER_KHRONOS_validation"
                                                                                }};

    MIHYCore::DataStruct::MIHYVector<const char*> required_extension_name_vector{1, {
                                                                                        VK_EXT_DEBUG_REPORT_EXTENSION_NAME
                                                                                        #ifdef MIHY_PLATFORM_WINDOWS
                                                                                        , VK_KHR_SURFACE_EXTENSION_NAME
                                                                                        , VK_KHR_WIN32_SURFACE_EXTENSION_NAME
                                                                                        #endif
                                                                                    }};

    MIHYCore::DataStruct::MIHYVector<const char*> required_logical_device_extension_name_vector{1, {
                                                                                                        VK_KHR_SWAPCHAIN_EXTENSION_NAME
                                                                                                   }};

    

    VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData){
        std::cout << "validation layer: " << msg << std::endl;
        return VK_FALSE;
    }

    Boolean mihyvulkan_check_required_layer_support(){

        //지원하는 레이어, 확장을 얻습니다.
        UInt32 layer_count;
        UInt32 extension_count;
        vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
        vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

        MIHYCore::DataStruct::MIHYVector<VkLayerProperties>     layer_property_vector{layer_count};
        MIHYCore::DataStruct::MIHYVector<VkExtensionProperties> extension_property_vector{extension_count};
        layer_property_vector.resize(layer_count);
        extension_property_vector.resize(extension_count);
        vkEnumerateInstanceLayerProperties(&layer_count, layer_property_vector.get_memory());
        vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extension_property_vector.get_memory());

        for(UInt32 j = 0; j < layer_count; ++j){
            std::cout << "Layer: " << layer_property_vector[j].layerName << std::endl;
        }

        for(UInt32 i = 0; i < extension_count; ++i){
            std::cout << "Extension: " << extension_property_vector[i].extensionName << std::endl;
        }

        //원하는 레이어가 지원되는지 확인합니다.
        for(UInt32 i = 0; i < required_layer_name_vector.get_size(); ++i){

            Boolean support = false;

            for(UInt32 j = 0; j < layer_count; ++j){

                if(strcmp(required_layer_name_vector[i], layer_property_vector[j].layerName) == 0){
                    support = true;
                    break;
                }

            }

            if(!support){
                return false;
            }


        }

        //원하는 확장이 지원되는지 확인합니다.
        for(UInt32 i = 0; i < required_extension_name_vector.get_size(); ++i){

            Boolean support = false;

            for(UInt32 j = 0; j < extension_count; ++j){

                if(strcmp(required_extension_name_vector[i], extension_property_vector[j].extensionName) == 0){
                    support = true;
                    break;
                }

            }

            if(!support){
                return false;
            }

        }

        return true;

    }

    VkSurfaceKHR mihyvulkan_create_surface(VkInstance instance, void* program_instance_handle, void* gui_handle){

        VkSurfaceKHR surface;

        #ifdef MIHY_PLATFORM_WINDOWS
        VkWin32SurfaceCreateInfoKHR surface_create_info{};
        surface_create_info.sType       = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        surface_create_info.pNext       = nullptr;
        surface_create_info.flags       = NULL;
        surface_create_info.hinstance   = (HINSTANCE)program_instance_handle;
        surface_create_info.hwnd        = (HWND)gui_handle;

        if(vkCreateWin32SurfaceKHR(instance, &surface_create_info, nullptr, &surface) == VK_SUCCESS){
            std::cout << "Vulkan surface created" << std::endl;
        }else{
            std::cout << "Vulkan surface creation failed" << std::endl;
            return VK_NULL_HANDLE;
        }
        #endif

        return surface;

    }

    UInt32 mihyvulkan_calculate_physical_device_suitability_score(VkPhysicalDevice physical_device){

        VkPhysicalDeviceProperties physical_device_properties;
        vkGetPhysicalDeviceProperties(physical_device, &physical_device_properties);

        UInt32 score = 0;

        if(physical_device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
            score += 1000;
        }

        return score;

    }

    void mihyvulkan_find_physical_device(VkInstance instance){
        
        std::cout << "mihyvulkan_find_physical_device" << std::endl;

        
        UInt32 physical_device_count;
        vkEnumeratePhysicalDevices(instance, &physical_device_count, nullptr);

        MIHYCore::DataStruct::MIHYVector<VkPhysicalDevice> physical_device_vector{physical_device_count};
        physical_device_vector.resize(physical_device_count);
        vkEnumeratePhysicalDevices(instance, &physical_device_count, physical_device_vector.get_memory());

        //점수가 가장 높은 물리 장치를 선택합니다.
        vulkan.physical_device                          = VK_NULL_HANDLE;
        Int32   most_suitable_physical_device_index     = -1;       //-1 = not found
        UInt32  most_physical_device_suitablility_score = 0;
        for(UInt32 i = 0; i < physical_device_count; ++i){

            VkPhysicalDeviceProperties physical_device_properties;
            vkGetPhysicalDeviceProperties(physical_device_vector[i], &physical_device_properties);

            std::cout << "Physical Device: " << physical_device_properties.deviceName << std::endl;

            UInt32 score{mihyvulkan_calculate_physical_device_suitability_score(physical_device_vector[i])};
            if(score > most_physical_device_suitablility_score){
                most_suitable_physical_device_index     = i;
                most_physical_device_suitablility_score = score;
            }

        }

        if(most_suitable_physical_device_index != -1){
            vulkan.physical_device = physical_device_vector[most_suitable_physical_device_index];
        }

    }

    Boolean mihyvulkan_create_logical_device(VkInstance instance, VkPhysicalDevice physical_device, VkDevice* out_logical_device, MIHYVULKAN_QUEUE* out_queue){

        //필요한큐 패밀리를 찾습니다.

        UInt32 queue_family_count;
        vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);

        MIHYCore::DataStruct::MIHYVector<VkQueueFamilyProperties> queue_family_property_vector{queue_family_count};
        queue_family_property_vector.resize(queue_family_count);
        vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_family_property_vector.get_memory());

        UInt32 graphics_queue_family_index  = -1;
        UInt32 present_queue_family_index   = -1;
        for(UInt32 i = 0; i < queue_family_count; ++i){

            if(queue_family_property_vector[i].queueCount > 0){
                
                //그래픽스 큐 패밀리인지 확인합니다.
                if(queue_family_property_vector[i].queueFlags & VK_QUEUE_GRAPHICS_BIT){
                    graphics_queue_family_index = i;
                }

                //화면 출력 큐 패밀리인지 확인합니다.
                if(vkGetPhysicalDeviceWin32PresentationSupportKHR(physical_device, i)){
                    present_queue_family_index = i;
                }

            }

            /*
            std::cout << "Queue Family " << i << " Type: ";
            if(queue_family_property_vector[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)          std::cout << "VK_QUEUE_GRAPHICS_BIT, ";
            if(queue_family_property_vector[i].queueFlags & VK_QUEUE_COMPUTE_BIT)           std::cout << "VK_QUEUE_COMPUTE_BIT, ";
            if(queue_family_property_vector[i].queueFlags & VK_QUEUE_TRANSFER_BIT)          std::cout << "VK_QUEUE_TRANSFER_BIT, ";
            if(queue_family_property_vector[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)    std::cout << "VK_QUEUE_SPARSE_BINDING_BIT, ";
            if(queue_family_property_vector[i].queueFlags & VK_QUEUE_PROTECTED_BIT)         std::cout << "VK_QUEUE_PROTECTED_BIT, ";
            if(queue_family_property_vector[i].queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR)  std::cout << "VK_QUEUE_VIDEO_DECODE_BIT_KHR, ";
            if(queue_family_property_vector[i].queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR)  std::cout << "VK_QUEUE_VIDEO_ENCODE_BIT_KHR, ";
            if(queue_family_property_vector[i].queueFlags & VK_QUEUE_OPTICAL_FLOW_BIT_NV)   std::cout << "VK_QUEUE_OPTICAL_FLOW_BIT_NV,";
            std::cout << " Count: " << queue_family_property_vector[i].queueCount << std::endl;
            */

        }

        if(graphics_queue_family_index == -1){
            std::cout << "Graphics queue family not found" << std::endl;
            return false;
        }

        if(present_queue_family_index == -1){
            std::cout << "Present queue family not found" << std::endl;
            return false;
        }


        //논리 장치를 생성합니다.

        *out_logical_device = VK_NULL_HANDLE;

        float                                                       queue_priority = 1.0f;
        VkDeviceQueueCreateInfo                                     queue_create_info{};
        MIHYCore::DataStruct::MIHYVector<VkDeviceQueueCreateInfo>   queue_create_info_vector{2};
        queue_create_info.sType             = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_info.pNext             = nullptr;
        queue_create_info.flags             = NULL;
        queue_create_info.pQueuePriorities  = &queue_priority;
        queue_create_info.queueCount        = 1;

        queue_create_info.queueFamilyIndex  = graphics_queue_family_index;
        queue_create_info_vector.push_back(queue_create_info);

        queue_create_info.queueFamilyIndex  = present_queue_family_index;
        queue_create_info_vector.push_back(queue_create_info);

        VkDeviceCreateInfo device_create_info{};
        device_create_info.sType                    = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        device_create_info.pNext                    = nullptr;
        device_create_info.flags                    = NULL;
        device_create_info.queueCreateInfoCount     = queue_create_info_vector.get_size();
        device_create_info.pQueueCreateInfos        = queue_create_info_vector.get_memory();
        device_create_info.pEnabledFeatures         = nullptr;
        device_create_info.enabledLayerCount        = 0;
        device_create_info.ppEnabledLayerNames      = nullptr;
        device_create_info.enabledExtensionCount    = 0;
        device_create_info.ppEnabledExtensionNames  = nullptr;

        vkCreateDevice(physical_device, &device_create_info, nullptr, out_logical_device);
        if(*out_logical_device == VK_NULL_HANDLE){
            std::cout << "Logical device creation failed" << std::endl;
            return false;
        }

        //큐를 얻습니다.

        vkGetDeviceQueue(*out_logical_device, graphics_queue_family_index, 0, &out_queue->graphics_queue);
        if(out_queue->graphics_queue == VK_NULL_HANDLE){
            std::cout << "Graphics queue not found" << std::endl;
            return false;
        }

        vkGetDeviceQueue(*out_logical_device, present_queue_family_index, 0, &out_queue->present_queue);
        if(out_queue->present_queue == VK_NULL_HANDLE){
            std::cout << "Present queue not found" << std::endl;
            return false;
        }


        //스왑체인과 연동합니다.
        
        UInt32 surface_format_count{};
        UInt32 present_mode_count{};

        vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, vulkan.output_surface, &surface_format_count, nullptr);
        vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, vulkan.output_surface, &present_mode_count, nullptr);

        VkSurfaceCapabilitiesKHR                                surface_capabilities;
        MIHYCore::DataStruct::MIHYVector<VkSurfaceFormatKHR>    surface_format_vector{surface_format_count};
        MIHYCore::DataStruct::MIHYVector<VkPresentModeKHR>      present_mode_vector{present_mode_count};
        surface_format_vector.resize(surface_format_count);
        present_mode_vector.resize(present_mode_count);

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, vulkan.output_surface, &surface_capabilities);
        vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, vulkan.output_surface, &surface_format_count, surface_format_vector.get_memory());
        vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, vulkan.output_surface, &present_mode_count, present_mode_vector.get_memory());


        const VkSurfaceFormatKHR    required_surface_format{VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
        VkSurfaceFormatKHR          choosen_surface_format{};
        const VkPresentModeKHR      required_present_mode{VK_PRESENT_MODE_FIFO_KHR};
        VkPresentModeKHR            choosen_present_mode{};

        if(surface_format_count == 1 && surface_format_vector[0].format == VK_FORMAT_UNDEFINED){
            choosen_surface_format = required_surface_format;
            return false;
        }

        for(UInt32 i = 0; i < surface_format_count; ++i){
            if(surface_format_vector[i].format == required_surface_format.format && surface_format_vector[i].colorSpace == required_surface_format.colorSpace){
                choosen_surface_format = required_surface_format;
                break;
            }
        }

        return true;

    }

    Boolean mihyvulkan_initialize(MIHYPlatform::MIHYPLATFORM_PLATFORM* platform, MIHYPlatform::GUI::MIHYPlatform_GUI_Element* screen_gui_element){

        std::cout << "mihyvulkan_initialize" << std::endl;


        std::cout << "-------------------------------------------------------" << std::endl;
        std::cout << "mihyvulkan_check_required_layer_support" << std::endl;
        if(mihyvulkan_check_required_layer_support()){
            std::cout << "Support" << std::endl;
        }else{
            std::cout << "Not Support" << std::endl;
            return false;
        }
        std::cout << "-------------------------------------------------------" << std::endl;



        #ifdef MIHY_PLATFORM_WINDOWS
            std::cout << "Platform: Windows" << std::endl;
        #else
            std::cout << "Platform: Unknown" << std::endl;
        #endif


        //Vulkan 인스턴스를 생성합니다.

        std::cout << "-------------------------------------------------------" << std::endl;
        std::cout << "Create vulkan instance" << std::endl;
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
        instance_create_info.enabledLayerCount          = required_layer_name_vector.get_size();
        instance_create_info.ppEnabledLayerNames        = required_layer_name_vector.get_memory();
        instance_create_info.enabledExtensionCount      = required_extension_name_vector.get_size();
        instance_create_info.ppEnabledExtensionNames    = required_extension_name_vector.get_memory();

        if(vkCreateInstance(&instance_create_info, nullptr, &vulkan.instance) == VK_SUCCESS){
            std::cout << "Vulkan instance created" << std::endl;
        }else{
            std::cout << "Vulkan instance creation failed" << std::endl;
            return false;
        }
        std::cout << "-------------------------------------------------------" << std::endl;


        //불칸 함수를 로드합니다.

        std::cout << "Load vulkan function" << std::endl;
        if(mihyvulkan_load_vulkan_function(vulkan.instance)){
            std::cout << "Vulkan function loaded" << std::endl;
        }else{
            std::cout << "Vulkan function load failed" << std::endl;
            return false;
        }



        //디버그 레이어를 생성합니다.

        VkDebugReportCallbackCreateInfoEXT debug_report_callback_create_info{};
        debug_report_callback_create_info.sType         = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        debug_report_callback_create_info.pNext         = nullptr;
        debug_report_callback_create_info.flags         = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
        debug_report_callback_create_info.pfnCallback   = debug_report;
        debug_report_callback_create_info.pUserData     = nullptr;

        if(mihyvulkan_create_debug_report_callback(vulkan.instance, &debug_report_callback_create_info, nullptr, &vulkan.debug_report_callback) == VK_SUCCESS){
            std::cout << "Vulkan debug report callback created" << std::endl;
        }else{
            std::cout << "Vulkan debug report callback creation failed" << std::endl;
            return false;
        }


        //출력 서피스를 생성합니다.

        vulkan.output_surface = mihyvulkan_create_surface(vulkan.instance, platform->program_instance_handle, screen_gui_element->get_data().handle);


        //물리, 논리 장치를 생성합니다.

        mihyvulkan_find_physical_device(vulkan.instance);
        if(vulkan.physical_device == VK_NULL_HANDLE){
            std::cout << "Physical device not found" << std::endl;
            return false;
        }else{
            std::cout << "Physical device found" << std::endl;
        }

        if(mihyvulkan_create_logical_device(vulkan.instance, vulkan.physical_device, &vulkan.logical_device, &vulkan.queue)){
            std::cout << "Logical device created" << std::endl;
        }else{
            std::cout << "Logical device creation failed" << std::endl;
            return false;
        }

        return true;

    }

    Boolean      mihyvulkan_release(){
            
        std::cout << "mihyvulkan_release" << std::endl;

        vkDestroySurfaceKHR(vulkan.instance, vulkan.output_surface, nullptr);
        mihyvulkan_destroy_debug_report_callback(vulkan.instance, vulkan.debug_report_callback, nullptr);
        vkDestroyDevice(vulkan.logical_device, nullptr);
        vkDestroyInstance(vulkan.instance, nullptr);
    
        return true;

    }


    

}