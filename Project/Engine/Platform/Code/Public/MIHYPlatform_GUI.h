#ifndef _MIHYPLATFORM_GUI_H_
#define _MIHYPLATFORM_GUI_H_

namespace MIHYPlatform{
    namespace GUI{

    struct MIHYPLATFORM_API MIHYPLATFORM_GUI_DATA{
        void* handle;
    };

    class MIHYPLATFORM_API MIHYPlatform_GUI_Element{
    public:

        virtual void initialize() = 0;
        virtual void release() = 0;

        virtual MIHYPLATFORM_GUI_DATA get_data() = 0;

    };

    class MIHYPLATFORM_API MIHYPlatform_GUI{
    public:

        

    };

    }
}

#endif