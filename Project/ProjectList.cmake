#setting variable
set(MIHYPLATFORM_PROJECT_NAME                           MIHYPlatform)
set(MIHYPLATFORM_DIRECTORY                              ${CMAKE_CURRENT_LIST_DIR}/Engine/Platform)
set(MIHYPLATFORM_CODE_DIRECTORY                         ${MIHYPLATFORM_DIRECTORY}/Code)

set(MIHYMODULE_PROJECT_NAME                             MIHYModule)
set(MIHYMODULE_DIRECTORY                                ${CMAKE_CURRENT_LIST_DIR}/Engine/Module)
set(MIHYMODULE_CODE_DIRECTORY                           ${MIHYMODULE_DIRECTORY}/Code)

set(MIHYCORE_PROJECT_NAME                               MIHYCore)
set(MIHYCORE_DIRECTORY                                  ${CMAKE_CURRENT_LIST_DIR}/Engine/Core)
set(MIHYCORE_CODE_DIRECTORY                             ${MIHYCORE_DIRECTORY}/Code)

set(MIHYCLIENT_PROJECT_NAME                             MIHYClient)
set(MIHYCLIENT_DIRECTORY                                ${CMAKE_CURRENT_LIST_DIR}/Engine/Client)
set(MIHYCLIENT_CODE_DIRECTORY                           ${MIHYCLIENT_DIRECTORY}/Code)


#include directory
include_directories(${MIHYPLATFORM_CODE_DIRECTORY}/Public)
include_directories(${MIHYMODULE_CODE_DIRECTORY}/Public)
include_directories(${MIHYCORE_CODE_DIRECTORY}/Public)
include_directories(${MIHYCLIENT_CODE_DIRECTORY}/Public)

#library directory
link_directories(${MIHY_BINARY_DIRECTORY})

#project
add_subdirectory(Engine/Platform    Platform)
add_subdirectory(Engine/Module      Module)
add_subdirectory(Engine/Core        Core)
add_subdirectory(Engine/Client      Client)