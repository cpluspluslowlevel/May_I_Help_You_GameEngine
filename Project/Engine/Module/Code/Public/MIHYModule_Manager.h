#ifndef _MIHYMODULE_MANAGER_H_
#define _MIHYMODULE_MANAGER_H_

#include "MIHYPlatform_Library_Loader.h"

namespace MIHYModule
{

    class MIHYModule_Manager;                                                                                                                                                                                          


    /// @brief 모듈의 정보를 저장하는 구조체
    struct MIHYMODULE_MODULE{

        MIHYPlatform::Library_Handle handle;

    };


    class MIHYMODULE_API MIHYModule_Module_Container{
    private:
        std::unordered_map<std::string, MIHYMODULE_MODULE> m_module_umap;

    public:
        MIHYModule_Module_Container() = default;
        MIHYModule_Module_Container(const MIHYModule_Module_Container&) = delete;
        MIHYModule_Module_Container(MIHYModule_Module_Container&&) = delete;
        ~MIHYModule_Module_Container() = default;
        MIHYModule_Module_Container& operator=(const MIHYModule_Module_Container&) = delete;
        MIHYModule_Module_Container& operator=(MIHYModule_Module_Container&&) = delete;

        /// @brief 
        /// @param name 
        const decltype(m_module_umap)::value_type& find(const std::string& name);

        
        
    private:

        bool insert(const std::string& name, const MIHYPlatform::Library_Handle& module);

        bool insert(const std::string& name, const std::wstring& module_path);

        friend MIHYModule_Manager;

    };


    class MIHYMODULE_API MIHYModule_Manager{
    private:

        

    public:
        MIHYModule_Manager() = default;
        MIHYModule_Manager(const MIHYModule_Manager&) = delete;
        MIHYModule_Manager(MIHYModule_Manager&&) = delete;
        ~MIHYModule_Manager() = default;
        MIHYModule_Manager& operator=(const MIHYModule_Manager&) = delete;
        MIHYModule_Manager& operator=(MIHYModule_Manager&&) = delete;



    };
}

#endif