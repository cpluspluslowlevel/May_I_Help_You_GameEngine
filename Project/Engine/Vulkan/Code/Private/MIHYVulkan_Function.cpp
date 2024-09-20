#include "MIHYVulkan_PCH.h"
#include "MIHYVulkan_Function.h"

#include "vulkan/vulkan.h"

namespace MIHYVulkan{


    MIHYVulkan_Create_Debug_Report_Callback_Function_Type       mihyvulkan_create_debug_report_callback{};
    MIHYVulkan_Destroy_Debug_Report_Callback_Function_Type      mihyvulkan_destroy_debug_report_callback{};

    Boolean mihyvulkan_load_vulkan_function(VkInstance instance){

        mihyvulkan_create_debug_report_callback = (MIHYVulkan_Create_Debug_Report_Callback_Function_Type)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
        if(mihyvulkan_create_debug_report_callback == nullptr){
            return false;
        }

        mihyvulkan_destroy_debug_report_callback = (MIHYVulkan_Destroy_Debug_Report_Callback_Function_Type)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
        if(mihyvulkan_destroy_debug_report_callback == nullptr){
            return false;
        }

        return true;

    }

}