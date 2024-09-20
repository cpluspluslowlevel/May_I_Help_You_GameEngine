#ifndef _MIHYVULKAN_DEVICE_H_
#define _MIHYVULKAN_DEVICE_H_

#include "MIHYPlatform_Platform.h"
#include "MIHYPlatform_GUI.h"

namespace MIHYVulkan{

    /// @brief 그래픽 처리를 하는 물리 장치를 나타내는 클래스입니다. 
    class MIHYVULKAN_API MIHYVulkan_Physical_Device{
    private:

        VkPhysicalDevice   physical_device;
        
    public:
    };

    MIHYVULKAN_API Boolean      mihyvulkan_initialize(MIHYPlatform::MIHYPLATFORM_PLATFORM* platform, MIHYPlatform::GUI::MIHYPlatform_GUI_Element* screen_gui_element);
    MIHYVULKAN_API Boolean      mihyvulkan_release();

}

#endif