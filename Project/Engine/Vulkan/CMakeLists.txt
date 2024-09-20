cmake_minimum_required(VERSION 3.20)
project(${MIHYVULKAN_PROJECT_NAME})


message(STATUS "---------------------------------------------------")
message(STATUS "LIST_DIRECTORY: ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "SOURCE_DIRECTORY: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "BINARY_DIRECTORY: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "MIHYVULKAN_CODE_DIRECTORY: ${MIHYVULKAN_CODE_DIRECTORY}")
message(STATUS "---------------------------------------------------")

file(GLOB_RECURSE MIHYVULKAN_SOURCE     "${MIHYVULKAN_CODE_DIRECTORY}/*.cpp"
                                        "${MIHYVULKAN_CODE_DIRECTORY}/*ixx")

add_library(${MIHYVULKAN_PROJECT_NAME} SHARED ${MIHYVULKAN_SOURCE})

target_link_directories(${MIHYVULKAN_PROJECT_NAME} PUBLIC $ENV{VULKAN_SDK}/Lib)
                                        
target_include_directories(${MIHYVULKAN_PROJECT_NAME} PUBLIC $ENV{VULKAN_SDK}/Include)