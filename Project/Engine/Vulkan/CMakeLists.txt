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

message($ENV{VULKAN_SDK}/Include)
message($ENV{VULKAN_SDK}/Lib)

include_directories($ENV{VULKAN_SDK}/Include)
link_directories($ENV{VULKAN_SDK}/Lib)


add_library(${MIHYVULKAN_PROJECT_NAME} SHARED ${MIHYVULKAN_SOURCE})