#ifndef _MIHYCORE_MODULE_MANAGER_H_
#define _MIHYCORE_MODULE_MANAGER_H_

#include "MIHYPlatform_Library_Loader.h"

namespace MIHYCore::Module{

    class MIHYCore_Module_Manager;                                                                                                                                                                                          


    /// @brief 모듈의 정보를 저장하는 구조체
    struct MIHYCORE_MODULE{

        MIHYPlatform::Library_Handle handle;

    };


    class MIHYCORE_API MIHYCore_Module_Container{
    private:
        std::unordered_map<std::string, MIHYCORE_MODULE> m_module_umap;

    public:
        MIHYCore_Module_Container() = default;
        MIHYCore_Module_Container(const MIHYCore_Module_Container&) = delete;
        MIHYCore_Module_Container(MIHYCore_Module_Container&&) = delete;
        ~MIHYCore_Module_Container() = default;
        MIHYCore_Module_Container& operator=(const MIHYCore_Module_Container&) = delete;
        MIHYCore_Module_Container& operator=(MIHYCore_Module_Container&&) = delete;


        const decltype(m_module_umap)::value_type& find(const std::string& name);

        
        
    private:

        bool insert(const std::string& name, const MIHYPlatform::Library_Handle& module);

        bool insert(const std::string& name, const std::wstring& module_path);

        friend MIHYCore_Module_Manager;

    };


    class MIHYCORE_API MIHYCore_Module_Manager{
    private:

        

    public:
        MIHYCore_Module_Manager() = default;
        MIHYCore_Module_Manager(const MIHYCore_Module_Manager&) = delete;
        MIHYCore_Module_Manager(MIHYCore_Module_Manager&&) = delete;
        ~MIHYCore_Module_Manager() = default;
        MIHYCore_Module_Manager& operator=(const MIHYCore_Module_Manager&) = delete;
        MIHYCore_Module_Manager& operator=(MIHYCore_Module_Manager&&) = delete;



    };
}

#endif