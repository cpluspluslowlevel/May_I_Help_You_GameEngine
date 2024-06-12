#include "MIHYCore_PCH.h"
#include "MIHYCore_DataStruct.h"


namespace MIHYCore{
    namespace DataStruct{

        

    std::string MIHYVector_UnitTest()
    {
        
#define VECTOR_PRINT(v) std::cout << "Capacity: " << v.get_capacity() << std::endl; for(UInt32 i = 0; i < v.get_size(); ++i) std::cout << v[i] << " "; std::cout << std::endl;
        {
            MIHYVector<UInt32> v{10};
            assert(v.get_capacity() == 10);
            for(UInt32 i = 0; i < v.get_size(); ++i) v.push_back(i);
            //ccassert(v.get_size() == 10);
            VECTOR_PRINT(v);
        }
        return "Success";

    }


    }
}