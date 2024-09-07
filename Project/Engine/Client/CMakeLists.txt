cmake_minimum_required(VERSION 3.20)
project(${MIHYCLIENT_PROJECT_NAME})

# Print log
message(STATUS "---------------------------------------------------")
message(STATUS "LIST_DIRECTORY: ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "SOURCE_DIRECTORY: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "BINARY_DIRECTORY: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "MIHYCLIENT_CODE_DIRECTORY: ${MIHYCLIENT_CODE_DIRECTORY}")
message(STATUS "---------------------------------------------------")

file(GLOB_RECURSE MIHYCLIENT_SOURCE    "${MIHYCLIENT_CODE_DIRECTORY}/*.cpp"
                                       "${MIHYCLIENT_CODE_DIRECTORY}/*.ixx")

add_executable(${MIHYCLIENT_PROJECT_NAME} WIN32 ${MIHYCLIENT_SOURCE})

target_link_libraries(${MIHYCLIENT_PROJECT_NAME} PRIVATE ${MIHYPLATFORM_PROJECT_NAME})
target_link_libraries(${MIHYCLIENT_PROJECT_NAME} PRIVATE ${MIHYCORE_PROJECT_NAME})
target_link_libraries(${MIHYCLIENT_PROJECT_NAME} PRIVATE ${MIHYVULKAN_PROJECT_NAME})