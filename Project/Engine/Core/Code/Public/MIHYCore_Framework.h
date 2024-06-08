#ifndef _MIHYCORE_FRAMEWORK_H_
#define _MIHYCORE_FRAMEWORK_H_

namespace MIHYCore
{


    class MIHYCORE_API MIHYCore_Framework{
    private:
        
    public:
        MIHYCore_Framework() = default;
        MIHYCore_Framework(const MIHYCore_Framework&) = delete;
        MIHYCore_Framework(MIHYCore_Framework&&) = delete;
        ~MIHYCore_Framework() = default;
        MIHYCore_Framework& operator=(const MIHYCore_Framework&) = delete;
        MIHYCore_Framework& operator=(MIHYCore_Framework&&) = delete;

        

    };



}

#endif