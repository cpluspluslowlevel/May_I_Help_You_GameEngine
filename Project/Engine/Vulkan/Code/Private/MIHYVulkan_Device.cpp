#include "MIHYVulkan_PCH.h"
#include "MIHYVulkan_Device.h"

#include "vulkan/vulkan.h"

#ifdef MIHY_PLATFORM_WINDOWS
#include <Windows.h>
#include "vulkan/vulkan_win32.h"
#endif



#pragma comment(lib, "vulkan-1.lib")

namespace MIHYVulkan{

    VkInstance                  instance;
    VkDebugReportCallbackEXT    debug_report_callback;
    VkSurfaceKHR                output_surface;
    VkPhysicalDevice            physical_device;

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

    

    VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData){
        std::cout << "validation layer: " << msg << std::endl;
        return VK_FALSE;
    }

    Boolean mihyvulkan_check_required_layer_support(){

        //지원하는 레이어를 얻습니다.
        UInt32 layer_count;
        vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

        MIHYCore::DataStruct::MIHYVector<VkLayerProperties> layer_property_vector{layer_count};
        layer_property_vector.resize(layer_count);
        vkEnumerateInstanceLayerProperties(&layer_count, layer_property_vector.get_memory());

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

        return true;

    }

    VkSurfaceKHR mihyvulkan_create_surface(void* program_instance_handle, void* gui_handle){

        std::cout << "mihyvulkan_create_surface" << std::endl;

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

    void mihyvulkan_find_physical_device(){
        
        std::cout << "mihyvulkan_find_physical_device" << std::endl;

        
        UInt32 physical_device_count;
        vkEnumeratePhysicalDevices(instance, &physical_device_count, nullptr);

        MIHYCore::DataStruct::MIHYVector<VkPhysicalDevice> physical_device_vector{physical_device_count};
        physical_device_vector.resize(physical_device_count);
        vkEnumeratePhysicalDevices(instance, &physical_device_count, physical_device_vector.get_memory());

        //점수가 가장 높은 물리 장치를 선택합니다.
        physical_device                                 = VK_NULL_HANDLE;
        Int32   most_suitable_physical_device_index     = -1;       //-1 = not found
        UInt32  most_physical_device_suitablility_score = 0;
        for(UInt32 i = 0; i < physical_device_count; ++i){

            VkPhysicalDeviceProperties physical_device_properties;
            vkGetPhysicalDeviceProperties(physical_device_vector[i], &physical_device_properties);

            std::cout << "Physical Device: " << physical_device_properties.deviceName << std::endl;

            UInt32 score{ mihyvulkan_calculate_physical_device_suitability_score(physical_device_vector[i]) };
            if(score > most_physical_device_suitablility_score){
                most_suitable_physical_device_index     = i;
                most_physical_device_suitablility_score = score;
            }

        }

        if(most_suitable_physical_device_index != -1){
            physical_device = physical_device_vector[most_suitable_physical_device_index];
        }

    }

    void mihyvulkan_find_queue(VkPhysicalDevice device){
        
    }

    Boolean mihyvulkan_initialize(MIHYPlatform::MIHYPLATFORM_PLATFORM* platform, MIHYPlatform::GUI::MIHYPlatform_GUI_Element* screen_gui_element){

        std::cout << "mihyvulkan_initialize" << std::endl;

        std::cout << "Checking Required Layer Support: ";
        if(mihyvulkan_check_required_layer_support()){
            std::cout << "Support" << std::endl;
        }else{
            std::cout << "Not Support" << std::endl;
            return false;
        }


        #ifdef MIHY_PLATFORM_WINDOWS
            std::cout << "Platform: Windows" << std::endl;
        #else
            std::cout << "Platform: Unknown" << std::endl;
        #endif


        //Vulkan 인스턴스를 생성합니다.

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

        if(vkCreateInstance(&instance_create_info, nullptr, &instance) == VK_SUCCESS){
            std::cout << "Vulkan instance created" << std::endl;
        }else{
            std::cout << "Vulkan instance creation failed" << std::endl;
            return false;
        }

        std::cout << "Load vulkan function" << std::endl;
        if(mihyvulkan_load_vulkan_function(instance)){
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

        if(mihyvulkan_create_debug_report_callback(instance, &debug_report_callback_create_info, nullptr, &debug_report_callback) == VK_SUCCESS){
            std::cout << "Vulkan debug report callback created" << std::endl;
        }else{
            std::cout << "Vulkan debug report callback creation failed" << std::endl;
            return false;
        }

        output_surface = mihyvulkan_create_surface(platform->program_instance_handle, screen_gui_element->get_data().handle);

        mihyvulkan_find_physical_device();
        if(physical_device == VK_NULL_HANDLE){
            std::cout << "Physical device not found" << std::endl;
            return false;
        }

        mihyvulkan_find_queue(physical_device);

        return true;

    }

    Boolean      mihyvulkan_release(){
            
        std::cout << "mihyvulkan_release" << std::endl;

        vkDestroySurfaceKHR(instance, output_surface, nullptr);
        mihyvulkan_destroy_debug_report_callback(instance, debug_report_callback, nullptr);
        vkDestroyInstance(instance, nullptr);
    
        return true;

    }


    

}