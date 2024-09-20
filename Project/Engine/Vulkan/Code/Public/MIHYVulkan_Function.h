#ifndef _MIHYVULKAN_FUNCTION_H_
#define _MIHYVULKAN_FUNCTION_H_


namespace MIHYVulkan{

    Boolean mihyvulkan_load_vulkan_function(VkInstance instance);

    typedef VkResult(*MIHYVulkan_Create_Debug_Report_Callback_Function_Type)(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* create_info, const VkAllocationCallbacks* allocator, VkDebugReportCallbackEXT* callback);
    extern MIHYVulkan_Create_Debug_Report_Callback_Function_Type       mihyvulkan_create_debug_report_callback;

    typedef VkResult(*MIHYVulkan_Destroy_Debug_Report_Callback_Function_Type)(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* allocator);
    extern MIHYVulkan_Destroy_Debug_Report_Callback_Function_Type      mihyvulkan_destroy_debug_report_callback;

}

#endif