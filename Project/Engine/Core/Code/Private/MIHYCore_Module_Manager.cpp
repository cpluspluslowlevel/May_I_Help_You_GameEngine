#include "MIHYCore_PCH.h"
#include "MIHYCore_Module_Manager.h"

namespace MIHYCore::Module{

bool MIHYCore_Module_Container::insert(const std::string &name, const MIHYPlatform::Library_Handle &module)
{

    auto iter{m_module_umap.find(name)};
    if(iter != m_module_umap.end()){
        return false;
    }

    m_module_umap.emplace(name, module);

    return true;

}

bool MIHYCore_Module_Container::insert(const std::string &name, const std::wstring& module_path)
{

    auto iter{m_module_umap.find(name)};
    if(iter != m_module_umap.end()){
        return false;
    }

    auto module_handle{MIHYPlatform::load_library(module_path.c_str())};
    if(module_handle == nullptr){
        return false;
    }

    MIHYCORE_MODULE module{};
    module.handle = module_handle;
    m_module_umap.emplace(name, module);

    return true;

}

}