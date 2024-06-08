cmake_minimum_required(VERSION 3.20)
project(${MIHYMODULE_PROJECT_NAME})

# Print log
message(STATUS "---------------------------------------------------")
message(STATUS "LIST_DIRECTORY: ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "SOURCE_DIRECTORY: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "BINARY_DIRECTORY: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "MIHYMODULE_CODE_DIRECTORY: ${MIHYMODULE_CODE_DIRECTORY}")
message(STATUS "---------------------------------------------------")

file(GLOB_RECURSE MIHYMODULE_SOURCE     "${MIHYMODULE_CODE_DIRECTORY}/*.cpp"
                                        "${MIHYMODULE_CODE_DIRECTORY}/*ixx")

add_library(${MIHYMODULE_PROJECT_NAME} SHARED ${MIHYMODULE_SOURCE})

target_link_libraries(${MIHYMODULE_PROJECT_NAME} PRIVATE ${MIHYPLATFORM_PROJECT_NAME})