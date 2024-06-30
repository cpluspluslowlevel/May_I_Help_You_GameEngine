set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



if(MSVC)
    add_compile_options(/utf-8)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8 -g)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8 -g)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


set(MIHY_ENGINE_NAME                                    May_I_Help_You_GameEngine)
set(MIHY_ROOT_DIRECTORY                                 ${CMAKE_CURRENT_LIST_DIR}/..)
set(MIHY_PROJECT_DIRECTORY                              ${MIHY_ROOT_DIRECTORY}/Project)
set(MIHY_PROJECT_ENGINE_DIRECTORY                       ${MIHY_PROJECT_DIRECTORY}/Engine)
set(MIHY_BINARY_DIRECTORY                               ${MIHY_ROOT_DIRECTORY}/Binary)
set(MIHY_EXTERNAL_DIRECTORY                             ${MIHY_ROOT_DIRECTORY}/External)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${MIHY_BINARY_DIRECTORY}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${MIHY_BINARY_DIRECTORY}/Release)


message(STATUS "---------------------------------------------------")
message(STATUS "MIHY_ENGINE_NAME: ${MIHY_ENGINE_NAME}")
message(STATUS "MIHY_ROOT_DIRECTORY: ${MIHY_ROOT_DIRECTORY}")
message(STATUS "MIHY_PROJECT_DIRECTORY: ${MIHY_PROJECT_DIRECTORY}")
message(STATUS "MIHY_PROJECT_ENGINE_DIRECTORY: ${MIHY_PROJECT_ENGINE_DIRECTORY}")
message(STATUS "MIHY_BINARY_DIRECTORY: ${MIHY_BINARY_DIRECTORY}")
message(STATUS "MIHY_EXTERNAL_DIRECTORY: ${MIHY_EXTERNAL_DIRECTORY}")
message(STATUS "---------------------------------------------------")