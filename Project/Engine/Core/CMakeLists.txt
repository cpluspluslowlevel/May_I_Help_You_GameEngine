cmake_minimum_required(VERSION 3.20)
project(${MIHYCORE_PROJECT_NAME})


message(STATUS "---------------------------------------------------")
message(STATUS "LIST_DIRECTORY: ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "SOURCE_DIRECTORY: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "BINARY_DIRECTORY: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "MIHYCORE_CODE_DIRECTORY: ${MIHYCORE_CODE_DIRECTORY}")
message(STATUS "---------------------------------------------------")

file(GLOB_RECURSE MIHYCORE_SOURCE   "${MIHYCORE_CODE_DIRECTORY}/*.cpp"
                                    "${MIHYCORE_CODE_DIRECTORY}/*ixx")

add_library(${MIHYCORE_PROJECT_NAME} SHARED ${MIHYCORE_SOURCE})


target_link_libraries(${MIHYCORE_PROJECT_NAME} PUBLIC ${MIHYPLATFORM_PROJECT_NAME})