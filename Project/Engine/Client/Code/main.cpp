#include <iostream>

#include "MIHYPlatform.h"
#include "MIHYPlatform_Library_Loader.h"

int main()
{

    auto test{MIHYPlatform::load_library("")};

    std::cout << "Hello, World!" << std::endl;
    
    return 0;

}